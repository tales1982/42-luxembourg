import styled from "styled-components";

export const Overlay = styled.div`
  position: fixed;
  inset: 0;
  background: rgba(0, 0, 0, 0.6);
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 1000;
`;

export const Modal = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: ${({ theme }) => theme.space(4)};
  width: 100%;
  max-width: 420px;
  position: relative;
`;

export const ModalTitle = styled.h3`
  font-size: 1.1rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const ModalClose = styled.button`
  position: absolute;
  top: ${({ theme }) => theme.space(2)};
  right: ${({ theme }) => theme.space(2)};
  background: none;
  border: none;
  cursor: pointer;
  color: ${({ theme }) => theme.colors.muted};
  font-size: 1rem;
  &:hover { color: ${({ theme }) => theme.colors.text}; }
`;

export const ModalBody = styled.div`
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(1.5)};
`;

export const Label = styled.label`
  font-size: 0.8rem;
  font-weight: 600;
  color: ${({ theme }) => theme.colors.muted};
  text-transform: uppercase;
  letter-spacing: 0.04em;
  display: block;
`;

export const Input = styled.input`
  width: 100%;
  padding: ${({ theme }) => `${theme.space(1.5)} ${theme.space(2)}`};
  background: ${({ theme }) => theme.colors.card};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  color: ${({ theme }) => theme.colors.text};
  font-size: 1rem;
  box-sizing: border-box;

  &:focus {
    outline: none;
    border-color: ${({ theme }) => theme.colors.primary};
  }

  &::placeholder {
    color: ${({ theme }) => theme.colors.muted};
  }
`;

export const SubText = styled.p`
  font-size: 0.8rem;
  color: ${({ theme }) => theme.colors.muted};
  line-height: 1.5;
`;

export const ActionButton = styled.button`
  padding: ${({ theme }) => `${theme.space(1.5)} ${theme.space(3)}`};
  background: ${({ theme }) => theme.colors.primary};
  color: white;
  border: none;
  border-radius: ${({ theme }) => theme.radius.md};
  font-size: 0.95rem;
  font-weight: 600;
  cursor: pointer;
  margin-top: ${({ theme }) => theme.space(1)};

  &:disabled {
    opacity: 0.5;
    cursor: not-allowed;
  }

  &:hover:not(:disabled) {
    opacity: 0.85;
  }
`;

export const ErrorMsg = styled.p`
  font-size: 0.8rem;
  color: #f87171;
`;

export const SuccessMsg = styled.p`
  font-size: 0.95rem;
  color: #4ade80;
  font-weight: 600;
`;

export const PlatformAddress = styled.div`
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(1)};
  background: ${({ theme }) => theme.colors.card};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  padding: ${({ theme }) => `${theme.space(1)} ${theme.space(1.5)}`};
  font-family: monospace;
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.textSecondary};
  word-break: break-all;
`;

export const AddressCopy = styled.button`
  background: none;
  border: none;
  cursor: pointer;
  color: ${({ theme }) => theme.colors.primary};
  font-size: 1rem;
  flex-shrink: 0;
  &:hover { opacity: 0.7; }
`;

export const TxHashLink = styled.a`
  font-size: 0.85rem;
  color: ${({ theme }) => theme.colors.primary};
  text-decoration: none;
  font-family: monospace;
  &:hover { text-decoration: underline; }
`;
