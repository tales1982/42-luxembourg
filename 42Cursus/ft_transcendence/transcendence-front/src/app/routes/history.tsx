import { createFileRoute } from "@tanstack/react-router";
import { useEffect, useState } from "react";
import { useTranslation } from "react-i18next";
import styled from "styled-components";
import { api } from "../../lib/api/client";
import { StatusBadge } from "../../components/ui/Badge";
import { Spinner } from "../../components/ui/Loading";
import type { TaskResponse, TaskSubmissionResponse, Page } from "../../types";
import { Title, CenterLoader, EmptyState, List, TaskItem, TaskTop, TaskTitle, MetaRow, CategoryTag, RewardText } from "./taken.styled";

export const Route = createFileRoute("/history")({
  component: HistoryPage,
});

// ── Styled ───────────────────────────────────────────────────────────────────

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

const DateText = styled.span`
  font-size: 0.78rem;
  color: ${({ theme }) => theme.colors.muted};
`;

const TaskDesc = styled.p`
  color: ${({ theme }) => theme.colors.muted};
  font-size: 0.85rem;
  line-height: 1.5;
  margin-bottom: 0.75rem;
  display: -webkit-box;
  -webkit-line-clamp: 2;
  -webkit-box-orient: vertical;
  overflow: hidden;
`;

const ProofBox = styled.div`
  background: rgba(0, 0, 0, 0.2);
  border-radius: 6px;
  padding: 0.5rem 0.75rem;
  font-size: 0.82rem;
  color: ${({ theme }) => theme.colors.muted};
  margin-top: 0.5rem;
`;

// ── Helpers ──────────────────────────────────────────────────────────────────

function formatDate(d?: string) {
  if (!d) return "—";
  return new Date(d).toLocaleDateString(undefined, { month: "short", day: "numeric", year: "numeric" });
}

// ── Component ────────────────────────────────────────────────────────────────

type TabType = "created" | "taken" | "submissions";

function HistoryPage() {
  const { t } = useTranslation();
  const [activeTab, setActiveTab] = useState<TabType>("created");

  const [created, setCreated] = useState<TaskResponse[]>([]);
  const [taken, setTaken] = useState<TaskResponse[]>([]);
  const [submissions, setSubmissions] = useState<TaskSubmissionResponse[]>([]);
  const [loading, setLoading] = useState(false);

  useEffect(() => {
    setLoading(true);
    Promise.all([
      api.get<Page<TaskResponse>>("/api/tasks/my-created", { params: { page: 0, size: 100 } }).then((r) => r.data.content),
      api.get<Page<TaskResponse>>("/api/tasks/my-taken", { params: { page: 0, size: 100 } }).then((r) => r.data.content),
      api.get<Page<TaskSubmissionResponse>>("/api/submissions/my", { params: { page: 0, size: 100 } }).then((r) => r.data.content),
    ])
      .then(([c, tk, sub]) => {
        setCreated(c);
        setTaken(tk);
        setSubmissions(sub);
      })
      .catch(() => {})
      .finally(() => setLoading(false));
  }, []);

  return (
    <>
      <Title>{t("history.title")}</Title>

      <Tabs>
        <Tab $active={activeTab === "created"} onClick={() => setActiveTab("created")}>
          {t("history.created")} {created.length > 0 && `(${created.length})`}
        </Tab>
        <Tab $active={activeTab === "taken"} onClick={() => setActiveTab("taken")}>
          {t("history.taken")} {taken.length > 0 && `(${taken.length})`}
        </Tab>
        <Tab $active={activeTab === "submissions"} onClick={() => setActiveTab("submissions")}>
          {t("history.submissions")} {submissions.length > 0 && `(${submissions.length})`}
        </Tab>
      </Tabs>

      {loading ? (
        <CenterLoader><Spinner $size="lg" /></CenterLoader>
      ) : (
        <>
          {/* ── Tasks Created ── */}
          {activeTab === "created" && (
            created.length === 0 ? (
              <EmptyState>{t("history.noHistory")}</EmptyState>
            ) : (
              <List>
                {created.map((task) => (
                  <TaskItem key={task.id}>
                    <TaskTop>
                      <TaskTitle>{task.title}</TaskTitle>
                      <StatusBadge $status={task.status}>
                        {task.status.replace("_", " ")}
                      </StatusBadge>
                    </TaskTop>
                    <TaskDesc>{task.description}</TaskDesc>
                    <MetaRow>
                      <CategoryTag>{task.categoryName || "—"}</CategoryTag>
                      <RewardText>{task.rewardAmount} ZION</RewardText>
                    </MetaRow>
                    <DateText>{formatDate(task.createdAt)}</DateText>
                  </TaskItem>
                ))}
              </List>
            )
          )}

          {/* ── Tasks Taken ── */}
          {activeTab === "taken" && (
            taken.length === 0 ? (
              <EmptyState>{t("history.noHistory")}</EmptyState>
            ) : (
              <List>
                {taken.map((task) => (
                  <TaskItem key={task.id}>
                    <TaskTop>
                      <TaskTitle>{task.title}</TaskTitle>
                      <StatusBadge $status={task.status}>
                        {task.status.replace("_", " ")}
                      </StatusBadge>
                    </TaskTop>
                    <TaskDesc>{task.description}</TaskDesc>
                    <MetaRow>
                      <CategoryTag>{task.categoryName || "—"}</CategoryTag>
                      <RewardText>{task.rewardAmount} ZION</RewardText>
                    </MetaRow>
                    <DateText>{formatDate(task.createdAt)}</DateText>
                  </TaskItem>
                ))}
              </List>
            )
          )}

          {/* ── My Submissions ── */}
          {activeTab === "submissions" && (
            submissions.length === 0 ? (
              <EmptyState>{t("history.noHistory")}</EmptyState>
            ) : (
              <List>
                {submissions.map((sub) => (
                  <TaskItem key={sub.id}>
                    <TaskTop>
                      <TaskTitle>Task #{sub.taskId}</TaskTitle>
                      <StatusBadge $status={sub.status}>
                        {sub.status}
                      </StatusBadge>
                    </TaskTop>
                    {sub.proofText && (
                      <ProofBox>{sub.proofText}</ProofBox>
                    )}
                    <MetaRow style={{ marginTop: "0.75rem" }}>
                      <DateText>{t("history.submittedAt")}: {formatDate(sub.submittedAt)}</DateText>
                      {sub.reviewedAt && (
                        <DateText>{t("history.reviewedAt")}: {formatDate(sub.reviewedAt)}</DateText>
                      )}
                    </MetaRow>
                  </TaskItem>
                ))}
              </List>
            )
          )}
        </>
      )}
    </>
  );
}
