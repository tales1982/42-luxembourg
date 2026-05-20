import styled from "styled-components";
import { Link } from "@tanstack/react-router";

export const PageWrapper = styled.div`
  min-height: 100vh;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: ${({ theme }) => theme.space(2)};
  background: ${({ theme }) => theme.colors.bg};
`;

export const RegCard = styled.div`
  width: 100%;
  max-width: 420px;
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: ${({ theme }) => theme.space(4)};
`;

export const LogoSection = styled.div`
  text-align: center;
  margin-bottom: ${({ theme }) => theme.space(4)};
`;

export const Logo = styled.h1`
  font-size: 1.875rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.primary};
`;

export const Subtitle = styled.p`
  color: ${({ theme }) => theme.colors.muted};
  margin-top: ${({ theme }) => theme.space(0.5)};
  font-size: 0.9rem;
`;

export const Form = styled.form`
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(2.5)};
`;

export const TermsBox = styled.div`
  border: 1px solid ${({ theme }) => theme.colors.border};
  background: ${({ theme }) => theme.colors.card};
  border-radius: ${({ theme }) => theme.radius.md};
  padding: ${({ theme }) => theme.space(1.5)};
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(1)};
`;

export const TermsTitle = styled.div`
  font-weight: 600;
  color: ${({ theme }) => theme.colors.text};
  font-size: 0.9rem;
`;

export const TermsText = styled.p`
  color: ${({ theme }) => theme.colors.textSecondary};
  font-size: 0.8rem;
  line-height: 1.5;
`;

export const CheckboxRow = styled.label`
  display: flex;
  align-items: flex-start;
  gap: 8px;
  font-size: 0.8rem;
  color: ${({ theme }) => theme.colors.muted};
  cursor: pointer;
  line-height: 1.5;

  span {
    flex: 1;
  }
`;

export const CheckboxInput = styled.input`
  margin-top: 2px;
`;

export const InlineError = styled.div`
  color: ${({ theme }) => theme.colors.danger};
  font-size: 0.8rem;
`;

export const ErrorMsg = styled.div`
  color: ${({ theme }) => theme.colors.danger};
  font-size: 0.85rem;
  text-align: center;
`;

export const SuccessMsg = styled.div`
  color: ${({ theme }) => theme.colors.success};
  padding: ${({ theme }) => theme.space(2.5)} 0;
  text-align: center;
  font-size: 0.95rem;
`;

export const BottomText = styled.p`
  text-align: center;
  color: ${({ theme }) => theme.colors.muted};
  font-size: 0.875rem;
  margin-top: ${({ theme }) => theme.space(2)};
`;

export const AccentLink = styled(Link)`
  color: ${({ theme }) => theme.colors.primary};
  font-size: inherit;
  display: inline;
  &:hover {
    text-decoration: underline;
  }
`;

export const LangRow = styled.div`
  display: flex;
  justify-content: center;
  gap: 8px;
  margin-bottom: ${({ theme }) => theme.space(2)};
`;

export const LangBtn = styled.button<{ $active?: boolean }>`
  padding: 4px 10px;
  background: ${({ theme, $active }) =>
    $active ? theme.colors.primary : "transparent"};
  color: ${({ theme, $active }) =>
    $active ? theme.colors.bg : theme.colors.muted};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.sm};
  cursor: pointer;
  font-size: 0.75rem;
  font-weight: 600;
`;
