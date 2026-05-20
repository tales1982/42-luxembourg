import styled, { keyframes } from "styled-components";

/* ── Animations ── */
export const fadeInUp = keyframes`
  from { opacity: 0; transform: translateY(30px); }
  to { opacity: 1; transform: translateY(0); }
`;

/* ── Page Wrapper ── */
export const PageWrapper = styled.div`
  min-height: 100vh;
  background-color: #0b1a2b;
  background-image:
    linear-gradient(rgba(11, 26, 43, 0.75), rgba(11, 26, 43, 0.85)),
    url("/bg.jpg");
  background-size: cover;
  background-position: 50% 0%;
  background-repeat: no-repeat;
`;

/* ── Navbar ── */
export const Nav = styled.nav`
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  z-index: 50;
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 0 ${({ theme }) => theme.space(4)};
  height: 64px;
  background: rgba(11, 26, 43, 0.92);
  backdrop-filter: blur(12px);
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
`;

export const NavLogo = styled.span`
  font-size: 1.5rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.primary};
`;

export const NavActions = styled.div`
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(1.5)};
`;

export const NavBtn = styled.button<{ $primary?: boolean }>`
  padding: ${({ theme }) => `${theme.space(1)} ${theme.space(2.5)}`};
  border-radius: ${({ theme }) => theme.radius.md};
  font-weight: 600;
  font-size: 0.9rem;
  cursor: pointer;
  transition: all 200ms ease;
  border: ${({ $primary, theme }) =>
    $primary ? "none" : `1px solid ${theme.colors.border}`};
  background: ${({ $primary, theme }) =>
    $primary ? theme.colors.primary : "transparent"};
  color: ${({ $primary, theme }) =>
    $primary ? theme.colors.bg : theme.colors.text};

  &:hover {
    background: ${({ $primary, theme }) =>
      $primary ? theme.colors.primaryHover : theme.colors.card};
    box-shadow: ${({ $primary, theme }) =>
      $primary ? theme.shadow.glow : "none"};
  }
`;

export const LangSelector = styled.select`
  background: transparent;
  color: ${({ theme }) => theme.colors.textSecondary};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.sm};
  padding: 4px 8px;
  font-size: 0.8rem;
  cursor: pointer;

  option {
    background: ${({ theme }) => theme.colors.bg};
    color: ${({ theme }) => theme.colors.text};
  }
`;

/* ── Hero ── */
export const HeroSection = styled.section`
  min-height: 100vh;
  display: flex;
  align-items: center;
  justify-content: center;
  text-align: center;
  padding: ${({ theme }) => `${theme.space(12)} ${theme.space(3)}`};
  background: radial-gradient(
    ellipse at 50% 0%,
    rgba(52, 211, 153, 0.08) 0%,
    transparent 60%
  );
`;

export const HeroContent = styled.div`
  max-width: 720px;
  animation: ${fadeInUp} 0.8s ease-out;
`;

export const HeroTitle = styled.h1`
  font-size: clamp(2rem, 5vw, 3.5rem);
  font-weight: 800;
  color: ${({ theme }) => theme.colors.text};
  line-height: 1.15;
  margin-bottom: ${({ theme }) => theme.space(3)};

  span {
    color: ${({ theme }) => theme.colors.primary};
  }
`;

export const HeroSubtitle = styled.p`
  font-size: clamp(1rem, 2.5vw, 1.25rem);
  color: ${({ theme }) => theme.colors.textSecondary};
  line-height: 1.6;
  margin-bottom: ${({ theme }) => theme.space(4)};
`;

export const HeroCTA = styled.button`
  padding: ${({ theme }) => `${theme.space(2)} ${theme.space(5)}`};
  background: ${({ theme }) => theme.colors.primary};
  color: ${({ theme }) => theme.colors.bg};
  font-weight: 700;
  font-size: 1.1rem;
  border: none;
  border-radius: ${({ theme }) => theme.radius.md};
  cursor: pointer;
  transition: all 250ms ease;

  &:hover {
    background: ${({ theme }) => theme.colors.primaryHover};
    box-shadow: ${({ theme }) => theme.shadow.glow};
    transform: translateY(-2px);
  }
`;

/* ── How it works ── */
export const SectionWrapper = styled.section`
  padding: ${({ theme }) => `${theme.space(10)} ${theme.space(3)}`};
  max-width: 1100px;
  margin: 0 auto;
`;

