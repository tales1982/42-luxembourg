import styled from "styled-components";

export const Title = styled.h2`
  font-size: 1.5rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const StatsGrid = styled.div`
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(140px, 1fr));
  gap: ${({ theme }) => theme.space(2)};
  margin-bottom: ${({ theme }) => theme.space(4)};
`;

export const StatCard = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: ${({ theme }) => theme.space(2.5)};
  text-align: center;
`;

export const StatNum = styled.p`
  font-size: 2rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.primary};
  margin: 0 0 4px;
  line-height: 1;
`;

export const StatLabel = styled.p`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.muted};
  margin: 0;
  text-transform: uppercase;
  letter-spacing: 0.04em;
`;

export const Section = styled.section`
  margin-bottom: ${({ theme }) => theme.space(4)};
`;

export const SectionTitle = styled.h3`
  font-size: 0.75rem;
  font-weight: 600;
  color: ${({ theme }) => theme.colors.muted};
  text-transform: uppercase;
  letter-spacing: 0.06em;
  margin-bottom: ${({ theme }) => theme.space(2)};
`;

export const BreakdownRow = styled.div`
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(1.5)};
  max-width: 480px;
`;

export const BreakdownItem = styled.div`
  display: flex;
  justify-content: space-between;
  align-items: center;
  font-size: 0.875rem;
  color: ${({ theme }) => theme.colors.text};
`;

export const BreakdownBar = styled.div<{ $pct: number; $color: string }>`
  height: 6px;
  border-radius: 99px;
  background: ${({ theme }) => theme.colors.border};
  margin-top: 4px;
  overflow: hidden;
  &::after {
    content: "";
    display: block;
    height: 100%;
    width: ${({ $pct }) => $pct}%;
    background: ${({ $color }) => $color};
    border-radius: 99px;
    transition: width 0.4s ease;
  }
`;

export const ZionBadge = styled.div`
  display: inline-flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(1)};
  background: rgba(52, 211, 153, 0.1);
  border: 1px solid ${({ theme }) => theme.colors.primary};
  color: ${({ theme }) => theme.colors.primary};
  border-radius: ${({ theme }) => theme.radius.md};
  padding: ${({ theme }) => theme.space(1)} ${({ theme }) => theme.space(2)};
  font-size: 1rem;
  font-weight: 700;
`;

export const CenterLoader = styled.div`
  display: flex;
  justify-content: center;
  padding: ${({ theme }) => theme.space(6)};
`;
