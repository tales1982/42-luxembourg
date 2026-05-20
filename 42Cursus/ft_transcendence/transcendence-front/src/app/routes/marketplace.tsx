import { createFileRoute } from "@tanstack/react-router";
import { useEffect, useState, useMemo } from "react";
import { useTranslation } from "react-i18next";
import { useAppDispatch, useAppSelector } from "../../store/hooks";
import { fetchOpenTasks, fetchCategories } from "../../store/slices/tasks.slice";
import { StatusBadge } from "../../components/ui/Badge";
import { Button } from "../../components/ui/Button";
import { Select } from "../../components/ui/Select";
import { Input } from "../../components/ui/Input";
import { Spinner } from "../../components/ui/Loading";
import { TaskDetailsModal } from "../../components/features/tasks/TaskDetailsModal";
import type { TaskResponse } from "../../types";
import {
  Header,
  Filters,
  TaskCard,
  CardTop,
  CardTitle,
  CardDesc,
  CardMeta,
  CardFooter,
  FooterItem,
  Grid,
  Title,
  CenterLoader,
  EmptyState,
  CategoryTag,
  RewardText,
} from "./marketplace.styled";


export const Route = createFileRoute("/marketplace")({
  component: MarketplacePage,
});

function formatDate(dateString?: string) {
  if (!dateString) return "\u2014";
  return new Date(dateString).toLocaleDateString("en-US", {
    month: "short",
    day: "numeric",
    year: "numeric",
  });
}

type SortOption = "newest" | "oldest" | "reward_high" | "reward_low";

function MarketplacePage() {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const { tasks, categories, loading } = useAppSelector((s) => s.tasks);

  const [selectedTask, setSelectedTask] = useState<TaskResponse | null>(null);
  const [detailsOpen, setDetailsOpen] = useState(false);
  const [categoryFilter, setCategoryFilter] = useState("");
  const [searchQuery, setSearchQuery] = useState("");
  const [sortBy, setSortBy] = useState<SortOption>("newest");

  useEffect(() => {
    dispatch(fetchOpenTasks({ page: 0, size: 100 }));
    dispatch(fetchCategories());
  }, [dispatch]);

  const filteredTasks = useMemo(() => {
    let result = tasks;

    if (categoryFilter) {
      result = result.filter((t) => t.categoryName === categoryFilter);
    }

    if (searchQuery.trim()) {
      const q = searchQuery.toLowerCase();
      result = result.filter(
        (t) =>
          t.title.toLowerCase().includes(q) ||
          (t.description?.toLowerCase().includes(q) ?? false) ||
          (t.categoryName?.toLowerCase().includes(q) ?? false)
      );
    }

    const sorted = [...result];
    if (sortBy === "newest") {
      sorted.sort((a, b) => new Date(b.createdAt).getTime() - new Date(a.createdAt).getTime());
    } else if (sortBy === "oldest") {
      sorted.sort((a, b) => new Date(a.createdAt).getTime() - new Date(b.createdAt).getTime());
    } else if (sortBy === "reward_high") {
      sorted.sort((a, b) => (b.rewardAmount ?? 0) - (a.rewardAmount ?? 0));
    } else if (sortBy === "reward_low") {
      sorted.sort((a, b) => (a.rewardAmount ?? 0) - (b.rewardAmount ?? 0));
    }

    return sorted;
  }, [tasks, categoryFilter, searchQuery, sortBy]);

  function openDetails(task: TaskResponse) {
    setSelectedTask(task);
    setDetailsOpen(true);
  }

  return (
    <>
      <Header>
        <Title>{t("nav.marketplace")}</Title>
        <Filters>
          <Input
            value={searchQuery}
            onChange={(e) => setSearchQuery(e.target.value)}
            placeholder={t("tasks.searchPlaceholder")}
            style={{ minWidth: "200px" }}
          />
          <Select
            value={categoryFilter}
            onChange={(e) => setCategoryFilter(e.target.value)}
          >
            <option value="">{t("tasks.allCategories")}</option>
            {categories.map((c) => (
              <option key={c.id} value={c.name}>
                {c.name}
              </option>
            ))}
          </Select>
          <Select
            value={sortBy}
            onChange={(e) => setSortBy(e.target.value as SortOption)}
          >
            <option value="newest">{t("tasks.sortNewest")}</option>
            <option value="oldest">{t("tasks.sortOldest")}</option>
            <option value="reward_high">{t("tasks.sortRewardHigh")}</option>
            <option value="reward_low">{t("tasks.sortRewardLow")}</option>
          </Select>
        </Filters>
      </Header>

      {loading ? (
        <CenterLoader>
          <Spinner $size="lg" />
        </CenterLoader>
      ) : filteredTasks.length === 0 ? (
        <EmptyState>{t("tasks.noTasks")}</EmptyState>
      ) : (
        <Grid>
          {filteredTasks.map((task) => (
            <TaskCard key={task.id}>
              <CardTop>
                <CardTitle>{task.title}</CardTitle>
                <StatusBadge $status={task.status}>OPEN</StatusBadge>
              </CardTop>

              <CardDesc>{task.description}</CardDesc>

              <CardMeta>
                <CategoryTag>{task.categoryName || "\u2014"}</CategoryTag>
                <RewardText>{task.rewardAmount} ZION</RewardText>
              </CardMeta>

              <CardFooter>
                <FooterItem>{task.locationText || "Remote"}</FooterItem>
                <FooterItem>{formatDate(task.deadlineAt)}</FooterItem>
              </CardFooter>

              <Button $variant="secondary" $fullWidth onClick={() => openDetails(task)}>
                {t("tasks.viewDetails")}
              </Button>
            </TaskCard>
          ))}
        </Grid>
      )}

      <TaskDetailsModal
        open={detailsOpen}
        onClose={() => setDetailsOpen(false)}
        task={selectedTask}
        onTaken={() => dispatch(fetchOpenTasks({ page: 0, size: 100 }))}
      />
    </>
  );
}
