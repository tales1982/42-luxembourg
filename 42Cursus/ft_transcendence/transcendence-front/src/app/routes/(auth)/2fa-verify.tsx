import { createFileRoute, useNavigate } from "@tanstack/react-router";
import { useState } from "react";
import { useTranslation } from "react-i18next";
import { useAppDispatch, useAppSelector } from "../../../store/hooks";
import { setCredentials, logout } from "../../../store/slices/auth.slice";
import { authApi } from "../../../lib/api/auth";
import { Input, Label, FormGroup } from "../../../components/ui/Input";
import { Button } from "../../../components/ui/Button";
import {
  PageWrapper,
  LoginCard,
  LogoSection,
  Logo,
  Subtitle,
  Form,
  ErrorMsg,
  BottomText,
  AccentLink,
} from "./login.styled";

export const Route = createFileRoute("/(auth)/2fa-verify")({
  component: TwoFactorVerifyPage,
});

function TwoFactorVerifyPage() {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const navigate = useNavigate();

  const challengeToken = useAppSelector((s) => s.auth.challengeToken);
  const pendingEmail = useAppSelector((s) => s.auth.pendingEmail);
  const authStatus = useAppSelector((s) => s.auth.status);

  const [code, setCode] = useState("");
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  // Only redirect to login if we don't have a challenge token AND we're not
  // already authenticated (setCredentials clears challengeToken on success).
  if (authStatus === "guest") {
    navigate({ to: "/login", replace: true });
    return null;
  }

  async function onSubmit(e: React.FormEvent) {
    e.preventDefault();
    setError(null);
    setLoading(true);
    try {
      const res = await authApi.verify2fa({ challengeToken: challengeToken!, code });
      dispatch(setCredentials(res));
      navigate({ to: "/marketplace" });
    } catch {
      setError(t("twoFactor.verifyError"));
    } finally {
      setLoading(false);
    }
  }

  function handleCancel() {
    dispatch(logout());
    navigate({ to: "/login" });
  }

  return (
    <PageWrapper>
      <LoginCard>
        <LogoSection>
          <Logo>{t("app.title")}</Logo>
          <Subtitle>{t("twoFactor.title")}</Subtitle>
        </LogoSection>

        <p style={{ textAlign: "center", marginBottom: "1rem", color: "var(--color-muted, #aaa)", fontSize: "0.9rem" }}>
          {t("twoFactor.loginChallenge")}
          {pendingEmail && <><br /><strong>{pendingEmail}</strong></>}
        </p>

        <Form onSubmit={onSubmit}>
          <FormGroup>
            <Label>{t("twoFactor.code")}</Label>
            <Input
              type="text"
              inputMode="numeric"
              pattern="[0-9]{6}"
              maxLength={6}
              value={code}
              onChange={(e) => setCode(e.target.value.replace(/\D/g, ""))}
              placeholder="000000"
              autoFocus
              required
            />
          </FormGroup>

          {error && <ErrorMsg>{error}</ErrorMsg>}

          <Button $fullWidth disabled={loading || code.length !== 6}>
            {loading ? t("common.loading") : t("twoFactor.verifyLogin")}
          </Button>
        </Form>

        <BottomText>
          <AccentLink to="/login" onClick={handleCancel}>{t("auth.backToLogin")}</AccentLink>
        </BottomText>
      </LoginCard>
    </PageWrapper>
  );
}
