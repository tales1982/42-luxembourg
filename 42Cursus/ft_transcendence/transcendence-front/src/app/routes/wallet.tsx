import { createFileRoute } from "@tanstack/react-router";
import { useEffect, useState } from "react";
import { useTranslation } from "react-i18next";
import { useAppDispatch, useAppSelector } from "../../store/hooks";
import { fetchAccount, fetchLedger } from "../../store/slices/payment.slice";
import { fetchTokenBalance, fetchTotalSupply } from "../../store/slices/blockchain.slice";
import { env } from "../../config/env";
import { Spinner } from "../../components/ui/Loading";
import { DepositModal } from "../../components/features/blockchain/DepositModal";
import { WithdrawModal } from "../../components/features/blockchain/WithdrawModal";
import {
  Title,
  Grid,
  Card,
  CardLabel,
  CardValue,
  CardSub,
  SectionTitle,
  Table,
  TableHead,
  TableRow,
  TxTypeBadge,
  AmountCell,
  TxLink,
  NoHash,
  EmptyState,
  CenterLoader,
  WalletNotice,
  BlockchainInfoGrid,
  InfoCard,
  InfoLabel,
  InfoValue,
  InfoLink,
  RefreshButton,
  ChainBadge,
  FullAddress,
  ActionRow,
  DepositButton,
  WithdrawButton,
} from "./wallet.styled";

export const Route = createFileRoute("/wallet")({
  component: WalletPage,
});

const POSITIVE_TYPES = new Set(["DEPOSIT", "TASK_PAYOUT", "ESCROW_RELEASE"]);
const SEPOLIA_CHAIN_ID = 11155111;

function formatDate(iso: string) {
  return new Date(iso).toLocaleString();
}

function shortHash(hash: string) {
  return `${hash.slice(0, 10)}…${hash.slice(-6)}`;
}

function shortAddr(addr: string) {
  return `${addr.slice(0, 8)}…${addr.slice(-6)}`;
}

