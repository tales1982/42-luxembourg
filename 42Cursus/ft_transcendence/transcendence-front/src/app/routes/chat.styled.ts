import styled, { css } from "styled-components";

export const Title = styled.h2`
  font-size: 1.5rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const ChatContainer = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  overflow: hidden;
  display: flex;
  height: 600px;

  @media (max-width: 768px) {
    flex-direction: column;
    height: auto;
  }
`;

export const ConversationList = styled.div`
  width: 33.333%;
  border-right: 1px solid ${({ theme }) => theme.colors.border};
  display: flex;
  flex-direction: column;

  @media (max-width: 768px) {
    width: 100%;
    border-right: none;
    border-bottom: 1px solid ${({ theme }) => theme.colors.border};
    max-height: 200px;
  }
`;

export const ConversationHeader = styled.div`
  padding: ${({ theme }) => theme.space(2)};
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
`;

export const ConversationHeaderTitle = styled.h3`
  font-weight: 600;
  color: ${({ theme }) => theme.colors.text};
  font-size: 0.95rem;
`;

export const ConversationsScroll = styled.div`
  overflow-y: auto;
  flex: 1;
`;

export const ConversationItem = styled.div<{ $active?: boolean }>`
  display: flex;
  align-items: center;
  padding: ${({ theme }) => theme.space(2)};
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
  cursor: pointer;
  transition: background 150ms ease;

  &:hover {
    background: ${({ theme }) => theme.colors.card};
  }

  ${({ $active, theme }) =>
    $active &&
    css`
      background: ${theme.colors.card};
    `}
`;

export const ConvInfo = styled.div`
  margin-left: ${({ theme }) => theme.space(1.5)};
  flex: 1;
  overflow: hidden;
`;

export const ConvName = styled.h4`
  font-weight: 600;
  color: ${({ theme }) => theme.colors.text};
  font-size: 0.875rem;
`;

export const ConvPreview = styled.p`
  color: ${({ theme }) => theme.colors.muted};
  font-size: 0.8rem;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
`;

export const ChatWindow = styled.div`
  flex: 1;
  display: flex;
  flex-direction: column;

  @media (max-width: 768px) {
    min-height: 400px;
  }
`;

export const ChatHeader = styled.div`
  display: flex;
  align-items: center;
  gap: ${({ theme }) => theme.space(1.5)};
  padding: ${({ theme }) => theme.space(2)};
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
`;

export const ChatUserName = styled.h3`
  font-weight: 600;
  color: ${({ theme }) => theme.colors.text};
  font-size: 0.95rem;
`;

export const MessagesArea = styled.div`
  flex: 1;
  overflow-y: auto;
  padding: ${({ theme }) => theme.space(2)};
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(2)};
`;

export const MessageRow = styled.div<{ $sent: boolean }>`
  display: flex;
  justify-content: ${({ $sent }) => ($sent ? "flex-end" : "flex-start")};
`;

export const MessageBubble = styled.div<{ $sent: boolean }>`
  max-width: 70%;
  padding: ${({ theme }) => theme.space(1.5)};
  border-radius: ${({ theme }) => theme.radius.lg};

  ${({ $sent, theme }) =>
    $sent
      ? css`
          background: rgba(74, 183, 96, 0.15);
          border: 1px solid rgba(74, 183, 96, 0.3);
          border-top-right-radius: 4px;
        `
      : css`
          background: rgba(255, 255, 255, 0.05);
          border: 1px solid ${theme.colors.border};
          border-top-left-radius: 4px;
        `}
`;

export const MessageText = styled.p`
  font-size: 0.875rem;
  line-height: 1.5;
  color: ${({ theme }) => theme.colors.text};
`;

export const MessageTime = styled.span`
  font-size: 0.7rem;
  color: ${({ theme }) => theme.colors.muted};
  display: block;
  margin-top: 4px;
`;

export const InputArea = styled.div`
  display: flex;
  padding: ${({ theme }) => theme.space(2)};
  border-top: 1px solid ${({ theme }) => theme.colors.border};
`;

export const MessageInput = styled.input`
  flex: 1;
  padding: ${({ theme }) => theme.space(1.5)};
  background: ${({ theme }) => theme.colors.card};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.md} 0 0 ${({ theme }) => theme.radius.md};
  color: ${({ theme }) => theme.colors.text};

  &::placeholder {
    color: ${({ theme }) => theme.colors.muted};
  }

  &:focus {
    outline: none;
    border-color: ${({ theme }) => theme.colors.primary};
  }
`;

export const SendBtn = styled.button`
  padding: ${({ theme }) => `${theme.space(1.5)} ${theme.space(2.5)}`};
  background: ${({ theme }) => theme.colors.primary};
  color: ${({ theme }) => theme.colors.bg};
  border: none;
  border-radius: 0 ${({ theme }) => theme.radius.md} ${({ theme }) => theme.radius.md} 0;
  cursor: pointer;
  font-weight: 600;
  transition: background 150ms ease;

  &:hover {
    background: ${({ theme }) => theme.colors.primaryHover};
  }
`;

export const EmptyChat = styled.div`
  flex: 1;
  display: flex;
  align-items: center;
  justify-content: center;
  color: ${({ theme }) => theme.colors.muted};
  font-size: 0.9rem;
`;

export const CenterLoader = styled.div`
  display: flex;
  justify-content: center;
  padding: ${({ theme }) => theme.space(6)};
`;