import { createFileRoute, useNavigate } from "@tanstack/react-router";
import { useEffect, useState } from "react";
import { useTranslation } from "react-i18next";
import styled from "styled-components";
import { friendsApi, type FriendEntry, type UserSearchResult } from "../../lib/api/friends";
import { useAppDispatch } from "../../store/hooks";
import { fetchMessages, getOrCreateDirectConversation } from "../../store/slices/chat.slice";
import { Button } from "../../components/ui/Button";
import { Input, FormGroup, Label } from "../../components/ui/Input";
import { Spinner } from "../../components/ui/Loading";
import { showToast } from "../../components/ui/Toast";
import { Title, CenterLoader, EmptyState } from "./taken.styled";

export const Route = createFileRoute("/friends")({
  component: FriendsPage,
});

// ── Styled ──────────────────────────────────────────────────────────────────

const Tabs = styled.div`
  display: flex;
  gap: 0.5rem;
  margin-bottom: 1.5rem;
  border-bottom: 1px solid ${({ theme }) => theme.colors.border};
`;

const Tab = styled.button<{ $active: boolean }>`
  padding: 0.5rem 1rem;
  background: none;
  border: none;
  border-bottom: 2px solid ${({ $active, theme }) => ($active ? theme.colors.accent : "transparent")};
  color: ${({ $active, theme }) => ($active ? theme.colors.text : theme.colors.muted)};
  font-weight: ${({ $active }) => ($active ? 700 : 400)};
  cursor: pointer;
  font-size: 0.9rem;
  transition: all 0.15s;
`;

const Card = styled.div`
  background: ${({ theme }) => theme.colors.panel};
  border: 1px solid ${({ theme }) => theme.colors.border};
  border-radius: ${({ theme }) => theme.radius.lg};
  padding: 1rem 1.25rem;
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 1rem;
`;

const UserInfo = styled.div`
  display: flex;
  flex-direction: column;
  gap: 0.2rem;
`;

const UserName = styled.span`
  font-weight: 600;
  color: ${({ theme }) => theme.colors.text};
  font-size: 0.95rem;
`;

const UserEmail = styled.span`
  color: ${({ theme }) => theme.colors.muted};
  font-size: 0.8rem;
`;

const Actions = styled.div`
  display: flex;
  gap: 0.5rem;
  flex-shrink: 0;
`;

const List = styled.div`
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
`;

const SearchRow = styled.div`
  display: flex;
  gap: 0.75rem;
  align-items: flex-end;
  margin-bottom: 1rem;
`;

const SubTabs = styled.div`
  display: flex;
  gap: 0.5rem;
  margin-bottom: 1rem;
`;

const SubTab = styled.button<{ $active: boolean }>`
  padding: 0.3rem 0.75rem;
  border-radius: 20px;
  border: 1px solid ${({ $active, theme }) => ($active ? theme.colors.accent : theme.colors.border)};
  background: ${({ $active, theme }) => ($active ? "rgba(99,102,241,0.12)" : "transparent")};
  color: ${({ $active, theme }) => ($active ? theme.colors.accent : theme.colors.muted)};
  font-size: 0.8rem;
  cursor: pointer;
`;

// ── Component ────────────────────────────────────────────────────────────────

type TabType = "friends" | "pending" | "find";

