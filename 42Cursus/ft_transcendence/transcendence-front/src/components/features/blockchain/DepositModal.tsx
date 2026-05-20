import { useState } from "react";
import { useTranslation } from "react-i18next";
import { useAppDispatch, useAppSelector } from "../../../store/hooks";
import { deposit } from "../../../store/slices/payment.slice";
import { fetchAccount } from "../../../store/slices/payment.slice";
import { env } from "../../../config/env";
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
  PlatformAddress,
  AddressCopy,
} from "./TokenModal.styled";

interface Props {
  onClose: () => void;
}

export function DepositModal({ onClose }: Props) {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const { loading, error } = useAppSelector((s) => s.payment);

  const [amount, setAmount] = useState("");
  const [txHash, setTxHash] = useState("");
  const [success, setSuccess] = useState(false);
  const [copied, setCopied] = useState(false);

  const contractAddress = env.ZION_TOKEN_ADDRESS;

  async function handleSubmit(e: React.FormEvent) {
    e.preventDefault();
    const parsed = parseFloat(amount);
    if (isNaN(parsed) || parsed <= 0) return;

    const result = await dispatch(
      deposit({ amount: parsed, chainTxHash: txHash || undefined })
    );
    if (deposit.fulfilled.match(result)) {
      dispatch(fetchAccount());
      setSuccess(true);
    }
  }

  function handleCopy() {
    navigator.clipboard.writeText(contractAddress);
    setCopied(true);
    setTimeout(() => setCopied(false), 2000);
  }

  return (
    <Overlay onClick={onClose}>
      <Modal onClick={(e) => e.stopPropagation()}>
        <ModalClose onClick={onClose}>✕</ModalClose>
        <ModalTitle>{t("wallet.depositTitle")}</ModalTitle>

        {success ? (
          <ModalBody>
            <SuccessMsg>✓ {t("wallet.depositSuccess")}</SuccessMsg>
            <ActionButton onClick={onClose}>{t("common.close")}</ActionButton>
          </ModalBody>
        ) : (
          <ModalBody as="form" onSubmit={handleSubmit}>
            <SubText>{t("wallet.depositInfo")}</SubText>

            <Label>{t("wallet.contractAddress")}</Label>
            <PlatformAddress>
              {contractAddress}
              <AddressCopy onClick={handleCopy}>
                {copied ? "✓" : "⎘"}
              </AddressCopy>
            </PlatformAddress>

            <Label>{t("wallet.amount")}</Label>
            <Input
              type="number"
              min="0.0001"
              step="0.0001"
              placeholder="0.0000"
              value={amount}
              onChange={(e) => setAmount(e.target.value)}
              required
            />

            <Label>{t("wallet.txHashOptional")}</Label>
            <Input
              type="text"
              placeholder="0x..."
              value={txHash}
              onChange={(e) => setTxHash(e.target.value)}
            />

            {error && <ErrorMsg>{error}</ErrorMsg>}

            <ActionButton type="submit" disabled={loading || !amount}>
              {loading ? t("auth.loading") : t("wallet.depositBtn")}
            </ActionButton>
          </ModalBody>
        )}
      </Modal>
    </Overlay>
  );
}
