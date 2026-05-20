import styled from "styled-components";

export const Header = styled.div`
  display: flex;
  flex-wrap: wrap;
  align-items: center;
  justify-content: space-between;
  margin-bottom: ${({ theme }) => theme.space(3)};
  gap: ${({ theme }) => theme.space(2)};
`;

export const Title = styled.h2`
  font-size: 1.5rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
`;

export const Filters = styled.div`
  display: flex;
  flex-wrap: wrap;
  gap: ${({ theme }) => theme.space(1.5)};
`;

export const Grid = styled.div`
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(320px, 1fr));
  gap: ${({ theme }) => theme.space(3)};

  @media (max-width: 768px) {
    grid-template-columns: 1fr;
  }
`;

export const TaskCard = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: ${({ theme }) => theme.space(2.5)};
  transition: all 200ms ease;

  &:hover {
    border-color: ${({ theme }) => theme.colors.borderHover};
    box-shadow: ${({ theme }) => theme.shadow.md};
  }
`;

export const CardTop = styled.div`
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  margin-bottom: ${({ theme }) => theme.space(1.5)};
  gap: ${({ theme }) => theme.space(1)};
`;

export const CardTitle = styled.h4`
  font-size: 1.05rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
  flex: 1;
`;

export const CardDesc = styled.p`
  color: ${({ theme }) => theme.colors.muted};
  font-size: 0.85rem;
  line-height: 1.5;
  margin-bottom: ${({ theme }) => theme.space(2)};
  display: -webkit-box;
  -webkit-line-clamp: 2;
  -webkit-box-orient: vertical;
  overflow: hidden;
`;

export const CardMeta = styled.div`
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
  font-size: 1.1rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.primary};
`;

export const CardFooter = styled.div`
  display: flex;
  justify-content: space-between;
  font-size: 0.8rem;
  color: ${({ theme }) => theme.colors.muted};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const FooterItem = styled.span`
  display: flex;
  align-items: center;
  gap: 4px;
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