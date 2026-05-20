import { Link } from "@tanstack/react-router";
import styled, { css } from "styled-components";

export const Bar = styled.header`
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
  padding: ${({ theme }) => theme.space(2)};
`;

export const Row = styled.div`
  max-width: 1100px;
  margin: 0 auto;
  display: flex;
  gap: ${({ theme }) => theme.space(2)};
  align-items: center;
  justify-content: space-between;
`;

export const Left = styled.div`
  display: flex;
  gap: ${({ theme }) => theme.space(2)};
  align-items: center;
`;

export const Right = styled.div`
  display: flex;
  gap: ${({ theme }) => theme.space(1)};
  align-items: center;
`;



export const NavLink = styled(Link)<{ $active?: boolean }>`
  display: flex;
  align-items: center;
  padding: ${({ theme }) => theme.space(1.5)};
  border-radius: ${({ theme }) => theme.radius.md};
  color: ${({ theme }) => theme.colors.textSecondary};
  transition: all 150ms ease;
  font-size: 0.925rem;
  font-weight: 500;

  &:hover {
    background: ${({ theme }) => theme.colors.card};
    color: ${({ theme }) => theme.colors.text};
  }

  ${({ $active, theme }) =>
    $active &&
    css`
      border-left: 3px solid ${theme.colors.primary};
      background: rgba(52, 211, 153, 0.08);
      color: ${theme.colors.text};
    `}
`;
export const NavBtn = styled(NavLink)`
  display: flex;
  align-items: center;
  gap: 4px;
  border: 1px solid ${({ theme }) => theme.colors.border};
  background: transparent;
  color: ${({ theme }) => theme.colors.text};
  border-radius: ${({ theme }) => theme.radius.md};
  padding: 6px 10px;
  cursor: pointer;
  &:hover {
    border-color: ${({ theme }) => theme.colors.primary};
  }
`;
export const RegisterBtn = styled(NavBtn)`
  background: ${({ theme }) => theme.colors.primary};
  color: ${({ theme }) => theme.colors.panel};
`;
