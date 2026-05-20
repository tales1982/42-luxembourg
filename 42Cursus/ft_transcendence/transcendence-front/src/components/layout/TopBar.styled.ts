import styled from "styled-components";

export const Header = styled.header`
  position: sticky;
  top: 0;
  background: ${({ theme }) => theme.colors.bgSecondary};
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
  padding: ${({ theme }) => theme.space(2)};
  z-index: 30;
`;



export const Row = styled.div`
  display: flex;
  flex-wrap: wrap;
  align-items: center;
  justify-content: space-between;
  gap: ${({ theme }) => theme.space(2)};
`;



export const SearchWrapper = styled.div`
  position: relative;
  flex: 1;
  max-width: 320px;
`;



export const SearchIcon = styled.span`
  position: absolute;
  left: 12px;
  top: 50%;
  transform: translateY(-50%);
  color: ${({ theme }) => theme.colors.muted};
  font-size: 0.85rem;
`;



export const SearchInput = styled.input`
  width: 100%;
  padding: ${({ theme }) => theme.space(1.5)};
  padding-left: 36px;
  background: ${({ theme }) => theme.colors.card};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  color: ${({ theme }) => theme.colors.text};
  transition: all 150ms ease;

  &::placeholder {
    color: ${({ theme }) => theme.colors.muted};
  }

  &:focus {
    outline: none;
    border-color: ${({ theme }) => theme.colors.primary};
    box-shadow: 0 0 0 2px rgba(52, 211, 153, 0.2);
  }
`;



export const Actions = styled.div`
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(1.5)};
`;



export const WalletBtn = styled.button<{ $connected?: boolean }>`
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(1)};
  padding: ${({ theme }) => `${theme.space(1)} ${theme.space(2)}`};
  background: ${({ theme, $connected }) =>
    $connected ? "rgba(52, 211, 153, 0.15)" : theme.colors.card};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  color: ${({ theme }) => theme.colors.text};
  cursor: pointer;
  transition: all 150ms ease;
  font-size: 0.875rem;

  &:hover {
    background: ${({ theme }) => theme.colors.cardHover};
  }
`;



export const BalanceBox = styled.div`
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(1)};
  padding: ${({ theme }) => `${theme.space(1)} ${theme.space(2)}`};
  background: ${({ theme }) => theme.colors.card};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  font-size: 0.875rem;
  font-weight: 600;
`;



export const CoinIcon = styled.span`
  color: ${({ theme }) => theme.colors.warning};
`;



export const MobileMenuBtn = styled.button`
  display: none;
  background: ${({ theme }) => theme.colors.card};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.sm};
  color: ${({ theme }) => theme.colors.text};
  padding: ${({ theme }) => theme.space(1)};
  cursor: pointer;

  @media (max-width: 768px) {
    display: flex;
    align-items: center;
    justify-content: center;
  }
`;

/* ── Language Select ── */



export const LangWrapper = styled.div`
  position: relative;
`;



export const LangButton = styled.button`
  display: flex;
  align-items: center;
  gap: 6px;
  padding: ${({ theme }) => `${theme.space(1)} ${theme.space(1.5)}`};
  background: ${({ theme }) => theme.colors.card};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  color: ${({ theme }) => theme.colors.text};
  cursor: pointer;
  font-size: 0.85rem;
  transition: all 150ms ease;

  &:hover {
    border-color: ${({ theme }) => theme.colors.borderHover};
    background: ${({ theme }) => theme.colors.cardHover};
  }
`;



export const LangDropdown = styled.div<{ $open: boolean }>`
  display: ${({ $open }) => ($open ? "block" : "none")};
  position: absolute;
  top: calc(100% + 4px);
  right: 0;
  min-width: 160px;
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  box-shadow: ${({ theme }) => theme.shadow.md};
  overflow: hidden;
  z-index: 50;
`;



export const LangOption = styled.button<{ $active?: boolean }>`
  display: flex;
  align-items: center;
  gap: 10px;
  width: 100%;
  padding: ${({ theme }) => `${theme.space(1.5)} ${theme.space(2)}`};
  background: ${({ $active }) =>
    $active ? "rgba(52, 211, 153, 0.1)" : "transparent"};
  border: none;
  color: ${({ $active, theme }) =>
    $active ? theme.colors.primary : theme.colors.text};
  cursor: pointer;
  font-size: 0.85rem;
  text-align: left;
  transition: background 150ms ease;

  &:hover {
    background: ${({ theme }) => theme.colors.card};
  }
`;



export const Flag = styled.span`
  font-size: 1.2rem;
  line-height: 1;
`;



export const ChevronDown = styled.span`
  font-size: 0.6rem;
  color: ${({ theme }) => theme.colors.muted};
`;

/* ── User Greeting ── */

export const UserGreeting = styled.div`
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(1)};
  padding: ${({ theme }) => `${theme.space(1)} ${theme.space(2)}`};
  background: ${({ theme }) => theme.colors.card};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  font-size: 0.875rem;
  color: ${({ theme }) => theme.colors.text};

  @media (max-width: 640px) {
    display: none;
  }
`;

export const UserAvatar = styled.span`
  width: 24px;
  height: 24px;
  border-radius: 50%;
  background: ${({ theme }) => theme.colors.primary};
  color: #000;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 0.75rem;
  font-weight: 700;
  flex-shrink: 0;
  overflow: hidden;

  img {
    width: 100%;
    height: 100%;
    object-fit: cover;
    display: block;
  }
`;

/* ── Logout Button ── */



export const LogoutBtn = styled.button`
  display: flex;
  align-items: center;
  gap: 6px;
  padding: ${({ theme }) => `${theme.space(1)} ${theme.space(2)}`};
  background: transparent;
  border: 1px solid ${({ theme }) => theme.colors.danger};
  border-radius: ${({ theme }) => theme.radius.md};
  color: ${({ theme }) => theme.colors.danger};
  cursor: pointer;
  font-size: 0.85rem;
  font-weight: 500;
  transition: all 150ms ease;

  &:hover {
    background: ${({ theme }) => theme.colors.danger};
    color: #fff;
  }
`;
