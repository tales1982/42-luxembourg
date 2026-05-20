import { useRouterState } from "@tanstack/react-router";
import { useTranslation } from "react-i18next";
import { useEffect } from "react";
import { useAppSelector, useAppDispatch } from "../../store/hooks";
import { fetchUnreadCount } from "../../store/slices/notifications.slice";
import  { NavLink, Aside, Logo, Nav, NavIcon, NavBadge, BottomSection, NewTaskButton, Footer, SchoolName, Authors } from "./Sidebar.styled";
import { WalletConnect } from "../features/blockchain/WalletConnect";
import type { SidebarProps } from "../../interfaces/SidebarProps.interface";
import {
  FiGrid,
  FiShoppingBag,
  FiClipboard,
  FiCheckCircle,
  FiMessageSquare,
  FiUser,
  FiCreditCard,
  FiUsers,
  FiClock,
  FiBell,
} from "react-icons/fi";




export function Sidebar({ open, onClose, onNewTask }: SidebarProps) {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const location = useRouterState({ select: (s) => s.location });
  const unreadCount = useAppSelector((s) => s.chat.unreadTotal);
  const unreadNotifications = useAppSelector((s) => s.notifications.unreadCount);

  useEffect(() => {
    dispatch(fetchUnreadCount());
    const interval = setInterval(() => dispatch(fetchUnreadCount()), 30000);
    return () => clearInterval(interval);
  }, [dispatch]);

  const isActive = (path: string) => location.pathname === path;

  const handleClick = () => {
    if (window.innerWidth < 768) onClose();
  };

  return (
    <Aside $open={open}>
      <Logo>{t("app.title")}</Logo>

      <Nav>
        <NavLink to="/dashboard" $active={isActive("/dashboard")} onClick={handleClick}>
          <NavIcon><FiGrid /></NavIcon>
          {t("nav.dashboard")}
        </NavLink>

        <NavLink to="/marketplace" $active={isActive("/marketplace")} onClick={handleClick}>
          <NavIcon><FiShoppingBag /></NavIcon>
          {t("nav.marketplace")}
        </NavLink>

        <NavLink to="/my-tasks" $active={isActive("/my-tasks")} onClick={handleClick}>
          <NavIcon><FiClipboard /></NavIcon>
          {t("nav.myTasks")}
        </NavLink>

        <NavLink to="/taken" $active={isActive("/taken")} onClick={handleClick}>
          <NavIcon><FiCheckCircle /></NavIcon>
          {t("nav.takenByMe")}
        </NavLink>

        <NavLink to="/chat" $active={isActive("/chat")} onClick={handleClick}>
          <NavIcon><FiMessageSquare /></NavIcon>
          {t("nav.chat")}
          {unreadCount > 0 && <NavBadge>{unreadCount}</NavBadge>}
        </NavLink>

        <NavLink to="/profile" $active={isActive("/profile")} onClick={handleClick}>
          <NavIcon><FiUser /></NavIcon>
          {t("nav.profile")}
        </NavLink>

        <NavLink to="/wallet" $active={isActive("/wallet")} onClick={handleClick}>
          <NavIcon><FiCreditCard /></NavIcon>
          {t("nav.wallet")}
        </NavLink>

        <NavLink to="/friends" $active={isActive("/friends")} onClick={handleClick}>
          <NavIcon><FiUsers /></NavIcon>
          {t("nav.friends")}
        </NavLink>

        <NavLink to="/history" $active={isActive("/history")} onClick={handleClick}>
          <NavIcon><FiClock /></NavIcon>
          {t("nav.history")}
        </NavLink>

        <NavLink to="/notifications" $active={isActive("/notifications")} onClick={handleClick}>
          <NavIcon><FiBell /></NavIcon>
          {t("nav.notifications")}
          {unreadNotifications > 0 && <NavBadge>{unreadNotifications}</NavBadge>}
        </NavLink>
      </Nav>

      <BottomSection>
        <WalletConnect />

        <NewTaskButton onClick={onNewTask}>
          + {t("tasks.newTask")}
        </NewTaskButton>

        <Footer>
          <SchoolName>42 Luxembourg</SchoolName>
          <Authors>Tales &middot; Joao &middot; Andre &middot; Sandro &middot; Fabio</Authors>
        </Footer>
      </BottomSection>
    </Aside>
  );
}
