import styled, { css, keyframes } from "styled-components";

export type ToastType = "success" | "error" | "warning" | "info";

export const slideIn = keyframes`
  from { transform: translateY(100px); opacity: 0; }
  to { transform: translateY(0); opacity: 1; }
`;

export const slideOut = keyframes`
  from { transform: translateY(0); opacity: 1; }
  to { transform: translateY(100px); opacity: 0; }
`;

export const Container = styled.div<{ $visible: boolean }>`
  position: fixed;
  bottom: ${({ theme }) => theme.space(4)};
  right: ${({ theme }) => theme.space(4)};
  padding: ${({ theme }) => `${theme.space(2)} ${theme.space(3)}`};
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.3);
  z-index: 1000;
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(1.5)};
  max-width: 400px;

  ${({ $visible }) =>
    $visible
      ? css`animation: ${slideIn} 300ms ease forwards;`
      : css`animation: ${slideOut} 300ms ease forwards;`}
`;

export const Icon = styled.span<{ $type: ToastType }>`
  font-size: 1.1rem;
  color: ${({ theme, $type }) => {
    switch ($type) {
      case "success": return theme.colors.success;
      case "error": return theme.colors.danger;
      case "warning": return theme.colors.warning;
      default: return theme.colors.info;
    }
  }};
`;

export const Message = styled.span`
  color: ${({ theme }) => theme.colors.text};
  font-size: 0.875rem;
`;