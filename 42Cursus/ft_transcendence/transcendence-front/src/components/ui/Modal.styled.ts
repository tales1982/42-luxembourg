import styled from "styled-components";

export const Overlay = styled.div`
  position: fixed;
  inset: 0;
  background: rgba(6, 21, 11, 0.85);
  display: flex;
  align-items: center;
  justify-content: center;
  padding: ${({ theme }) => theme.space(2)};
  z-index: 50;
`;

export const Panel = styled.div<{ $maxWidth?: string }>`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  width: 100%;
  max-width: ${({ $maxWidth }) => $maxWidth || "640px"};
  max-height: 90vh;
  overflow-y: auto;
`;

export const Header = styled.div`
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: ${({ theme }) => theme.space(3)};
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
`;

export const Title = styled.h3`
  font-size: 1.25rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
`;

export const CloseBtn = styled.button`
  background: none;
  border: none;
  color: ${({ theme }) => theme.colors.muted};
  cursor: pointer;
  font-size: 1.25rem;
  padding: ${({ theme }) => theme.space(0.5)};
  transition: color 150ms ease;

  &:hover {
    color: ${({ theme }) => theme.colors.text};
  }
`;

export const Body = styled.div`
  padding: ${({ theme }) => theme.space(3)};
`;