function FriendsPage() {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const navigate = useNavigate();
  const [activeTab, setActiveTab] = useState<TabType>("friends");
  const [pendingSubTab, setPendingSubTab] = useState<"received" | "sent">("received");

  const [friends, setFriends] = useState<FriendEntry[]>([]);
  const [pendingReceived, setPendingReceived] = useState<FriendEntry[]>([]);
  const [pendingSent, setPendingSent] = useState<FriendEntry[]>([]);
  const [searchResults, setSearchResults] = useState<UserSearchResult[]>([]);
  const [searchQuery, setSearchQuery] = useState("");
  const [loading, setLoading] = useState(false);
  const [searching, setSearching] = useState(false);

  function loadData() {
    setLoading(true);
    Promise.all([
      friendsApi.list(),
      friendsApi.pendingReceived(),
      friendsApi.pendingSent(),
    ])
      .then(([f, pr, ps]) => {
        setFriends(f);
        setPendingReceived(pr);
        setPendingSent(ps);
      })
      .catch(() => {})
      .finally(() => setLoading(false));
  }

  useEffect(() => {
    loadData();
  }, []);

  async function handleSearch() {
    if (searchQuery.trim().length < 2) return;
    setSearching(true);
    try {
      const results = await friendsApi.search(searchQuery.trim());
      setSearchResults(results);
    } catch {
      showToast(t("friends.requestError"), "error");
    } finally {
      setSearching(false);
    }
  }

  async function handleAdd(email: string) {
    try {
      await friendsApi.sendRequest(email);
      showToast(t("friends.requestSent"));
      loadData();
    } catch (e: unknown) {
      const msg = e instanceof Error ? e.message : t("friends.requestError");
      showToast(msg, "error");
    }
  }

  async function handleAccept(id: number) {
    try {
      await friendsApi.accept(id);
      showToast(t("friends.accepted"));
      loadData();
    } catch {
      showToast(t("friends.acceptError"), "error");
    }
  }

  async function handleReject(id: number) {
    try {
      await friendsApi.reject(id);
      showToast(t("friends.rejected"));
      loadData();
    } catch {
      showToast(t("friends.rejectError"), "error");
    }
  }

  async function handleRemove(id: number) {
    try {
      await friendsApi.remove(id);
      showToast(t("friends.removed"));
      loadData();
    } catch {
      showToast(t("friends.removeError"), "error");
    }
  }

  async function handleChat(userId: number) {
    const result = await dispatch(getOrCreateDirectConversation(userId));
    if (getOrCreateDirectConversation.fulfilled.match(result)) {
      dispatch(fetchMessages({ conversationId: result.payload.id }));
      navigate({ to: "/chat" });
    } else {
      showToast(t("friends.chatError"), "error");
    }
  }

  return (
    <>
      <Title>{t("friends.title")}</Title>

      <Tabs>
        <Tab $active={activeTab === "friends"} onClick={() => setActiveTab("friends")}>
          {t("friends.myFriends")} {friends.length > 0 && `(${friends.length})`}
        </Tab>
        <Tab $active={activeTab === "pending"} onClick={() => setActiveTab("pending")}>
          {t("friends.pending")}
          {pendingReceived.length > 0 && ` (${pendingReceived.length})`}
        </Tab>
        <Tab $active={activeTab === "find"} onClick={() => setActiveTab("find")}>
          {t("friends.findPeople")}
        </Tab>
      </Tabs>

      {loading ? (
        <CenterLoader><Spinner $size="lg" /></CenterLoader>
      ) : (
        <>
          {/* ── My Friends ── */}
          {activeTab === "friends" && (
            friends.length === 0 ? (
              <EmptyState>{t("friends.noFriends")}</EmptyState>
            ) : (
              <List>
                {friends.map((f) => (
                  <Card key={f.id}>
                    <UserInfo>
                      <UserName>{f.displayName || f.email}</UserName>
                      <UserEmail>{f.email}</UserEmail>
                    </UserInfo>
                    <Actions>
                      <Button $variant="outline" $size="sm" onClick={() => handleChat(f.userId)}>
                        {t("friends.chat")}
                      </Button>
                      <Button $variant="secondary" $size="sm" onClick={() => handleRemove(f.id)}>
                        {t("friends.remove")}
                      </Button>
                    </Actions>
                  </Card>
                ))}
              </List>
            )
          )}

          {/* ── Pending Requests ── */}
          {activeTab === "pending" && (
            <>
              <SubTabs>
                <SubTab $active={pendingSubTab === "received"} onClick={() => setPendingSubTab("received")}>
                  {t("friends.pendingReceived")} {pendingReceived.length > 0 && `(${pendingReceived.length})`}
                </SubTab>
                <SubTab $active={pendingSubTab === "sent"} onClick={() => setPendingSubTab("sent")}>
                  {t("friends.pendingSent")} {pendingSent.length > 0 && `(${pendingSent.length})`}
                </SubTab>
              </SubTabs>

              {pendingSubTab === "received" && (
                pendingReceived.length === 0 ? (
                  <EmptyState>{t("friends.noPending")}</EmptyState>
                ) : (
                  <List>
                    {pendingReceived.map((f) => (
                      <Card key={f.id}>
                        <UserInfo>
                          <UserName>{f.displayName || f.email}</UserName>
                          <UserEmail>{f.email}</UserEmail>
                        </UserInfo>
                        <Actions>
                          <Button $size="sm" onClick={() => handleAccept(f.id)}>
                            {t("friends.accept")}
                          </Button>
                          <Button $variant="secondary" $size="sm" onClick={() => handleReject(f.id)}>
                            {t("friends.reject")}
                          </Button>
                        </Actions>
                      </Card>
                    ))}
                  </List>
                )
              )}

              {pendingSubTab === "sent" && (
                pendingSent.length === 0 ? (
                  <EmptyState>{t("friends.noPending")}</EmptyState>
                ) : (
                  <List>
                    {pendingSent.map((f) => (
                      <Card key={f.id}>
                        <UserInfo>
                          <UserName>{f.displayName || f.email}</UserName>
                          <UserEmail>{f.email}</UserEmail>
                        </UserInfo>
                        <Actions>
                          <Button $variant="secondary" $size="sm" onClick={() => handleRemove(f.id)}>
                            {t("common.cancel")}
                          </Button>
                        </Actions>
                      </Card>
                    ))}
                  </List>
                )
              )}
            </>
          )}

          {/* ── Find People ── */}
          {activeTab === "find" && (
            <>
              <SearchRow>
                <FormGroup style={{ flex: 1, marginBottom: 0 }}>
                  <Label>{t("friends.searchPlaceholder")}</Label>
                  <Input
                    value={searchQuery}
                    onChange={(e) => setSearchQuery(e.target.value)}
                    onKeyDown={(e) => e.key === "Enter" && handleSearch()}
                    placeholder={t("friends.searchPlaceholder")}
                  />
                </FormGroup>
                <Button onClick={handleSearch} disabled={searching || searchQuery.trim().length < 2}>
                  {searching ? t("common.loading") : "Search"}
                </Button>
              </SearchRow>

              {searchResults.length === 0 ? (
                <EmptyState>{t("friends.noResults")}</EmptyState>
              ) : (
                <List>
                  {searchResults.map((u) => (
                    <Card key={u.id}>
                      <UserInfo>
                        <UserName>{u.displayName || u.email}</UserName>
                        <UserEmail>{u.email}</UserEmail>
                      </UserInfo>
                      <Actions>
                        <Button $size="sm" onClick={() => handleAdd(u.email)}>
                          {t("friends.addFriend")}
                        </Button>
                      </Actions>
                    </Card>
                  ))}
                </List>
              )}
            </>
          )}
        </>
      )}
    </>
  );
}