export const SectionTitle = styled.h2`
  font-size: clamp(1.5rem, 3vw, 2rem);
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
  text-align: center;
  margin-bottom: ${({ theme }) => theme.space(6)};

  span {
    color: ${({ theme }) => theme.colors.primary};
  }
`;

export const StepsGrid = styled.div`
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
  gap: ${({ theme }) => theme.space(4)};
`;

export const StepCard = styled.div`
  text-align: center;
  padding: ${({ theme }) => theme.space(4)};
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  transition: all 250ms ease;

  &:hover {
    border-color: ${({ theme }) => theme.colors.borderHover};
    transform: translateY(-4px);
    box-shadow: ${({ theme }) => theme.shadow.lg};
  }
`;

export const StepIcon = styled.div`
  width: 64px;
  height: 64px;
  margin: 0 auto ${({ theme }) => theme.space(2)};
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 2rem;
  background: rgba(52, 211, 153, 0.1);
  border-radius: 50%;
`;

export const StepTitle = styled.h3`
  font-size: 1.1rem;
  font-weight: 600;
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: ${({ theme }) => theme.space(1)};
`;

export const StepDesc = styled.p`
  font-size: 0.9rem;
  color: ${({ theme }) => theme.colors.textSecondary};
  line-height: 1.5;
`;

/* ── Tasks Section ── */
export const TasksSectionBg = styled.section`
  padding: ${({ theme }) => `${theme.space(10)} ${theme.space(3)}`};
  background: ${({ theme }) => theme.colors.bgSecondary};
`;

export const TasksContainer = styled.div`
  max-width: 1100px;
  margin: 0 auto;
`;

export const TasksGrid = styled.div`
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
  gap: ${({ theme }) => theme.space(3)};

  @media (max-width: 768px) {
    grid-template-columns: 1fr;
  }
`;

export const TaskCard = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: ${({ theme }) => theme.space(3)};
  transition: all 200ms ease;
  cursor: pointer;

  &:hover {
    border-color: ${({ theme }) => theme.colors.primaryHover};
    box-shadow: ${({ theme }) => theme.shadow.md};
    transform: translateY(-2px);
  }
`;

export const CardHeader = styled.div`
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
  margin-bottom: ${({ theme }) => theme.space(1.5)};
`;

export const CategoryBadge = styled.span`
  padding: ${({ theme }) => `${theme.space(0.5)} ${theme.space(1.5)}`};
  background: rgba(52, 211, 153, 0.1);
  border-radius: 9999px;
  font-size: 0.78rem;
  color: ${({ theme }) => theme.colors.primary};
  font-weight: 500;
`;

export const RewardBadge = styled.span`
  font-size: 1.1rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.primary};
`;

export const CardBottom = styled.div`
  display: flex;
  justify-content: space-between;
  font-size: 0.78rem;
  color: ${({ theme }) => theme.colors.muted};
`;

export const OpenBadge = styled.span`
  display: inline-block;
  padding: ${({ theme }) => `${theme.space(0.25)} ${theme.space(1)}`};
  background: rgba(52, 211, 153, 0.15);
  color: ${({ theme }) => theme.colors.primary};
  border-radius: ${({ theme }) => theme.radius.sm};
  font-size: 0.72rem;
  font-weight: 600;
  text-transform: uppercase;
`;

export const FilterRow = styled.div`
  display: flex;
  flex-wrap: wrap;
  align-items: center;
  justify-content: center;
  gap: ${({ theme }) => theme.space(1)};
  margin-bottom: ${({ theme }) => theme.space(4)};
`;

export const FilterChip = styled.button<{ $active?: boolean }>`
  padding: ${({ theme }) => `${theme.space(0.75)} ${theme.space(2)}`};
  border-radius: 9999px;
  font-size: 0.85rem;
  font-weight: 500;
  cursor: pointer;
  transition: all 150ms ease;
  border: 1px solid
    ${({ $active, theme }) =>
      $active ? theme.colors.primary : theme.colors.border};
  background: ${({ $active }) =>
    $active ? "rgba(52, 211, 153, 0.15)" : "transparent"};
  color: ${({ $active, theme }) =>
    $active ? theme.colors.primary : theme.colors.textSecondary};

  &:hover {
    border-color: ${({ theme }) => theme.colors.primary};
    color: ${({ theme }) => theme.colors.primary};
  }
