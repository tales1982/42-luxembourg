import styled from "styled-components";

export const Title = styled.h2`
  font-size: 1.5rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const Grid = styled.div`
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(220px, 1fr));
  gap: ${({ theme }) => theme.space(2)};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const Card = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: ${({ theme }) => theme.space(3)};
`;

export const CardLabel = styled.p`
  font-size: 0.8rem;
  color: ${({ theme }) => theme.colors.muted};
  margin-bottom: ${({ theme }) => theme.space(0.75)};
  text-transform: uppercase;
  letter-spacing: 0.05em;
`;

export const CardValue = styled.p`
  font-size: 1.5rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.primary};
`;

export const CardSub = styled.p`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.muted};
  margin-top: ${({ theme }) => theme.space(0.5)};
  word-break: break-all;
`;

export const SectionTitle = styled.h3`
  font-size: 1.1rem;
  font-weight: 600;
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: ${({ theme }) => theme.space(2)};
`;

export const Table = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  overflow: hidden;
`;

export const TableHead = styled.div`
  display: grid;
  grid-template-columns: 120px 80px 1fr 100px;
  gap: ${({ theme }) => theme.space(2)};
  padding: ${({ theme }) => `${theme.space(1.5)} ${theme.space(2)}`};
  background: ${({ theme }) => theme.colors.card};
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
  font-size: 0.75rem;
  font-weight: 600;
  color: ${({ theme }) => theme.colors.muted};
  text-transform: uppercase;
`;

export const TableRow = styled.div`
  display: grid;
  grid-template-columns: 120px 80px 1fr 100px;
  gap: ${({ theme }) => theme.space(2)};
  padding: ${({ theme }) => `${theme.space(1.5)} ${theme.space(2)}`};
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
  font-size: 0.85rem;
  align-items: center;

  &:last-child {
    border-bottom: none;
  }

  &:hover {
    background: ${({ theme }) => theme.colors.card};
  }
`;

export const TxTypeBadge = styled.span<{ $type: string }>`
  padding: ${({ theme }) => `${theme.space(0.4)} ${theme.space(1)}`};
  border-radius: 9999px;
  font-size: 0.75rem;
  font-weight: 600;
  background: ${({ $type, theme }) => {
    switch ($type) {
      case "DEPOSIT":
      case "TASK_PAYOUT":
      case "ESCROW_RELEASE":
        return "rgba(74, 222, 128, 0.15)";
      case "WITHDRAW":
      case "ESCROW_LOCK":
        return "rgba(248, 113, 113, 0.15)";
      default:
        return theme.colors.card;
    }
  }};
  color: ${({ $type, theme }) => {
    switch ($type) {
      case "DEPOSIT":
      case "TASK_PAYOUT":
      case "ESCROW_RELEASE":
        return "#4ade80";
      case "WITHDRAW":
      case "ESCROW_LOCK":
        return "#f87171";
      default:
        return theme.colors.textSecondary;
    }
  }};
`;

export const AmountCell = styled.span<{ $positive: boolean }>`
  font-weight: 600;
  color: ${({ $positive }) => ($positive ? "#4ade80" : "#f87171")};
`;

export const TxLink = styled.a`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.primary};
  text-decoration: none;
  font-family: monospace;
  word-break: break-all;

  &:hover {
    text-decoration: underline;
  }
`;

export const NoHash = styled.span`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.muted};
`;

export const EmptyState = styled.div`
  text-align: center;
  padding: ${({ theme }) => theme.space(6)};
  color: ${({ theme }) => theme.colors.muted};
`;

export const CenterLoader = styled.div`
  display: flex;
  justify-content: center;
  padding: ${({ theme }) => theme.space(4)};
`;

export const WalletNotice = styled.div`
  background: rgba(99, 102, 241, 0.1);
  border: 1px solid rgba(99, 102, 241, 0.3);
  border-radius: ${({ theme }) => theme.radius.md};
  padding: ${({ theme }) => theme.space(2)};
  font-size: 0.85rem;
  color: ${({ theme }) => theme.colors.textSecondary};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const BlockchainInfoGrid = styled.div`
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
  gap: ${({ theme }) => theme.space(2)};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const InfoCard = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: ${({ theme }) => theme.space(2.5)};
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(0.5)};
`;

export const InfoLabel = styled.p`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.muted};
  text-transform: uppercase;
  letter-spacing: 0.05em;
  font-weight: 600;
`;

export const InfoValue = styled.p`
  font-size: 1rem;
  font-weight: 600;
  color: ${({ theme }) => theme.colors.text};
`;

export const InfoLink = styled.a`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.primary};
  text-decoration: none;
  margin-top: ${({ theme }) => theme.space(0.5)};

  &:hover {
    text-decoration: underline;
  }
`;

export const RefreshButton = styled.button`
  background: none;
  border: none;
  cursor: pointer;
  color: ${({ theme }) => theme.colors.primary};
  font-size: 1rem;
  padding: 0 0 0 ${({ theme }) => theme.space(0.5)};
  line-height: 1;
  vertical-align: middle;

  &:hover {
    opacity: 0.7;
  }
`;

export const ChainBadge = styled.span`
  display: inline-block;
  padding: ${({ theme }) => `${theme.space(0.3)} ${theme.space(1)}`};
  background: rgba(99, 102, 241, 0.15);
  color: #818cf8;
  border-radius: 9999px;
  font-size: 0.8rem;
  font-weight: 600;
`;

export const FullAddress = styled.p`
  font-size: 0.8rem;
  font-family: monospace;
  color: ${({ theme }) => theme.colors.textSecondary};
  word-break: break-all;
`;

export const ActionRow = styled.div`
  display: flex;
  gap: ${({ theme }) => theme.space(1)};
  margin-top: ${({ theme }) => theme.space(1.5)};
`;

const BaseActionBtn = styled.button`
  flex: 1;
  padding: ${({ theme }) => `${theme.space(0.75)} ${theme.space(1)}`};
  border: none;
  border-radius: ${({ theme }) => theme.radius.md};
  font-size: 0.8rem;
  font-weight: 600;
  cursor: pointer;

  &:disabled {
    opacity: 0.4;
    cursor: not-allowed;
  }
`;

export const DepositButton = styled(BaseActionBtn)`
  background: rgba(74, 222, 128, 0.15);
  color: #4ade80;

  &:hover:not(:disabled) {
    background: rgba(74, 222, 128, 0.25);
  }
`;

export const WithdrawButton = styled(BaseActionBtn)`
  background: rgba(99, 102, 241, 0.15);
  color: #818cf8;

  &:hover:not(:disabled) {
    background: rgba(99, 102, 241, 0.25);
  }
`;
