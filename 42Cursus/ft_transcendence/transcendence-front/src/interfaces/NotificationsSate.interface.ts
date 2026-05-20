import type { NotificationResponse } from "../types/notification.types";

export interface NotificationsState {
  notifications: NotificationResponse[];
  unreadCount: number;
  loading: boolean;
  error: string | null;
}