import styled from "styled-components";

export const PageHeader = styled.div`
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(3)};
  margin-bottom: ${({ theme }) => theme.space(4)};
  padding-bottom: ${({ theme }) => theme.space(3)};
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
`;

export const AvatarLarge = styled.img`
  width: 96px;
  height: 96px;
  border-radius: 50%;
  object-fit: cover;
  border: 3px solid ${({ theme }) => theme.colors.border};
  flex-shrink: 0;
`;

export const AvatarPlaceholderLarge = styled.div`
  width: 96px;
  height: 96px;
  border-radius: 50%;
  background: ${({ theme }) => theme.colors.accent};
  color: white;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 2.5rem;
  font-weight: 700;
  border: 3px solid ${({ theme }) => theme.colors.border};
  flex-shrink: 0;
`;

export const UserInfo = styled.div`
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(0.5)};
  flex: 1;
`;

export const UserName = styled.h2`
  font-size: 1.4rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
  margin: 0;
`;

export const UserMeta = styled.p`
  font-size: 0.875rem;
  color: ${({ theme }) => theme.colors.muted};
  margin: 0;
`;

export const StarsRow = styled.div`
  display: flex;
  align-items: center;
  gap: 2px;
  margin-top: ${({ theme }) => theme.space(0.5)};
`;

export const Star = styled.span<{ $filled: boolean }>`
  font-size: 1.1rem;
  color: ${({ $filled }) => ($filled ? "#f59e0b" : "#4b5563")};
`;

export const Section = styled.section`
  margin-bottom: ${({ theme }) => theme.space(4)};
`;

export const SectionTitle = styled.h3`
  font-size: 1rem;
  font-weight: 600;
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: ${({ theme }) => theme.space(2)};
  text-transform: uppercase;
  letter-spacing: 0.05em;
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.muted};
`;

export const StatRow = styled.div`
  display: flex;
  gap: ${({ theme }) => theme.space(2)};
  flex-wrap: wrap;
`;

export const StatItem = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  padding: ${({ theme }) => theme.space(2)} ${({ theme }) => theme.space(3)};
  min-width: 100px;
  text-align: center;
`;

export const StatNum = styled.p`
  font-size: 1.5rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.primary};
  margin: 0 0 4px;
`;

export const StatTxt = styled.p`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.muted};
  margin: 0;
`;

export const ReviewCard = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md};
  padding: ${({ theme }) => theme.space(2)};
  margin-bottom: ${({ theme }) => theme.space(1.5)};
`;

export const ReviewBody = styled.p`
  font-size: 0.875rem;
  color: ${({ theme }) => theme.colors.text};
  margin: ${({ theme }) => theme.space(1)} 0 0;
`;

export const ReviewMeta = styled.p`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.muted};
  margin: ${({ theme }) => theme.space(0.5)} 0 0;
`;

export const CenterLoader = styled.div`
  display: flex;
  justify-content: center;
  padding: ${({ theme }) => theme.space(6)};
`;

export const EmptyState = styled.div`
  text-align: center;
  padding: ${({ theme }) => theme.space(4)};
  color: ${({ theme }) => theme.colors.muted};
`;
