import { createFileRoute, useNavigate } from "@tanstack/react-router";
import { useEffect, useState } from "react";
import { useTranslation } from "react-i18next";
import { useAppDispatch, useAppSelector } from "../../store/hooks";
import { fetchMyTakenTasks } from "../../store/slices/tasks.slice";
import { getOrCreateTaskConversation } from "../../store/slices/chat.slice";
import { StatusBadge } from "../../components/ui/Badge";
import { Button } from "../../components/ui/Button";
import { Spinner } from "../../components/ui/Loading";
import { MarkDoneModal } from "../../components/features/tasks/MarkDoneModal";
import { Title, CenterLoader, EmptyState, List, MetaRow, TaskDesc, TaskItem, TaskTitle, TaskTop, CategoryTag, RewardText, InfoRow, WaitingBox, ActionsRow } from "./taken.styled";

export const Route = createFileRoute("/taken")({
  component: TakenByMePage,
});



function formatDate(dateString?: string) {
  if (!dateString) return "—";
  return new Date(dateString).toLocaleDateString("en-US", {
    month: "short",
    day: "numeric",
    year: "numeric",
  });
}

function TakenByMePage() {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const navigate = useNavigate();
  const { myTakenTasks, loading } = useAppSelector((s) => s.tasks);
  const [markDoneTaskId, setMarkDoneTaskId] = useState<number | null>(null);

  useEffect(() => {
    dispatch(fetchMyTakenTasks({ page: 0, size: 50 }));
  }, [dispatch]);

  return (
    <>
      <Title>{t("nav.takenByMe")}</Title>

      {loading ? (
        <CenterLoader><Spinner $size="lg" /></CenterLoader>
      ) : myTakenTasks.length === 0 ? (
        <EmptyState>{t("tasks.noTasks")}</EmptyState>
      ) : (
        <List>
          {myTakenTasks.map((task) => (
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

              <InfoRow>
                <span>{t("tasks.creator")}: {task.creatorEmail}</span>
                <span>{t("tasks.deadline")}: {formatDate(task.deadlineAt)}</span>
              </InfoRow>

              <ActionsRow>
                {(task.status === "IN_PROGRESS" || task.status === "SUBMITTED" || task.status === "APPROVED") && (
                  <Button
                    $variant="secondary"
                    $fullWidth
                    onClick={async () => {
                      await dispatch(getOrCreateTaskConversation(task.id));
                      navigate({ to: "/chat" });
                    }}
                  >
                    {t("tasks.openChat")}
                  </Button>
                )}

                {task.status === "IN_PROGRESS" && (
                  <Button $fullWidth onClick={() => setMarkDoneTaskId(task.id)}>
                    {t("tasks.markDone")}
                  </Button>
                )}

                {task.status === "SUBMITTED" && (
                  <WaitingBox>{t("tasks.waitingApproval")}</WaitingBox>
                )}
              </ActionsRow>
            </TaskItem>
          ))}
        </List>
      )}

      <MarkDoneModal
        open={markDoneTaskId !== null}
        onClose={() => setMarkDoneTaskId(null)}
        taskId={markDoneTaskId}
        onSubmitted={() => dispatch(fetchMyTakenTasks({ page: 0, size: 50 }))}
      />
    </>
  );
}
