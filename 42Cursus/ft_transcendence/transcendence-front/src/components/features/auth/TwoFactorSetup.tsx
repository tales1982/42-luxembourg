import { useState } from "react";
import { useTranslation } from "react-i18next";
import { authApi } from "../../../lib/api/auth";
import { Button } from "../../ui/Button";
import { Input, Label, FormGroup } from "../../ui/Input";
import styled from "styled-components";

const Section = styled.div`
  padding: 1.5rem;
  border: 1px solid var(--color-border, #2a3040);
  border-radius: 12px;
  background: var(--color-surface, #131b2e);
`;

const StatusBadge = styled.span<{ $enabled: boolean }>`
  display: inline-block;
  padding: 0.2rem 0.7rem;
  border-radius: 20px;
  font-size: 0.78rem;
  font-weight: 600;
  background: ${(p) => (p.$enabled ? "rgba(52,211,153,0.15)" : "rgba(100,116,139,0.15)")};
  color: ${(p) => (p.$enabled ? "#34d399" : "#94a3b8")};
  margin-left: 0.75rem;
`;

const QrImage = styled.img`
  display: block;
  margin: 1rem auto;
  border-radius: 8px;
  border: 4px solid #fff;
  width: 180px;
  height: 180px;
`;

const SecretBox = styled.div`
  background: rgba(0, 0, 0, 0.3);
  border-radius: 6px;
  padding: 0.5rem 0.75rem;
  font-family: monospace;
  font-size: 0.8rem;
  letter-spacing: 0.05em;
  word-break: break-all;
  margin: 0.5rem 0 1rem;
  color: #94a3b8;
`;

const ErrorMsg = styled.p`
  color: #f87171;
  font-size: 0.82rem;
  margin: 0.25rem 0;
`;

const SuccessMsg = styled.p`
  color: #34d399;
  font-size: 0.82rem;
  margin: 0.25rem 0;
`;

const Row = styled.div`
  display: flex;
  gap: 0.75rem;
  margin-top: 1rem;
`;

type Props = { enabled: boolean; onToggle: () => void };

export function TwoFactorSetup({ enabled, onToggle }: Props) {
  const { t } = useTranslation();

  const [step, setStep] = useState<"idle" | "setup" | "disable">("idle");
  const [qrCode, setQrCode] = useState<string>("");
  const [secret, setSecret] = useState<string>("");
  const [code, setCode] = useState("");
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [success, setSuccess] = useState<string | null>(null);

  async function startSetup() {
    setError(null);
    setLoading(true);
    try {
      const res = await authApi.setup2fa();
      setQrCode(res.qrCodeBase64);
      setSecret(res.secret);
      setStep("setup");
    } catch {
      setError(t("twoFactor.verifyError"));
    } finally {
      setLoading(false);
    }
  }

  async function confirmEnable() {
    setError(null);
    setLoading(true);
    try {
      await authApi.enable2fa(code);
      setSuccess(t("twoFactor.enableSuccess"));
      setStep("idle");
      setCode("");
      onToggle();
    } catch {
      setError(t("twoFactor.verifyError"));
    } finally {
      setLoading(false);
    }
  }

  async function confirmDisable() {
    setError(null);
    setLoading(true);
    try {
      await authApi.disable2fa(code);
      setSuccess(t("twoFactor.disableSuccess"));
      setStep("idle");
      setCode("");
      onToggle();
    } catch {
      setError(t("twoFactor.verifyError"));
    } finally {
      setLoading(false);
    }
  }

  return (
    <Section>
      <div style={{ display: "flex", alignItems: "center", marginBottom: "1rem" }}>
        <strong>{t("twoFactor.title")}</strong>
        <StatusBadge $enabled={enabled}>
          {enabled ? t("twoFactor.enabled") : t("twoFactor.disabled")}
        </StatusBadge>
      </div>

      {success && <SuccessMsg>{success}</SuccessMsg>}

      {/* ── Idle state ── */}
      {step === "idle" && !enabled && (
        <Button onClick={startSetup} disabled={loading}>
          {loading ? t("common.loading") : t("twoFactor.enable")}
        </Button>
      )}

      {step === "idle" && enabled && (
        <Button $variant="secondary" onClick={() => { setStep("disable"); setError(null); }}>
          {t("twoFactor.disable")}
        </Button>
      )}

      {/* ── Setup step: show QR ── */}
      {step === "setup" && (
        <>
          <p style={{ fontSize: "0.88rem", color: "#94a3b8" }}>{t("twoFactor.scanQr")}</p>
          {qrCode && <QrImage src={`data:image/png;base64,${qrCode}`} alt="QR Code 2FA" />}
          <p style={{ fontSize: "0.8rem", color: "#64748b" }}>{t("twoFactor.manualEntry")}</p>
          <SecretBox>{secret}</SecretBox>
          <FormGroup>
            <Label>{t("twoFactor.enterCode")}</Label>
            <Input
              type="text"
              inputMode="numeric"
              pattern="[0-9]{6}"
              maxLength={6}
              value={code}
              onChange={(e) => setCode(e.target.value.replace(/\D/g, ""))}
              placeholder="000000"
              autoFocus
            />
          </FormGroup>
          {error && <ErrorMsg>{error}</ErrorMsg>}
          <Row>
            <Button onClick={confirmEnable} disabled={loading || code.length !== 6}>
              {loading ? t("common.loading") : t("twoFactor.verify")}
            </Button>
            <Button $variant="secondary" onClick={() => { setStep("idle"); setCode(""); setError(null); }}>
              {t("common.cancel")}
            </Button>
          </Row>
        </>
      )}

      {/* ── Disable step ── */}
      {step === "disable" && (
        <>
          <FormGroup>
            <Label>{t("twoFactor.enterCode")}</Label>
            <Input
              type="text"
              inputMode="numeric"
              pattern="[0-9]{6}"
              maxLength={6}
              value={code}
              onChange={(e) => setCode(e.target.value.replace(/\D/g, ""))}
              placeholder="000000"
              autoFocus
            />
          </FormGroup>
          {error && <ErrorMsg>{error}</ErrorMsg>}
          <Row>
            <Button onClick={confirmDisable} disabled={loading || code.length !== 6}>
              {loading ? t("common.loading") : t("twoFactor.disable")}
            </Button>
            <Button $variant="secondary" onClick={() => { setStep("idle"); setCode(""); setError(null); }}>
              {t("common.cancel")}
            </Button>
          </Row>
        </>
      )}
    </Section>
  );
}
