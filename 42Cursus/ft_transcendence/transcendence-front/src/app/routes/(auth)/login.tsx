import { createFileRoute, useNavigate} from "@tanstack/react-router";
import { useState } from "react";
import { useTranslation } from "react-i18next";
import { Input, Label, FormGroup } from "../../../components/ui/Input";
import { Button } from "../../../components/ui/Button";
import { login } from "../../../lib/api/auth";
import { useAppDispatch } from "../../../store/hooks";
import { setCredentials, set2faChallenge } from "../../../store/slices/auth.slice";
import { PageWrapper, LoginCard, LangRow, LangBtn, LogoSection, Logo, Subtitle, SuccessMsg, Form, ErrorMsg, BottomText, AccentLink } from "./login.styled";

export const Route = createFileRoute("/(auth)/login")({
  component: LoginPage,
});



function LoginPage() {
  const { t, i18n } = useTranslation();
  const dispatch = useAppDispatch();
  const navigate = useNavigate();

  const [email, setEmail] = useState("");
  const [password, setPassword] = useState("");
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [success, setSuccess] = useState(false);

  async function onSubmit(e: React.FormEvent) {
    e.preventDefault();
    setError(null);
    setLoading(true);
    try {
      const res = await login({ email, password });
      if (res.requiresTwoFactor) {
        dispatch(set2faChallenge({ challengeToken: res.challengeToken, email }));
        navigate({ to: "/2fa-verify" });
        return;
      }
      dispatch(setCredentials(res));
      setSuccess(true);
      setTimeout(() => navigate({ to: "/marketplace" }), 1500);
    } catch (err: unknown) {
      const message = err instanceof Error ? err.message : t("auth.loginError");
      setError(message);
    } finally {
      setLoading(false);
    }
  }

  return (
    <PageWrapper>
      <LoginCard>
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
          <SuccessMsg>{t("auth.loginSuccess")}</SuccessMsg>
        ) : (
          <Form onSubmit={onSubmit}>
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
              />
            </FormGroup>

            {error && <ErrorMsg>{error}</ErrorMsg>}

            <Button $fullWidth disabled={loading}>
              {loading ? t("auth.loading") : t("auth.login")}
            </Button>
          </Form>
        )}

        <BottomText>
          {t("auth.noAccount")}{" "}
          <AccentLink to="/register">{t("auth.createAccount")}</AccentLink>
        </BottomText>
      </LoginCard>
    </PageWrapper>
  );
}
