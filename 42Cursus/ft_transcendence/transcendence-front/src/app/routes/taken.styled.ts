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
  margin-bottom: ${({ theme }) => theme.space(3)};
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

export const InfoRow = styled.div`
  display: flex;
  flex-direction: column;
  gap: 4px;
  font-size: 0.85rem;
  color: ${({ theme }) => theme.colors.muted};
  margin-bottom: ${({ theme }) => theme.space(2)};
`;

export const ActionsRow = styled.div`
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(1.5)};
`;

export const WaitingBox = styled.div`
  width: 100%;
  padding: ${({ theme }) => theme.space(1)};
  background: ${({ theme }) => theme.colors.card};
  border-radius: ${({ theme }) => theme.radius.md};
  text-align: center;
  font-weight: 500;
  color: ${({ theme }) => theme.colors.text};
  font-size: 0.875rem;
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