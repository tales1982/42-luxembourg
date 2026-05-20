import { createFileRoute } from "@tanstack/react-router";
import { useEffect } from "react";
import { useTranslation } from "react-i18next";
import { useAppDispatch, useAppSelector } from "../../store/hooks";
import {
  fetchNotifications,
  markAsRead,
  markAllAsRead,
} from "../../store/slices/notifications.slice";
import { Spinner } from "../../components/ui/Loading";
import { Button } from "../../components/ui/Button";
import {
  PageHeader,
  Title,
  CenterLoader,
  EmptyState,
  NotificationList,
  NotificationItem,
  NotifIcon,
  NotifContent,
  NotifTitle,
  NotifBody,
  NotifTime,
  MarkAllBtn,
} from "./notifications.styled";

export const Route = createFileRoute("/notifications")({
  component: NotificationsPage,
});

function typeIcon(type: string) {
  if (type === "NEW_MESSAGE") return "✉";
  if (type === "PAYMENT") return "💰";
  return "🔔";
}

function parseDate(dateStr: string) {
  // If backend sends LocalDateTime without timezone, treat it as UTC
  const hasTz = /Z|[+-]\d{2}:\d{2}$/.test(dateStr);
  return new Date(hasTz ? dateStr : `${dateStr}Z`);
}

function timeAgo(dateStr: string) {
  const diff = Date.now() - parseDate(dateStr).getTime();
  const mins = Math.floor(diff / 60000);
  if (mins < 1) return "just now";
  if (mins < 60) return `${mins}m ago`;
  const hrs = Math.floor(mins / 60);
  if (hrs < 24) return `${hrs}h ago`;
  return `${Math.floor(hrs / 24)}d ago`;
}

function NotificationsPage() {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const { notifications, loading, unreadCount } = useAppSelector(
    (s) => s.notifications
  );

  useEffect(() => {
    dispatch(fetchNotifications({ page: 0, size: 50 }));
  }, [dispatch]);

  function handleMarkAll() {
    dispatch(markAllAsRead());
  }

  function handleClick(id: number, isRead: boolean) {
    if (!isRead) dispatch(markAsRead(id));
  }

  return (
    <>
      <PageHeader>
        <Title>{t("nav.notifications")}</Title>
        {unreadCount > 0 && (
          <MarkAllBtn onClick={handleMarkAll}>
            {t("notifications.markAllRead")}
          </MarkAllBtn>
        )}
      </PageHeader>

      {loading ? (
        <CenterLoader>
          <Spinner $size="lg" />
        </CenterLoader>
      ) : notifications.length === 0 ? (
        <EmptyState>{t("notifications.empty")}</EmptyState>
      ) : (
        <NotificationList>
          {notifications.map((n) => (
            <NotificationItem
              key={n.id}
              $unread={!n.isRead}
              onClick={() => handleClick(n.id, n.isRead)}
            >
              <NotifIcon>{typeIcon(n.type)}</NotifIcon>
              <NotifContent>
                <NotifTitle $unread={!n.isRead}>{n.title}</NotifTitle>
                {n.body && <NotifBody>{n.body}</NotifBody>}
                <NotifTime>{timeAgo(n.createdAt)}</NotifTime>
              </NotifContent>
            </NotificationItem>
          ))}
        </NotificationList>
      )}
    </>
  );
}
