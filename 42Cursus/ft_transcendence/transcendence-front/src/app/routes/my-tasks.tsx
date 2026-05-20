import { createFileRoute, useNavigate } from "@tanstack/react-router";
import { useEffect } from "react";
import { useTranslation } from "react-i18next";
import { useAppDispatch, useAppSelector } from "../../store/hooks";
import { fetchMyCreatedTasks } from "../../store/slices/tasks.slice";
import { getOrCreateTaskConversation } from "../../store/slices/chat.slice";
import {
  fetchSubmittedTaskProofs,
  approveTaskSubmission,
  rejectTaskSubmission,
} from "../../store/slices/submission.slice";
import { StatusBadge } from "../../components/ui/Badge";
import { Button } from "../../components/ui/Button";
import { Spinner } from "../../components/ui/Loading";
import { showToast } from "../../components/ui/Toast";
import type { TaskResponse } from "../../types";
import { ProofBox, ProofLabel, ProofText, ActionRow, ActionStack, PaidBox, AttachmentsRow, ProofImage, AttachmentLink } from "./my-tasks.styled";
import { InfoText } from "./profile.styled";
import { Title, CenterLoader, EmptyState, List, TaskItem, TaskTop, TaskTitle, TaskDesc, MetaRow, CategoryTag, RewardText } from "./taken.styled";

export const Route = createFileRoute("/my-tasks")({
  component: MyTasksPage,
});

function MyTasksPage() {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const navigate = useNavigate();

  const { myCreatedTasks, loading } = useAppSelector((s) => s.tasks);
  const { taskSubmissions, submissionAttachments } = useAppSelector((s) => s.submissions);

  useEffect(() => {
    dispatch(fetchMyCreatedTasks({ page: 0, size: 50 }));
  }, [dispatch]);

  useEffect(() => {
    const submittedTaskIds = myCreatedTasks
      .filter((t) => t.status === "SUBMITTED")
      .map((t) => t.id);
    if (submittedTaskIds.length > 0) {
      dispatch(fetchSubmittedTaskProofs(submittedTaskIds));
    }
  }, [myCreatedTasks, dispatch]);

  async function handleApprove(task: TaskResponse) {
    const taskSubs = taskSubmissions[task.id];
    const pending = taskSubs?.find((s) => s.status === "SUBMITTED");
    if (!pending) return;
    const result = await dispatch(approveTaskSubmission(pending.id));
    if (approveTaskSubmission.fulfilled.match(result)) {
      showToast(t("tasks.approved", { amount: task.rewardAmount }));
      dispatch(fetchMyCreatedTasks({ page: 0, size: 50 }));
    } else {
      showToast(t("tasks.approveError"), "error");
    }
  }

  async function handleReject(task: TaskResponse) {
    const taskSubs = taskSubmissions[task.id];
    const pending = taskSubs?.find((s) => s.status === "SUBMITTED");
    if (!pending) return;
    const result = await dispatch(rejectTaskSubmission(pending.id));
    if (rejectTaskSubmission.fulfilled.match(result)) {
      showToast(t("tasks.rejected"));
      dispatch(fetchMyCreatedTasks({ page: 0, size: 50 }));
    } else {
      showToast(t("tasks.rejectError"), "error");
    }
  }

  function renderActions(task: TaskResponse) {
    switch (task.status) {
      case "OPEN":
        return (
          <Button $variant="secondary" $size="sm">
            {t("common.delete")}
          </Button>
        );
      case "IN_PROGRESS":
        return (
          <>
            <InfoText>
              {t("tasks.takenBy")}: <strong>{task.takenByEmail}</strong>
            </InfoText>
            <Button
              $variant="secondary"
              $size="sm"
              onClick={async () => {
                await dispatch(getOrCreateTaskConversation(task.id));
                navigate({ to: "/chat" });
              }}
            >
              {t("tasks.openChat")}
            </Button>
          </>
        );
      case "SUBMITTED": {
        const taskSubs = taskSubmissions[task.id];
        const pending = taskSubs?.find((s) => s.status === "SUBMITTED");
        const pendingFiles = pending ? (submissionAttachments[pending.id] ?? []) : [];
        return (
          <>
            <Button
              $variant="secondary"
              $size="sm"
              onClick={async () => {
                await dispatch(getOrCreateTaskConversation(task.id));
                navigate({ to: "/chat" });
              }}
            >
              {t("tasks.openChat")}
            </Button>
            {pending && (
              <ProofBox>
                <ProofLabel>{t("tasks.proofSubmitted")}:</ProofLabel>
                <ProofText>{pending.proofText || t("tasks.noProof")}</ProofText>
                {pendingFiles.length > 0 && (
                  <AttachmentsRow>
                    {pendingFiles.map((file) =>
                      file.mimeType.startsWith("image/") ? (
                        <ProofImage
                          key={file.id}
                          src={file.url}
                          alt={file.fileName}
                          onClick={() => window.open(file.url, "_blank")}
                        />
                      ) : (
                        <AttachmentLink key={file.id} href={file.url} target="_blank" rel="noopener noreferrer">
                          📎 {file.fileName}
                        </AttachmentLink>
                      )
                    )}
                  </AttachmentsRow>
                )}
              </ProofBox>
            )}
            <ActionRow>
              <Button $size="sm" onClick={() => handleApprove(task)} style={{ flex: 1 }}>
                {t("tasks.approve")} ({task.rewardAmount} ZION)
              </Button>
              <Button $variant="secondary" $size="sm" onClick={() => handleReject(task)} style={{ flex: 1 }}>
                {t("tasks.reject")}
              </Button>
            </ActionRow>
          </>
        );
      }
      case "APPROVED":
        return (
          <ActionStack>
            <Button
              $variant="secondary"
              $size="sm"
              onClick={async () => {
                await dispatch(getOrCreateTaskConversation(task.id));
                navigate({ to: "/chat" });
              }}
            >
              {t("tasks.openChat")}
            </Button>
            <PaidBox>{t("tasks.paid")}: {task.rewardAmount} ZION</PaidBox>
          </ActionStack>
        );
      default:
        return null;
    }
  }

  return (
    <>
      <Title>{t("nav.myTasks")}</Title>

      {loading ? (
        <CenterLoader><Spinner $size="lg" /></CenterLoader>
      ) : myCreatedTasks.length === 0 ? (
        <EmptyState>{t("tasks.noTasks")}</EmptyState>
      ) : (
        <List>
          {myCreatedTasks.map((task) => (
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

              {renderActions(task)}
            </TaskItem>
          ))}
        </List>
      )}
    </>
  );
}
