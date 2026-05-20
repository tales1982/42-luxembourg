import styled from "styled-components";

export const ConnectButton = styled.button`
  width: 100%;
  padding: ${({ theme }) => theme.space(1.5)};
  background: transparent;
  color: ${({ theme }) => theme.colors.primary};
  font-weight: 600;
  border: 1px solid ${({ theme }) => theme.colors.primary};
  border-radius: ${({ theme }) => theme.radius.md};
  cursor: pointer;
  transition: all 150ms ease;
  font-size: 0.875rem;

  &:hover:not(:disabled) {
    background: rgba(52, 211, 153, 0.1);
    box-shadow: ${({ theme }) => theme.shadow.glow};
  }

  &:disabled {
    opacity: 0.5;
    cursor: not-allowed;
  }
`;

export const WalletInfo = styled.div`
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(1)};
  padding: ${({ theme }) => theme.space(1)} ${({ theme }) => theme.space(1.5)};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  background: ${({ theme }) => theme.colors.card};
  min-width: 0;
`;

export const WalletAddress = styled.span`
  font-size: 0.8rem;
  font-weight: 600;
  color: ${({ theme }) => theme.colors.primary};
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
  flex: 1;
`;

export const TokenBalance = styled.span`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.textSecondary};
  white-space: nowrap;
`;

export const DisconnectButton = styled.button`
  background: none;
  border: none;
  color: ${({ theme }) => theme.colors.muted};
  cursor: pointer;
  font-size: 0.75rem;
  padding: 2px 4px;
  border-radius: 4px;
  line-height: 1;

  &:hover {
    color: ${({ theme }) => theme.colors.danger};
  }
`;
