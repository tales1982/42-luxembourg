import styled from "styled-components";

export const PageHeader = styled.div`
  display: flex;
  align-items: center;
  justify-content: space-between;
  margin-bottom: ${({ theme }) => theme.space(3)};
`;

export const Title = styled.h2`
  font-size: 1.5rem;
  font-weight: 700;
  color: ${({ theme }) => theme.colors.text};
`;

export const CenterLoader = styled.div`
  display: flex;
  justify-content: center;
  padding: ${({ theme }) => theme.space(6)};
`;

export const EmptyState = styled.div`
  text-align: center;
  padding: ${({ theme }) => theme.space(6)};
  color: ${({ theme }) => theme.colors.muted};
`;

export const NotificationList = styled.div`
  display: flex;
  flex-direction: column;
  gap: ${({ theme }) => theme.space(1)};
  max-width: 640px;
`;

export const NotificationItem = styled.div<{ $unread: boolean }>`
  display: flex;
  gap: ${({ theme }) => theme.space(2)};
  padding: ${({ theme }) => theme.space(2)};
  border-radius: ${({ theme }) => theme.radius.md};
  background: ${({ theme, $unread }) =>
    $unread ? "rgba(52, 211, 153, 0.07)" : theme.colors.panel};
  border: 1px solid
    ${({ theme, $unread }) =>
      $unread ? theme.colors.primary : theme.colors.border};
  cursor: pointer;
  transition: background 150ms ease;

  &:hover {
    background: ${({ theme }) => theme.colors.card};
  }
`;

export const NotifIcon = styled.div`
  font-size: 1.4rem;
  min-width: 32px;
  text-align: center;
  padding-top: 2px;
`;

export const NotifContent = styled.div`
  flex: 1;
  min-width: 0;
`;

export const NotifTitle = styled.p<{ $unread: boolean }>`
  font-size: 0.9rem;
  font-weight: ${({ $unread }) => ($unread ? 700 : 500)};
  color: ${({ theme }) => theme.colors.text};
  margin-bottom: 2px;
`;

export const NotifBody = styled.p`
  font-size: 0.82rem;
  color: ${({ theme }) => theme.colors.muted};
  margin-bottom: 4px;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
`;

export const NotifTime = styled.span`
  font-size: 0.75rem;
  color: ${({ theme }) => theme.colors.muted};
`;

export const MarkAllBtn = styled.button`
  background: none;
  border: none;
  color: ${({ theme }) => theme.colors.primary};
  font-size: 0.85rem;
  font-weight: 600;
  cursor: pointer;
  padding: ${({ theme }) => theme.space(0.5)};

  &:hover {
    text-decoration: underline;
  }
`;
