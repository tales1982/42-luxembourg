import { createFileRoute, useNavigate } from "@tanstack/react-router";
import { useEffect, useRef, useState } from "react";
import { useTranslation } from "react-i18next";
import { Input, Label, FormGroup } from "../../components/ui/Input";
import { Button } from "../../components/ui/Button";
import { Spinner } from "../../components/ui/Loading";
import { showToast } from "../../components/ui/Toast";
import { useAppSelector, useAppDispatch } from "../../store/hooks";
import { logout } from "../../store/slices/auth.slice";
import { fetchProfile, saveProfile, setProfile } from "../../store/slices/profile.slice";
import {
  FormCard,
  Grid,
  Required,
  StyledSelect,
  FullWidth,
  InfoBox,
  InfoText,
  Footer,
  AvatarSection,
  AvatarWrapper,
  AvatarImage,
  AvatarPlaceholder,
  AvatarOverlay,
  AvatarInfo,
  AvatarHint,
} from "./profile.styled";
import { CenterLoader, Title } from "./taken.styled";
import { TwoFactorSetup } from "../../components/features/auth/TwoFactorSetup";
import { authApi } from "../../lib/api/auth";
import { profileApi } from "../../lib/api/profile";
import { api } from "../../lib/api/client";
import { env } from "../../config/env";

export const Route = createFileRoute("/profile")({
  component: ProfilePage,
});