`;

export const EmptyState = styled.div`
  text-align: center;
  padding: ${({ theme }) => theme.space(6)};
  color: ${({ theme }) => theme.colors.muted};
  font-size: 1rem;
`;

export const LoadingWrapper = styled.div`
  text-align: center;
  padding: ${({ theme }) => theme.space(6)};
  color: ${({ theme }) => theme.colors.muted};
`;

/* ── Task Detail Modal ── */
export const ModalOverlay = styled.div`
  position: fixed;
  inset: 0;
  z-index: 100;
  background: rgba(0, 0, 0, 0.6);
  display: flex;
  align-items: center;
  justify-content: center;
  padding: ${({ theme }) => theme.space(2)};
`;

export const ModalCard = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: ${({ theme }) => theme.space(4)};
  max-width: 560px;
  width: 100%;
  max-height: 85vh;
  overflow-y: auto;
  position: relative;
`;

export const ModalClose = styled.button`
  position: absolute;
  top: ${({ theme }) => theme.space(2)};
  right: ${({ theme }) => theme.space(2)};
  background: transparent;
  border: none;
  color: ${({ theme }) => theme.colors.muted};
  font-size: 1.5rem;
  cursor: pointer;
  line-height: 1;

  &:hover {
    color: ${({ theme }) => theme.colors.text};
  }
`;

export const ModalTitle = styled.h3`
  font-size: 1.25rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: ${({ theme }) => theme.space(2)};
  padding-right: ${({ theme }) => theme.space(4)};
`;

export const ModalDesc = styled.p`
  color: ${({ theme }) => theme.colors.textSecondary};
  font-size: 0.95rem;
  line-height: 1.6;
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const ModalGrid = styled.div`
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: ${({ theme }) => theme.space(2)};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const ModalLabel = styled.span`
  font-size: 0.78rem;
  font-weight: 500;
  color: ${({ theme }) => theme.colors.muted};
  display: block;
  margin-bottom: 4px;
`;

export const ModalValue = styled.span`
  font-size: 0.95rem;
  color: ${({ theme }) => theme.colors.text};
`;

export const ModalReward = styled.span`
  font-size: 1.25rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.primary};
`;

export const ModalLoginBtn = styled.button`
  width: 100%;
  padding: ${({ theme }) => theme.space(1.5)};
  background: ${({ theme }) => theme.colors.primary};
  color: ${({ theme }) => theme.colors.bg};
  font-weight: 600;
  font-size: 1rem;
  border: none;
  border-radius: ${({ theme }) => theme.radius.md};
  cursor: pointer;
  transition: all 200ms ease;
  margin-top: ${({ theme }) => theme.space(2)};

  &:hover {
    background: ${({ theme }) => theme.colors.primaryHover};
    box-shadow: ${({ theme }) => theme.shadow.glow};
  }
`;

export const TagsRow = styled.div`
  display: flex;
  flex-wrap: wrap;
  gap: ${({ theme }) => theme.space(1)};
  margin-bottom: ${({ theme }) => theme.space(2)};
`;

export const TagChip = styled.span`
  padding: ${({ theme }) => `${theme.space(0.5)} ${theme.space(1.5)}`};
  background: ${({ theme }) => theme.colors.card};
  border-radius: 9999px;
  font-size: 0.8rem;
  color: ${({ theme }) => theme.colors.textSecondary};
`;

/* ── Footer ── */
export const FooterSection = styled.footer`
  padding: ${({ theme }) => `${theme.space(6)} ${theme.space(3)}`};
  text-align: center;
  border-top: 1px solid ${({ theme }) => theme.colors.border};
  background: ${({ theme }) => theme.colors.bg};
`;

export const FooterLogo = styled.p`
  font-size: 1.25rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.primary};
  margin-bottom: ${({ theme }) => theme.space(1)};
`;

export const FooterText = styled.p`
  font-size: 0.85rem;
  color: ${({ theme }) => theme.colors.muted};
  margin-bottom: ${({ theme }) => theme.space(0.5)};
`;

export const FooterLinks = styled.div`
  display: flex;
  align-items: center;
  justify-content: center;
  gap: ${({ theme }) => theme.space(3)};
  margin-top: ${({ theme }) => theme.space(2)};
`;

export const FooterLink = styled.a`
  font-size: 0.85rem;
  color: ${({ theme }) => theme.colors.textSecondary};
  text-decoration: none;
  transition: color 150ms ease;

  &:hover {
    color: ${({ theme }) => theme.colors.primary};
  }
`;
