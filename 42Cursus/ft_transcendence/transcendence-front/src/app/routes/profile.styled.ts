import styled from "styled-components";
import { Select } from "../../components/ui/Select";

export const Title = styled.h2`
  font-size: 1.5rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const FormCard = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: ${({ theme }) => theme.space(3)};
  max-width: 640px;
`;

export const Grid = styled.div`
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: ${({ theme }) => theme.space(2)};

  @media (max-width: 600px) {
    grid-template-columns: 1fr;
  }
`;

export const FullWidth = styled.div`
  grid-column: 1 / -1;
`;

export const InfoBox = styled.div`
  margin-top: ${({ theme }) => theme.space(3)};
  padding: ${({ theme }) => theme.space(2)};
  background: ${({ theme }) => theme.colors.card};
  border-radius: ${({ theme }) => theme.radius.md};
`;

export const InfoText = styled.p`
  font-size: 0.825rem;
  color: ${({ theme }) => theme.colors.muted};
  line-height: 1.5;
`;

export const Footer = styled.div`
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-top: ${({ theme }) => theme.space(3)};
`;

export const CenterLoader = styled.div`
  display: flex;
  justify-content: center;
  padding: ${({ theme }) => theme.space(6)};
`;

export const StyledSelect = styled(Select)`
  width: 100%;
`;

export const Required = styled.span`
  color: ${({ theme }) => theme.colors.danger};
`;

export const AvatarSection = styled.div`
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(3)};
  margin-bottom: ${({ theme }) => theme.space(3)};
  padding-bottom: ${({ theme }) => theme.space(3)};
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
`;

export const AvatarWrapper = styled.div`
  position: relative;
  cursor: pointer;
  &:hover > div {
    opacity: 1;
  }
`;

export const AvatarImage = styled.img`
  width: 80px;
  height: 80px;
  border-radius: 50%;
  object-fit: cover;
  border: 2px solid ${({ theme }) => theme.colors.border};
`;

export const AvatarPlaceholder = styled.div`
  width: 80px;
  height: 80px;
  border-radius: 50%;
  background: ${({ theme }) => theme.colors.accent};
  color: white;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 1.75rem;
  font-weight: 700;
  border: 2px solid ${({ theme }) => theme.colors.border};
`;

export const AvatarOverlay = styled.div`
  position: absolute;
  inset: 0;
  border-radius: 50%;
  background: rgba(0, 0, 0, 0.5);
  display: flex;
  align-items: center;
  justify-content: center;
  opacity: 0;
  transition: opacity 0.2s;
  color: white;
  font-size: 0.7rem;
  font-weight: 600;
  text-align: center;
  padding: 4px;
`;

export const AvatarInfo = styled.div`
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(1)};
`;

export const AvatarHint = styled.p`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.muted};
`;