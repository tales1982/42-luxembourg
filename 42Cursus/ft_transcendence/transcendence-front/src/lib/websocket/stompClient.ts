import { Client, type StompSubscription } from "@stomp/stompjs";
import SockJS from "sockjs-client";
import type { MessageResponse, NotificationResponse } from "../../types";

let client: Client | null = null;
const pendingSubs: Array<{
  conversationId: number;
  callback: (msg: MessageResponse) => void;
  canceled: boolean;
  attach: (sub: StompSubscription) => void;
}> = [];

let pendingNotif: {
  userId: number;
  callback: (notif: NotificationResponse) => void;
  canceled: boolean;
  attach: (sub: StompSubscription) => void;
} | null = null;

export const stompManager = {
  connect(wsUrl: string, token: string, onConnect?: () => void): void {
    if (client?.active) return;

    const normalizedBase = wsUrl.replace(/\/+$/, "").replace(/\/ws$/, "");
    const sockJsUrl = normalizedBase.replace(/^ws(s)?:\/\//, "http$1://") + "/ws";

    client = new Client({
      webSocketFactory: () => new SockJS(sockJsUrl),
      connectHeaders: {
        Authorization: `Bearer ${token}`,
      },
      reconnectDelay: 5000,
      onConnect: () => {
        console.debug("[STOMP] connected");
        onConnect?.();
        if (pendingSubs.length > 0) {
          const toAttach = pendingSubs.splice(0, pendingSubs.length);
          toAttach.forEach((p) => {
            if (p.canceled || !client?.connected) return;
            const sub = client.subscribe(
              `/topic/conversations/${p.conversationId}`,
              (frame) => {
                try {
                  const msg: MessageResponse = JSON.parse(frame.body);
                  p.callback(msg);
                } catch (e) {
                  console.error("[STOMP] failed to parse message", e);
                }
              }
            );
            p.attach(sub);
          });
        }
        if (pendingNotif && !pendingNotif.canceled && client?.connected) {
          const p = pendingNotif;
          const sub = client.subscribe(`/topic/notifications/${p.userId}`, (frame) => {
            try {
              const notif: NotificationResponse = JSON.parse(frame.body);
              p.callback(notif);
            } catch (e) {
              console.error("[STOMP] failed to parse notification", e);
            }
          });
          p.attach(sub);
          pendingNotif = null;
        }
      },
      onStompError: (frame) => {
        console.error("[STOMP] error", frame.headers["message"]);
      },
      onDisconnect: () => {
        console.debug("[STOMP] disconnected");
      },
    });

    client.activate();
  },

  subscribe(
    conversationId: number,
    callback: (msg: MessageResponse) => void
  ): StompSubscription | null {
    if (!client) return null;

    const makeSub = () =>
      client!.subscribe(`/topic/conversations/${conversationId}`, (frame) => {
        try {
          const msg: MessageResponse = JSON.parse(frame.body);
          callback(msg);
        } catch (e) {
          console.error("[STOMP] failed to parse message", e);
        }
      });

    if (client.connected) {
      return makeSub();
    }

    let actualSub: StompSubscription | null = null;
    const pending = {
      conversationId,
      callback,
      canceled: false,
      attach: (sub: StompSubscription) => {
        actualSub = sub;
      },
    };
    pendingSubs.push(pending);

    return {
      unsubscribe: () => {
        if (actualSub) {
          actualSub.unsubscribe();
        } else {
          pending.canceled = true;
        }
      },
    } as StompSubscription;
  },

  subscribeNotifications(
    userId: number,
    callback: (notif: NotificationResponse) => void
  ): StompSubscription | null {
    if (!client) return null;

    const makeSub = () =>
      client!.subscribe(`/topic/notifications/${userId}`, (frame) => {
        try {
          const notif: NotificationResponse = JSON.parse(frame.body);
          callback(notif);
        } catch (e) {
          console.error("[STOMP] failed to parse notification", e);
        }
      });

    if (client.connected) {
      return makeSub();
    }

    let actualSub: StompSubscription | null = null;
    pendingNotif = {
      userId,
      callback,
      canceled: false,
      attach: (sub: StompSubscription) => {
        actualSub = sub;
      },
    };

    return {
      unsubscribe: () => {
        if (actualSub) {
          actualSub.unsubscribe();
        } else if (pendingNotif) {
          pendingNotif.canceled = true;
        }
      },
    } as StompSubscription;
  },

  disconnect(): void {
    if (client?.active) {
      client.deactivate();
      client = null;
      pendingNotif = null;
    }
  },
};
