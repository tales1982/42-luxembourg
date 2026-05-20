import type { PropsWithChildren } from "react";
import { useNavigate, Link } from "@tanstack/react-router";
import { useTranslation } from "react-i18next";
import {
  PageWrapper,
  Nav,
  NavLogo,
  NavActions,
  LangSelector,
  NavBtn,
  FooterSection,
  FooterLogo,
  FooterText,
  FooterLinks,
  FooterLink,
} from "../../app/routes/index.styled";

interface PublicLayoutProps extends PropsWithChildren {
  showFooterLinks?: boolean;
}

export function PublicLayout({ children, showFooterLinks = false }: PublicLayoutProps) {
  const { t, i18n } = useTranslation();
  const navigate = useNavigate();

  return (
    <PageWrapper style={{ display: "flex", flexDirection: "column" }}>
      <Nav>
        <Link to="/" style={{ textDecoration: "none" }}>
          <NavLogo>Transcendence</NavLogo>
        </Link>
        <NavActions>
          <LangSelector
            value={i18n.language}
            onChange={(e) => i18n.changeLanguage(e.target.value)}
          >
            <option value="pt">PT</option>
            <option value="en">EN</option>
            <option value="fr">FR</option>
          </LangSelector>
          <NavBtn onClick={() => navigate({ to: "/login" })}>
            {t("auth.login")}
          </NavBtn>
          <NavBtn $primary onClick={() => navigate({ to: "/register" })}>
            {t("auth.register")}
          </NavBtn>
        </NavActions>
      </Nav>

      <div style={{ flex: 1 }}>
        {children}
      </div>

      <FooterSection>
        <FooterLogo>Transcendence</FooterLogo>
        <FooterText>42 Luxembourg</FooterText>
        <FooterText>
          Tales &middot; Joao &middot; Andre &middot; Sandro &middot; Fabio
        </FooterText>
        {showFooterLinks && (
          <FooterLinks>
            <FooterLink as={Link} to="/terms">{t("nav.terms")}</FooterLink>
            <FooterLink as={Link} to="/privacy">{t("nav.privacy")}</FooterLink>
          </FooterLinks>
        )}
      </FooterSection>
    </PageWrapper>
  );
}
