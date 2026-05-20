import { useState } from "react";
import { useTranslation } from "react-i18next";
import { useAppDispatch, useAppSelector } from "../../../store/hooks";
import { withdraw, fetchAccount } from "../../../store/slices/payment.slice";
import { fetchTokenBalance } from "../../../store/slices/blockchain.slice";
import {
  Overlay,
  Modal,
  ModalTitle,
  ModalClose,
  ModalBody,
  Label,
  Input,
  SubText,
  ActionButton,
  ErrorMsg,
  SuccessMsg,
  TxHashLink,
} from "./TokenModal.styled";

interface Props {
  onClose: () => void;
}

export function WithdrawModal({ onClose }: Props) {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const { loading, error, account } = useAppSelector((s) => s.payment);
  const { walletAddress, isConnected } = useAppSelector((s) => s.blockchain);

  const [amount, setAmount] = useState("");
  const [txHash, setTxHash] = useState<string | null>(null);
  const [done, setDone] = useState(false);

  const available = account ? Number(account.availableBalance) : 0;

  async function handleSubmit(e: React.FormEvent) {
    e.preventDefault();
    const parsed = parseFloat(amount);
    if (isNaN(parsed) || parsed <= 0) return;

    const result = await dispatch(withdraw({ amount: parsed }));
    if (withdraw.fulfilled.match(result)) {
      // Refresh balances
      dispatch(fetchAccount());
      if (walletAddress) dispatch(fetchTokenBalance(walletAddress));
      // Try to get txHash from the refreshed ledger
      const updatedAccount = result.payload;
      setTxHash((updatedAccount as any)?.chainTxHash ?? null);
      setDone(true);
    }
  }

  function handleMax() {
    setAmount(available.toFixed(4));
  }

  return (
    <Overlay onClick={onClose}>
      <Modal onClick={(e) => e.stopPropagation()}>
        <ModalClose onClick={onClose}>✕</ModalClose>
        <ModalTitle>{t("wallet.withdrawTitle")}</ModalTitle>

        {done ? (
          <ModalBody>
            <SuccessMsg>✓ {t("wallet.withdrawSuccess")}</SuccessMsg>
            {txHash && (
              <TxHashLink
                href={`https://sepolia.etherscan.io/tx/${txHash}`}
                target="_blank"
                rel="noreferrer"
              >
                {t("wallet.viewTxEtherscan")} ↗
              </TxHashLink>
            )}
            <ActionButton onClick={onClose}>{t("common.close")}</ActionButton>
          </ModalBody>
        ) : (
          <ModalBody as="form" onSubmit={handleSubmit}>
            <SubText>
              {isConnected && walletAddress
                ? `${t("wallet.withdrawTo")}: ${walletAddress.slice(0, 10)}…${walletAddress.slice(-6)}`
                : t("wallet.connectNotice")}
            </SubText>

            <Label>
              {t("wallet.amount")}
              <span style={{ float: "right", color: "#888", fontSize: "0.75rem" }}>
                {t("wallet.available")}: {available.toFixed(4)} ZION
              </span>
            </Label>
            <Input
              type="number"
              min="0.0001"
              step="0.0001"
              max={available}
              placeholder="0.0000"
              value={amount}
              onChange={(e) => setAmount(e.target.value)}
              required
            />
            <button
              type="button"
              onClick={handleMax}
              style={{ background: "none", border: "none", color: "var(--color-primary, #6366f1)", cursor: "pointer", fontSize: "0.75rem", padding: 0, textAlign: "right" }}
            >
              MAX
            </button>

            {error && <ErrorMsg>{error}</ErrorMsg>}

            <ActionButton
              type="submit"
              disabled={loading || !amount || !isConnected}
            >
              {loading ? t("auth.loading") : t("wallet.withdrawBtn")}
            </ActionButton>

            {!isConnected && (
              <ErrorMsg>{t("wallet.connectFirst")}</ErrorMsg>
            )}
          </ModalBody>
        )}
      </Modal>
    </Overlay>
  );
}