function WalletPage() {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();

  const [showDeposit, setShowDeposit] = useState(false);
  const [showWithdraw, setShowWithdraw] = useState(false);

  const { account, ledger, ledgerLoading } = useAppSelector((s) => s.payment);
  const { walletAddress, tokenBalance, totalSupply, chainId, isConnected } = useAppSelector((s) => s.blockchain);

  const contractAddress = env.ZION_TOKEN_ADDRESS;

  useEffect(() => {
    dispatch(fetchAccount());
    dispatch(fetchLedger(0));
    dispatch(fetchTotalSupply());
  }, [dispatch]);

  function handleRefreshBalance() {
    if (walletAddress) dispatch(fetchTokenBalance(walletAddress));
  }

  const onChainTxCount = ledger.filter((tx) => tx.chainTxHash).length;

  return (
    <>
      {showDeposit && <DepositModal onClose={() => { setShowDeposit(false); dispatch(fetchLedger(0)); }} />}
      {showWithdraw && <WithdrawModal onClose={() => { setShowWithdraw(false); dispatch(fetchLedger(0)); }} />}

      <Title>{t("wallet.title")}</Title>

      {!isConnected && (
        <WalletNotice>
          🦊 {t("wallet.connectNotice")}
        </WalletNotice>
      )}

      {/* Balance Cards */}
      <Grid>
        <Card>
          <CardLabel>{t("wallet.onChainBalance")}</CardLabel>
          <CardValue>{Number.parseFloat(tokenBalance).toFixed(4)} ZION</CardValue>
          <CardSub>
            {t("wallet.sepoliaNetwork")}
            {isConnected && (
              <RefreshButton onClick={handleRefreshBalance} title={t("wallet.refresh")}>↻</RefreshButton>
            )}
          </CardSub>
        </Card>

        <Card>
          <CardLabel>{t("wallet.offChainBalance")}</CardLabel>
          <CardValue>{account ? Number(account.availableBalance).toFixed(4) : "0.0000"} ZION</CardValue>
          <CardSub>{t("wallet.availableToWithdraw")}</CardSub>
          <ActionRow>
            <DepositButton onClick={() => setShowDeposit(true)}>
              ↓ {t("wallet.deposit")}
            </DepositButton>
            <WithdrawButton
              onClick={() => setShowWithdraw(true)}
              disabled={!isConnected || !account || Number(account.availableBalance) <= 0}
            >
              ↑ {t("wallet.withdraw")}
            </WithdrawButton>
          </ActionRow>
        </Card>

        <Card>
          <CardLabel>{t("wallet.lockedBalance")}</CardLabel>
          <CardValue>{account ? Number(account.lockedBalance).toFixed(4) : "0.0000"} ZION</CardValue>
          <CardSub>{t("wallet.lockedInEscrow")}</CardSub>
        </Card>

        <Card>
          <CardLabel>{t("wallet.connectedWallet")}</CardLabel>
          <CardValue style={{ fontSize: "0.85rem", wordBreak: "break-all" }}>
            {isConnected && walletAddress ? shortAddr(walletAddress) : "—"}
          </CardValue>
          {isConnected && walletAddress && (
            <CardSub>
              <TxLink
                href={`https://sepolia.etherscan.io/address/${walletAddress}`}
                target="_blank"
                rel="noreferrer"
              >
                {t("wallet.viewOnEtherscan")} ↗
              </TxLink>
            </CardSub>
          )}
        </Card>
      </Grid>

      {/* Blockchain Info Section */}
      <SectionTitle>{t("wallet.blockchainInfo")}</SectionTitle>

      <BlockchainInfoGrid>
        <InfoCard>
          <InfoLabel>{t("wallet.network")}</InfoLabel>
          <InfoValue>
            <ChainBadge>Sepolia Testnet</ChainBadge>
          </InfoValue>
          <InfoValue style={{ fontSize: "0.75rem", color: "var(--color-muted, #888)" }}>
            Chain ID: {chainId ?? SEPOLIA_CHAIN_ID}
          </InfoValue>
        </InfoCard>

        <InfoCard>
          <InfoLabel>{t("wallet.tokenContract")}</InfoLabel>
          <FullAddress title={contractAddress}>
            {contractAddress ? shortHash(contractAddress) : "—"}
          </FullAddress>
          {contractAddress && (
            <InfoLink
              href={`https://sepolia.etherscan.io/token/${contractAddress}`}
              target="_blank"
              rel="noreferrer"
            >
              {t("wallet.viewContract")} ↗
            </InfoLink>
          )}
        </InfoCard>

        <InfoCard>
          <InfoLabel>{t("wallet.totalSupply")}</InfoLabel>
          <InfoValue>{Number.parseFloat(totalSupply).toLocaleString(undefined, { maximumFractionDigits: 2 })} ZION</InfoValue>
          <InfoValue style={{ fontSize: "0.75rem", color: "var(--color-muted, #888)" }}>
            ERC-20 · 18 decimals
          </InfoValue>
        </InfoCard>

        <InfoCard>
          <InfoLabel>{t("wallet.onChainTxCount")}</InfoLabel>
          <InfoValue style={{ fontSize: "1.6rem", fontWeight: 700 }}>{onChainTxCount}</InfoValue>
          <InfoValue style={{ fontSize: "0.75rem", color: "var(--color-muted, #888)" }}>
            {t("wallet.txWithHash")}
          </InfoValue>
        </InfoCard>

        {isConnected && walletAddress && (
          <InfoCard style={{ gridColumn: "1 / -1" }}>
            <InfoLabel>{t("wallet.fullAddress")}</InfoLabel>
            <FullAddress style={{ fontFamily: "monospace", fontSize: "0.8rem", wordBreak: "break-all" }}>
              {walletAddress}
            </FullAddress>
            <InfoLink
              href={`https://sepolia.etherscan.io/address/${walletAddress}`}
              target="_blank"
              rel="noreferrer"
            >
              {t("wallet.viewOnEtherscan")} ↗
            </InfoLink>
          </InfoCard>
        )}
      </BlockchainInfoGrid>

      {/* Transaction History */}
      <SectionTitle>{t("wallet.transactionHistory")}</SectionTitle>

      {ledgerLoading ? (
        <CenterLoader><Spinner $size="md" /></CenterLoader>
      ) : ledger.length === 0 ? (
        <EmptyState>{t("wallet.noTransactions")}</EmptyState>
      ) : (
        <Table>
          <TableHead>
            <span>{t("wallet.date")}</span>
            <span>{t("wallet.type")}</span>
            <span>{t("wallet.txHash")}</span>
            <span>{t("wallet.amount")}</span>
          </TableHead>
          {ledger.map((tx) => {
            const positive = POSITIVE_TYPES.has(tx.txType);
            return (
              <TableRow key={tx.id}>
                <span style={{ color: "var(--color-muted, #888)", fontSize: "0.78rem" }}>
                  {formatDate(tx.createdAt)}
                </span>
                <TxTypeBadge $type={tx.txType}>
                  {tx.txType.replace("_", " ")}
                </TxTypeBadge>
                <span>
                  {tx.chainTxHash ? (
                    <TxLink
                      href={`https://sepolia.etherscan.io/tx/${tx.chainTxHash}`}
                      target="_blank"
                      rel="noreferrer"
                      title={tx.chainTxHash}
                    >
                      {shortHash(tx.chainTxHash)} ↗
                    </TxLink>
                  ) : (
                    <NoHash>{t("wallet.offChain")}</NoHash>
                  )}
                </span>
                <AmountCell $positive={positive}>
                  {positive ? "+" : "-"}{Number(tx.amount).toFixed(2)} ZION
                </AmountCell>
              </TableRow>
            );
          })}
        </Table>
      )}
    </>
  );
}
