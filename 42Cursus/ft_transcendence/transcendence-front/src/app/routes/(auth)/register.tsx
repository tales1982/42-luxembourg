import { createFileRoute, useNavigate} from "@tanstack/react-router";
import { useState } from "react";
import { useTranslation } from "react-i18next";
import { Input, Label, FormGroup } from "../../../components/ui/Input";
import { Button } from "../../../components/ui/Button";
import { register } from "../../../lib/api/auth";
import { useAppDispatch } from "../../../store/hooks";
import { setCredentials } from "../../../store/slices/auth.slice";
import { PageWrapper, LangRow, LangBtn, LogoSection, Logo, Subtitle, SuccessMsg, Form, ErrorMsg, BottomText, AccentLink, TermsBox, TermsTitle, TermsText, CheckboxRow, CheckboxInput, InlineError } from "./register.styled";
import { RegCard } from "./register.styled";

export const Route = createFileRoute("/(auth)/register")({
  component: RegisterPage,
});



function RegisterPage() {
  const { t, i18n } = useTranslation();
  const dispatch = useAppDispatch();
  const navigate = useNavigate();

  const [displayName, setDisplayName] = useState("");
  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [confirmPassword, setConfirmPassword] = useState("");
  const [acceptedTerms, setAcceptedTerms] = useState(false);
  const [termsError, setTermsError] = useState<string | null>(null);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [success, setSuccess] = useState(false);

  async function onSubmit(e: React.FormEvent) {
    e.preventDefault();
    setError(null);
    setTermsError(null);
    setSuccess(false);

    if (password !== confirmPassword) {
      setError(t("auth.passwordMismatch"));
      return;
    }
    if (!acceptedTerms) {
      setTermsError(t("auth.termsRequired"));
      return;
    }

    setLoading(true);
    try {
      const res = await register({ email, password, displayName: displayName || undefined });
      dispatch(setCredentials(res));
      setSuccess(true);
      setTimeout(() => navigate({ to: "/marketplace" }), 1500);
    } catch (err: unknown) {
      const message = err instanceof Error ? err.message : t("auth.registerError");
      setError(message);
    } finally {
      setLoading(false);
    }
  }

  return (
    <PageWrapper>
      <RegCard>
        <LangRow>
          <LangBtn $active={i18n.language === "pt"} onClick={() => i18n.changeLanguage("pt")}>PT</LangBtn>
          <LangBtn $active={i18n.language === "en"} onClick={() => i18n.changeLanguage("en")}>EN</LangBtn>
          <LangBtn $active={i18n.language === "fr"} onClick={() => i18n.changeLanguage("fr")}>FR</LangBtn>
        </LangRow>

        <LogoSection>
          <Logo>{t("app.title")}</Logo>
          <Subtitle>{t("app.subtitle")}</Subtitle>
        </LogoSection>

        {success ? (
          <SuccessMsg>{t("auth.registerSuccess")}</SuccessMsg>
        ) : (
          <Form onSubmit={onSubmit}>
            <FormGroup>
              <Label>{t("auth.displayName")}</Label>
              <Input
                value={displayName}
                onChange={(e) => setDisplayName(e.target.value)}
                placeholder={t("auth.displayNamePlaceholder")}
              />
            </FormGroup>

            <FormGroup>
              <Label>{t("auth.email")}</Label>
              <Input
                type="email"
                value={email}
                onChange={(e) => setEmail(e.target.value)}
                placeholder="you@example.com"
                required
              />
            </FormGroup>

            <FormGroup>
              <Label>{t("auth.password")}</Label>
              <Input
                type="password"
                value={password}
                onChange={(e) => setPassword(e.target.value)}
                placeholder="********"
                required
                minLength={6}
              />
            </FormGroup>

            <FormGroup>
              <Label>{t("auth.confirmPassword")}</Label>
              <Input
                type="password"
                value={confirmPassword}
                onChange={(e) => setConfirmPassword(e.target.value)}
                placeholder="********"
                required
              />
            </FormGroup>

            <TermsBox>
              <TermsTitle>{t("auth.termsTitle")}</TermsTitle>
              <TermsText>{t("auth.termsText")}</TermsText>
              <CheckboxRow>
                <CheckboxInput
                  type="checkbox"
                  checked={acceptedTerms}
                  onChange={(e) => setAcceptedTerms(e.target.checked)}
                />
                <span>
                  {t("auth.termsAcceptPre")}{" "}
                  <AccentLink to="/terms">{t("auth.termsOfUse")}</AccentLink>
                  {" "}{t("auth.termsAnd")}{" "}
                  <AccentLink to="/privacy">{t("auth.termsPrivacy")}</AccentLink>.
                </span>
              </CheckboxRow>
              {termsError && <InlineError>{termsError}</InlineError>}
            </TermsBox>

            {error && <ErrorMsg>{error}</ErrorMsg>}

            <Button $fullWidth disabled={loading || !acceptedTerms}>
              {loading ? t("auth.loading") : t("auth.register")}
            </Button>
          </Form>
        )}

        <BottomText>
          {t("auth.hasAccount")}{" "}
          <AccentLink to="/login">{t("auth.signIn")}</AccentLink>
        </BottomText>
      </RegCard>
    </PageWrapper>
  );
}
