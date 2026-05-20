import styled from "styled-components";

export const Title = styled.h2`
  font-size: 1.5rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const List = styled.div`
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(2)};
`;

export const TaskItem = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: ${({ theme }) => theme.space(2.5)};
`;

export const TaskTop = styled.div`
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  margin-bottom: ${({ theme }) => theme.space(1.5)};
  gap: ${({ theme }) => theme.space(1)};
`;

export const TaskTitle = styled.h4`
  font-size: 1.05rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
`;

export const TaskDesc = styled.p`
  color: ${({ theme }) => theme.colors.muted};
  font-size: 0.85rem;
  line-height: 1.5;
  margin-bottom: ${({ theme }) => theme.space(2)};
`;

export const MetaRow = styled.div`
  display: flex;
  align-items: center;
  justify-content: space-between;
  margin-bottom: ${({ theme }) => theme.space(2)};
`;

export const CategoryTag = styled.span`
  padding: ${({ theme }) => `${theme.space(0.5)} ${theme.space(1.5)}`};
  background: ${({ theme }) => theme.colors.card};
  border-radius: 9999px;
  font-size: 0.8rem;
  color: ${({ theme }) => theme.colors.textSecondary};
`;

export const RewardText = styled.span`
  font-weight: 700;
  color: ${({ theme }) => theme.colors.primary};
`;

export const InfoText = styled.div`
  font-size: 0.85rem;
  color: ${({ theme }) => theme.colors.muted};
  margin-bottom: ${({ theme }) => theme.space(1.5)};
`;

export const ProofBox = styled.div`
  padding: ${({ theme }) => theme.space(1.5)};
  background: ${({ theme }) => theme.colors.card};
  border-radius: ${({ theme }) => theme.radius.md};
  margin-bottom: ${({ theme }) => theme.space(2)};
`;

export const ProofLabel = styled.h5`
  font-weight: 600;
  color: ${({ theme }) => theme.colors.text};
  font-size: 0.85rem;
  margin-bottom: 4px;
`;

export const ProofText = styled.p`
  font-size: 0.825rem;
  color: ${({ theme }) => theme.colors.textSecondary};
  line-height: 1.5;
`;

export const ActionRow = styled.div`
  display: flex;
  gap: ${({ theme }) => theme.space(1.5)};
`;

export const ActionStack = styled.div`
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(1)};
`;

export const CenterLoader = styled.div`
  display: flex;
  justify-content: center;
  padding: ${({ theme }) => theme.space(6)};
`;

export const EmptyState = styled.div`
  text-align: center;
  padding: ${({ theme }) => theme.space(6)};
  color: ${({ theme }) => theme.colors.muted};
`;

export const PaidBox = styled.div`
  padding: ${({ theme }) => `${theme.space(1)} ${theme.space(2)}`};
  background: ${({ theme }) => theme.colors.card};
  border-radius: ${({ theme }) => theme.radius.md};
  font-weight: 500;
  color: ${({ theme }) => theme.colors.text};
  font-size: 0.875rem;
`;

export const AttachmentsRow = styled.div`
  display: flex;
  flex-wrap: wrap;
  gap: ${({ theme }) => theme.space(1.5)};
  margin-top: ${({ theme }) => theme.space(1.5)};
`;

export const ProofImage = styled.img`
  max-width: 100%;
  max-height: 220px;
  border-radius: ${({ theme }) => theme.radius.md};
  border: 1px solid ${({ theme }) => theme.colors.border};
  object-fit: contain;
  cursor: pointer;
`;

export const AttachmentLink = styled.a`
  display: inline-flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(0.75)};
  padding: ${({ theme }) => `${theme.space(0.75)} ${theme.space(1.5)}`};
  background: ${({ theme }) => theme.colors.card};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  color: ${({ theme }) => theme.colors.primary};
  font-size: 0.8rem;
  text-decoration: none;

  &:hover {
    text-decoration: underline;
  }
`;
