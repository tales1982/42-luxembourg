import { useState, useEffect, useRef, type PropsWithChildren } from "react";
import { useRouterState } from "@tanstack/react-router";
import { Sidebar } from "./Sidebar";
import { TopBar } from "./TopBar";
import { NewTaskModal } from "../features/tasks/NewTaskModal";
import { Layout, Overlay, MainArea, Content } from "./AppShell.styled";
import { useAppDispatch, useAppSelector } from "../../store/hooks";
import { fetchAccount } from "../../store/slices/payment.slice";
import { fetchProfile } from "../../store/slices/profile.slice";
import { fetchConversations, fetchUnreadCounts, addMessage, incrementUnread, clearUnread } from "../../store/slices/chat.slice";
import { addNotification } from "../../store/slices/notifications.slice";
import { stompManager } from "../../lib/websocket/stompClient";
import { env } from "../../config/env";
import type { StompSubscription } from "@stomp/stompjs";



export function AppShell({ children }: PropsWithChildren) {
  const dispatch = useAppDispatch();
  const location = useRouterState({ select: (s) => s.location });
  const accessToken = useAppSelector((s) => s.auth.accessToken);
  const authUser = useAppSelector((s) => s.auth.user);
  const profile = useAppSelector((s) => s.profile.profile);
  const { conversations, activeConversation } = useAppSelector((s) => s.chat);
  const [sidebarOpen, setSidebarOpen] = useState(false);
  const [newTaskOpen, setNewTaskOpen] = useState(false);
  const [search, setSearch] = useState("");
  const subsRef = useRef<Record<number, StompSubscription>>({});
  const notifSubRef = useRef<StompSubscription | null>(null);

  // Refs para evitar closure stale nos callbacks STOMP
  const activeConvIdRef = useRef<number | null>(activeConversation?.id ?? null);
  const locationRef = useRef<string>(location.pathname);
  const authEmailRef = useRef<string | undefined>(authUser?.email);
  activeConvIdRef.current = activeConversation?.id ?? null;
  locationRef.current = location.pathname;
  authEmailRef.current = authUser?.email;

  useEffect(() => {
    if (!accessToken) return;
    dispatch(fetchAccount());
    const intervalId = window.setInterval(() => {
      dispatch(fetchAccount());
    }, 60000);
    return () => window.clearInterval(intervalId);
  }, [accessToken, dispatch]);

  useEffect(() => {
    if (!accessToken) return;
    dispatch(fetchProfile());
  }, [accessToken, dispatch]);

  useEffect(() => {
    if (!accessToken) return;
    dispatch(fetchConversations());
    dispatch(fetchUnreadCounts());
    const intervalId = window.setInterval(() => {
      dispatch(fetchConversations());
      dispatch(fetchUnreadCounts());
    }, 5000);
    return () => window.clearInterval(intervalId);
  }, [accessToken, dispatch]);

  useEffect(() => {
    if (!accessToken) return;
    stompManager.connect(env.WS_URL, accessToken);
    return () => stompManager.disconnect();
  }, [accessToken]);

  useEffect(() => {
    if (!accessToken || !profile?.userId) return;
    if (notifSubRef.current) return;
    const sub = stompManager.subscribeNotifications(profile.userId, (notif) => {
      dispatch(addNotification(notif));
    });
    notifSubRef.current = sub;
    return () => {
      notifSubRef.current?.unsubscribe();
      notifSubRef.current = null;
    };
  }, [accessToken, profile?.userId, dispatch]);

  useEffect(() => {
    const current = subsRef.current;
    const existingIds = new Set(Object.keys(current).map((id) => Number(id)));
    const conversationIds = new Set(conversations.map((c) => c.id));

    // Subscribe to new conversations
    conversations.forEach((conv) => {
      if (existingIds.has(conv.id)) return;
      const sub = stompManager.subscribe(conv.id, (msg) => {
        // Usar refs para sempre ler os valores mais recentes sem re-criar a subscription
        const isFromSelf = !!authEmailRef.current && msg.senderEmail.toLowerCase() === authEmailRef.current.toLowerCase();
        const isActive = activeConvIdRef.current === msg.conversationId && locationRef.current === "/chat";

        if (isActive) {
          dispatch(addMessage(msg));
          dispatch(clearUnread(msg.conversationId));
        } else if (!isFromSelf) {
          dispatch(incrementUnread(msg.conversationId));
        }
      });
      if (sub) current[conv.id] = sub;
    });

    // Unsubscribe removed conversations
    existingIds.forEach((id) => {
      if (!conversationIds.has(id)) {
        current[id]?.unsubscribe();
        delete current[id];
      }
    });
  }, [conversations, dispatch]);

  return (
    <Layout>
      <Sidebar
        open={sidebarOpen}
        onClose={() => setSidebarOpen(false)}
        onNewTask={() => setNewTaskOpen(true)}
      />

      <Overlay $visible={sidebarOpen} onClick={() => setSidebarOpen(false)} />

      <MainArea>
        <TopBar
          onMenuToggle={() => setSidebarOpen((o) => !o)}
          searchValue={search}
          onSearchChange={setSearch}
        />
        <Content>{children}</Content>
      </MainArea>

      <NewTaskModal open={newTaskOpen} onClose={() => setNewTaskOpen(false)} />
    </Layout>
  );
}
