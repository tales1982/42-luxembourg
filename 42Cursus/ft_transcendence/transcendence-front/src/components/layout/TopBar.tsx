import { useRef, useEffect, useState } from "react";
import { useTranslation } from "react-i18next";
import { useNavigate } from "@tanstack/react-router";
import { useAppSelector, useAppDispatch } from "../../store/hooks";
import { logout } from "../../store/slices/auth.slice";
import { Flag } from "./LanguageDropdown.styled";
import { Row } from "./NavBar.styled";
import { Header, MobileMenuBtn, SearchWrapper, SearchIcon, SearchInput, Actions, LangWrapper, LangButton, ChevronDown, LangDropdown, LangOption, BalanceBox, CoinIcon, LogoutBtn, UserGreeting, UserAvatar } from "./TopBar.styled";
import type { TopBarProps } from "../../interfaces/TopBarProps.interface";
import { env } from "../../config/env";


/* ── Language data ── */

const LANGUAGES = [
  { code: "pt", label: "Português", flag: "\u{1F1E7}\u{1F1F7}" },
  { code: "en", label: "English", flag: "\u{1F1EC}\u{1F1E7}" },
  { code: "fr", label: "Français", flag: "\u{1F1EB}\u{1F1F7}" },
] as const;



export function TopBar({ onMenuToggle, searchValue, onSearchChange }: TopBarProps) {
  const { t, i18n } = useTranslation();
  const dispatch = useAppDispatch();
  const navigate = useNavigate();
  const account = useAppSelector((s) => s.payment.account);
  const user = useAppSelector((s) => s.auth.user);
  const profile = useAppSelector((s) => s.profile.profile);
  const initials = user?.displayName
    ? user.displayName.split(" ").map((n) => n[0]).slice(0, 2).join("").toUpperCase()
    : "?";
  const [langOpen, setLangOpen] = useState(false);
  const langRef = useRef<HTMLDivElement>(null);

  const balance = account?.availableBalance ?? 0;
  const currentLang = LANGUAGES.find((l) => l.code === i18n.language) ?? LANGUAGES[0];
  const avatarUrl = profile?.avatarUrl || null;

  function resolveUrl(url: string | null): string | null {
    if (!url) return null;
    if (url.startsWith("/")) return `${env.API_BASE_URL}${url}`;
    return url;
  }

  useEffect(() => {
    function handleClickOutside(e: MouseEvent) {
      if (langRef.current && !langRef.current.contains(e.target as Node)) {
        setLangOpen(false);
      }
    }
    document.addEventListener("mousedown", handleClickOutside);
    return () => document.removeEventListener("mousedown", handleClickOutside);
  }, []);

  const handleLanguageChange = (code: string) => {
    i18n.changeLanguage(code);
    localStorage.setItem("app-language", code);
    setLangOpen(false);
  };

  const handleLogout = () => {
    dispatch(logout());
    navigate({ to: "/" });
  };

  return (
    <Header>
      <Row>
        <MobileMenuBtn onClick={onMenuToggle}>&#9776;</MobileMenuBtn>

        <SearchWrapper>
          <SearchIcon>🔍</SearchIcon>
          <SearchInput
            type="text"
            placeholder={t("tasks.searchPlaceholder")}
            value={searchValue}
            onChange={(e) => onSearchChange(e.target.value)}
          />
        </SearchWrapper>

        <Actions>
          <LangWrapper ref={langRef}>
            <LangButton onClick={() => setLangOpen((o) => !o)}>
              <Flag>{currentLang.flag}</Flag>
              {currentLang.code.toUpperCase()}
              <ChevronDown>&#9660;</ChevronDown>
            </LangButton>

            <LangDropdown $open={langOpen}>
              {LANGUAGES.map((lang) => (
                <LangOption
                  key={lang.code}
                  $active={i18n.language === lang.code}
                  onClick={() => handleLanguageChange(lang.code)}
                >
                  <Flag>{lang.flag}</Flag>
                  {lang.label}
                </LangOption>
              ))}
            </LangDropdown>
          </LangWrapper>
          <BalanceBox>
            <CoinIcon>&#9733;</CoinIcon>
            {t("wallet.balance")}: {balance} ZION
          </BalanceBox>

          {user && (
            <UserGreeting>
              <UserAvatar>
                {avatarUrl ? (
                  <img src={resolveUrl(avatarUrl) ?? avatarUrl} alt={user.displayName || "avatar"} />
                ) : (
                  initials
                )}
              </UserAvatar>
              {user.displayName}
            </UserGreeting>
          )}

          <LogoutBtn onClick={handleLogout}>
            &#9211; {t("nav.logout")}
          </LogoutBtn>
        </Actions>
      </Row>
    </Header>
  );
}