function ProfilePage() {
  const { t } = useTranslation();
  const authUser = useAppSelector((s) => s.auth.user);
  const { profile, loading, saving } = useAppSelector((s) => s.profile);
  const dispatch = useAppDispatch();
  const navigate = useNavigate();
  const fileInputRef = useRef<HTMLInputElement>(null);

  const [fullName, setFullName] = useState("");
  const [country, setCountry] = useState("");
  const [phone, setPhone] = useState("");
  const [address, setAddress] = useState("");
  const [twoFactorEnabled, setTwoFactorEnabled] = useState(false);
  const [avatarUrl, setAvatarUrl] = useState<string | null>(null);
  const [uploadingAvatar, setUploadingAvatar] = useState(false);

  useEffect(() => {
    dispatch(fetchProfile());
    authApi.get2faStatus().then((r) => setTwoFactorEnabled(r.enabled)).catch(() => {});
  }, [dispatch]);

  useEffect(() => {
    if (profile) {
      setFullName(profile.fullName || "");
      setCountry(profile.country || "");
      setPhone(profile.phone || "");
      setAddress(profile.address || "");
      setAvatarUrl(profile.avatarUrl || null);
    }
  }, [profile]);

  async function handleAvatarChange(e: React.ChangeEvent<HTMLInputElement>) {
    const file = e.target.files?.[0];
    if (!file) return;
    setUploadingAvatar(true);
    try {
      const updated = await profileApi.uploadAvatar(file);
      setAvatarUrl(updated.avatarUrl || null);
      dispatch(setProfile(updated));
      showToast(t("profile.avatarUploaded"));
    } catch {
      showToast(t("profile.avatarError"), "error");
    } finally {
      setUploadingAvatar(false);
      if (fileInputRef.current) fileInputRef.current.value = "";
    }
  }

  // Resolve a relative /api/ URL to the full backend URL for <img> display
  function resolveUrl(url: string | null): string | null {
    if (!url) return null;
    if (url.startsWith("/")) return `${env.API_BASE_URL}${url}`;
    return url;
  }

  async function handleSubmit(e: { preventDefault(): void }) {
    e.preventDefault();
    const result = await dispatch(saveProfile({
      fullName: fullName || undefined,
      country,
      phone: phone || undefined,
      address: address || undefined,
      avatarUrl: avatarUrl || undefined,
    }));
    if (saveProfile.fulfilled.match(result)) {
      showToast(t("profile.saved"));
    } else {
      showToast(t("profile.saveError"), "error");
    }
  }

  async function handleExportData() {
    const res = await api.get("/api/profile/export", { responseType: "blob" });
    const url = URL.createObjectURL(res.data as Blob);
    const a = document.createElement("a");
    a.href = url;
    a.download = "my-data.json";
    a.click();
    URL.revokeObjectURL(url);
  }

  function handleLogout() {
    dispatch(logout());
    navigate({ to: "/" });
  }

  const initials = (authUser?.displayName || authUser?.email || "?")
    .charAt(0)
    .toUpperCase();

  if (loading) {
    return <CenterLoader><Spinner $size="lg" /></CenterLoader>;
  }

  return (
    <>
      <Title>{t("nav.profile")}</Title>

      <TwoFactorSetup
        enabled={twoFactorEnabled}
        onToggle={() => setTwoFactorEnabled((v) => !v)}
      />

      <FormCard style={{ marginTop: "1.5rem" }}>
        {/* ── Avatar ── */}
        <AvatarSection>
          <AvatarWrapper onClick={() => !uploadingAvatar && fileInputRef.current?.click()}>
            {avatarUrl ? (
              <AvatarImage src={resolveUrl(avatarUrl) ?? avatarUrl} alt={authUser?.displayName || "avatar"} />
            ) : (
              <AvatarPlaceholder>{initials}</AvatarPlaceholder>
            )}
            <AvatarOverlay>
              {uploadingAvatar ? <Spinner $size="sm" /> : t("profile.changeAvatar")}
            </AvatarOverlay>
          </AvatarWrapper>

          <AvatarInfo>
            <Label>{t("profile.avatar")}</Label>
            <AvatarHint>{t("profile.avatarHint")}</AvatarHint>
            <Button
              type="button"
              $variant="outline"
              disabled={uploadingAvatar}
              onClick={() => fileInputRef.current?.click()}
            >
              {uploadingAvatar ? <Spinner $size="sm" /> : t("profile.changeAvatar")}
            </Button>
          </AvatarInfo>

          <input
            ref={fileInputRef}
            type="file"
            accept="image/*"
            style={{ display: "none" }}
            onChange={handleAvatarChange}
          />
        </AvatarSection>

        {/* ── Form ── */}
        <form onSubmit={handleSubmit}>
          <Grid>
            <FormGroup>
              <Label>{t("profile.fullName")}</Label>
              <Input
                value={fullName}
                onChange={(e) => setFullName(e.target.value)}
              />
            </FormGroup>

            <FormGroup>
              <Label>{t("profile.email")}</Label>
              <Input
                value={authUser?.email || ""}
                readOnly
                style={{ opacity: 0.6 }}
              />
            </FormGroup>

            <FormGroup>
              <Label>{t("profile.country")} <Required>*</Required></Label>
              <StyledSelect
                value={country}
                onChange={(e) => setCountry(e.target.value)}
                required
              >
                <option value="">{t("profile.selectCountry")}</option>
                <option value="BR">Brasil</option>
                <option value="US">United States</option>
                <option value="UK">United Kingdom</option>
                <option value="CA">Canada</option>
                <option value="AU">Australia</option>
                <option value="FR">France</option>
                <option value="DE">Germany</option>
                <option value="PT">Portugal</option>
              </StyledSelect>
            </FormGroup>

            <FormGroup>
              <Label>{t("profile.phone")}</Label>
              <Input
                type="tel"
                value={phone}
                onChange={(e) => setPhone(e.target.value)}
              />
            </FormGroup>

            <FullWidth>
              <FormGroup>
                <Label>{t("profile.address")}</Label>
                <Input
                  value={address}
                  onChange={(e) => setAddress(e.target.value)}
                />
              </FormGroup>
            </FullWidth>
          </Grid>

          <InfoBox>
            <InfoText>{t("profile.infoNote")}</InfoText>
          </InfoBox>

          <Footer>
            <Button type="submit" disabled={saving}>
              {saving ? t("common.loading") : t("profile.save")}
            </Button>
            <div style={{ display: "flex", gap: "0.5rem" }}>
              <Button type="button" $variant="outline" onClick={handleExportData} title={t("profile.exportDataHint")}>
                ↓ {t("profile.exportData")}
              </Button>
              <Button type="button" $variant="danger" onClick={handleLogout}>
                {t("nav.logout")}
              </Button>
            </div>
          </Footer>
        </form>
      </FormCard>
    </>
  );
}
