import { createFileRoute } from "@tanstack/react-router";
import { useEffect, useRef } from "react";
import { useTranslation } from "react-i18next";
import { useAppDispatch, useAppSelector } from "../../store/hooks";
import {
  fetchConversations,
  fetchMessages,
  sendMessage,
  setActiveConversation,
  markConversationRead,
} from "../../store/slices/chat.slice";
import { Avatar } from "../../components/ui/Avatar";
import { Spinner } from "../../components/ui/Loading";
import { useState } from "react";
import type { ConversationResponse } from "../../types";
import { ChatContainer, ConversationList, ConversationHeader, ConversationHeaderTitle, ConversationsScroll, ConversationItem, ConvInfo, ConvName, ConvPreview, EmptyChat, ChatWindow, ChatHeader, ChatUserName, MessagesArea, MessageRow, MessageBubble, MessageText, MessageTime, InputArea, MessageInput, SendBtn } from "./chat.styled";
import { Title, CenterLoader } from "./taken.styled";

export const Route = createFileRoute("/chat")({
  component: ChatPage,
});



function formatTime(dateString: string) {
  return new Date(dateString).toLocaleTimeString("en-US", {
    hour: "2-digit",
    minute: "2-digit",
  });
}

function ChatPage() {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const { conversations, activeConversation, messages, loading, unreadByConversation } = useAppSelector((s) => s.chat);
  const authUser = useAppSelector((s) => s.auth.user);
  const [inputValue, setInputValue] = useState("");
  const messagesEndRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    dispatch(fetchConversations());
  }, [dispatch]);

  function getOtherParticipantName(conv: ConversationResponse): string {
    const emails = conv.participantEmails ?? [];
    const names = conv.participantDisplayNames ?? [];
    const authEmail = authUser?.email;

    if (emails.length > 0) {
      const otherIndex = authEmail
        ? emails.findIndex((e) => e && e.toLowerCase() !== authEmail.toLowerCase())
        : 0;
      const idx = otherIndex >= 0 ? otherIndex : 0;
      const displayName = names[idx]?.trim();
      return displayName || emails[idx] || `${t("chat.conversation")} #${conv.id}`;
    }

    return `${t("chat.conversation")} #${conv.id}`;
  }

  useEffect(() => {
    messagesEndRef.current?.scrollIntoView({ behavior: "smooth" });
  }, [messages]);

  useEffect(() => {
    if (!activeConversation) return;
    dispatch(markConversationRead(activeConversation.id));
  }, [activeConversation?.id, messages.length, dispatch]);

  useEffect(() => {
    if (activeConversation || conversations.length === 0) return;
    const withUnread = conversations.find((c) => (unreadByConversation[c.id] || 0) > 0);
    const target = withUnread ?? conversations[0];
    if (target) {
      selectConversation(target);
    }
  }, [activeConversation, conversations, unreadByConversation]);

  function selectConversation(conv: ConversationResponse) {
    dispatch(setActiveConversation(conv));
    dispatch(fetchMessages({ conversationId: conv.id }));
    dispatch(markConversationRead(conv.id));
  }

  function handleSend() {
    if (!inputValue.trim() || !activeConversation) return;
    dispatch(sendMessage({ conversationId: activeConversation.id, content: inputValue.trim() }));
    setInputValue("");
  }

  function handleKeyDown(e: React.KeyboardEvent) {
    if (e.key === "Enter") handleSend();
  }

  return (
    <>
      <Title>{t("nav.chat")}</Title>

      {loading && conversations.length === 0 ? (
        <CenterLoader><Spinner $size="lg" /></CenterLoader>
      ) : (
        <ChatContainer>
          <ConversationList>
            <ConversationHeader>
              <ConversationHeaderTitle>{t("chat.conversations")}</ConversationHeaderTitle>
            </ConversationHeader>
            <ConversationsScroll>
              {conversations.map((conv) => (
                <ConversationItem
                  key={conv.id}
                  $active={activeConversation?.id === conv.id}
                  onClick={() => selectConversation(conv)}
                >
                  <Avatar $size="sm">
                    {conv.participantIds[0]?.toString().charAt(0) || "?"}
                  </Avatar>
                  <ConvInfo>
                    <ConvName>{getOtherParticipantName(conv)}</ConvName>
                    <ConvPreview>{conv.taskId ? `Task #${conv.taskId}` : t("chat.directMessage")}</ConvPreview>
                  </ConvInfo>
                </ConversationItem>
              ))}
              {conversations.length === 0 && (
                <EmptyChat style={{ padding: 24 }}>{t("chat.noConversations")}</EmptyChat>
              )}
            </ConversationsScroll>
          </ConversationList>

          <ChatWindow>
            {activeConversation ? (
              <>
                <ChatHeader>
                  <Avatar $size="sm">?</Avatar>
                  <ChatUserName>{getOtherParticipantName(activeConversation)}</ChatUserName>
                </ChatHeader>

                <MessagesArea>
                  {messages.map((msg) => {
                    const isSent = msg.senderEmail === authUser?.email;
                    return (
                      <MessageRow key={msg.id} $sent={isSent}>
                        <MessageBubble $sent={isSent}>
                          <MessageText>{msg.content}</MessageText>
                          <MessageTime>{formatTime(msg.sentAt)}</MessageTime>
                        </MessageBubble>
                      </MessageRow>
                    );
                  })}
                  <div ref={messagesEndRef} />
                </MessagesArea>

                <InputArea>
                  <MessageInput
                    value={inputValue}
                    onChange={(e) => setInputValue(e.target.value)}
                    onKeyDown={handleKeyDown}
                    placeholder={t("chat.typePlaceholder")}
                  />
                  <SendBtn onClick={handleSend}>{t("chat.send")}</SendBtn>
                </InputArea>
              </>
            ) : (
              <EmptyChat>{t("chat.selectConversation")}</EmptyChat>
            )}
          </ChatWindow>
        </ChatContainer>
      )}
    </>
  );
}
