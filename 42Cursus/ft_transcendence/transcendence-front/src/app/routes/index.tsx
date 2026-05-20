import { createFileRoute, useNavigate } from "@tanstack/react-router";
import { useEffect, useState } from "react";
import { useTranslation } from "react-i18next";
import { publicTaskApi } from "../../lib/api/public";
import { useAppSelector } from "../../store/hooks";
import type { TaskResponse, CategoryResponse } from "../../types";
import { HeroSection, HeroContent, HeroTitle, HeroSubtitle, HeroCTA, SectionWrapper, SectionTitle, StepsGrid, StepCard, StepIcon, StepTitle, StepDesc, TasksSectionBg, TasksContainer, FilterRow, FilterChip, LoadingWrapper, TasksGrid, CardHeader, OpenBadge, CategoryBadge, RewardBadge, CardBottom, ModalOverlay, ModalCard, ModalClose, ModalTitle, ModalDesc, ModalGrid, ModalLabel, ModalReward, ModalValue, TagsRow, TagChip, ModalLoginBtn } from "./index.styled";
import { PublicLayout } from "../../components/layout/PublicLayout";
import { TaskCard, CardTitle, CardDesc, CardMeta } from "./marketplace.styled";
import { EmptyState } from "./taken.styled";

export const Route = createFileRoute("/")({
  component: LandingPage,
});



/* ── Helpers ── */
function formatDate(dateString?: string) {
  if (!dateString) return "\u2014";
  return new Date(dateString).toLocaleDateString("en-US", {
    month: "short",
    day: "numeric",
    year: "numeric",
  });
}

/* ── Component ── */
function LandingPage() {
  const { t, i18n } = useTranslation();
  const navigate = useNavigate();
  const isAuthenticated = useAppSelector(
    (s) => s.auth.status === "authenticated"
  );

  const [tasks, setTasks] = useState<TaskResponse[]>([]);
  const [categories, setCategories] = useState<CategoryResponse[]>([]);
  const [loading, setLoading] = useState(true);
  const [categoryFilter, setCategoryFilter] = useState("");
  const [selectedTask, setSelectedTask] = useState<TaskResponse | null>(null);

  useEffect(() => {
    if (isAuthenticated) {
      navigate({ to: "/marketplace", replace: true });
    }
  }, [isAuthenticated, navigate]);

  useEffect(() => {
    async function load() {
      try {
        const [taskData, catData] = await Promise.all([
          publicTaskApi.getOpenTasks(0, 50),
          publicTaskApi.getCategories(),
        ]);
        setTasks(taskData.content);
        setCategories(catData);
      } catch {
        // silently fail - tasks just won't show
      } finally {
        setLoading(false);
      }
    }
    load();
  }, []);

  const filteredTasks = categoryFilter
    ? tasks.filter((t) => t.categoryName === categoryFilter)
    : tasks;

  const steps = [
    {
      icon: "\u270D\uFE0F",
      titleKey: "landing.step1Title",
      descKey: "landing.step1Desc",
    },
    {
      icon: "\uD83D\uDD0D",
      titleKey: "landing.step2Title",
      descKey: "landing.step2Desc",
    },
    {
      icon: "\u2705",
      titleKey: "landing.step3Title",
      descKey: "landing.step3Desc",
    },
    {
      icon: "\uD83D\uDCB0",
      titleKey: "landing.step4Title",
      descKey: "landing.step4Desc",
    },
  ];

  return (
    <PublicLayout showFooterLinks>
      {/* ── Hero ── */}
      <HeroSection>
        <HeroContent>
          <HeroTitle>
            {t("landing.heroTitle1")}{" "}
            <span>{t("landing.heroHighlight")}</span>{" "}
            {t("landing.heroTitle2")}
          </HeroTitle>
          <HeroSubtitle>{t("landing.heroSubtitle")}</HeroSubtitle>
          <HeroCTA onClick={() => navigate({ to: "/register" })}>
            {t("landing.heroCTA")}
          </HeroCTA>
        </HeroContent>
      </HeroSection>

      {/* ── How it works ── */}
      <SectionWrapper>
        <SectionTitle>
          {t("landing.howTitle1")} <span>{t("landing.howHighlight")}</span>?
        </SectionTitle>
        <StepsGrid>
          {steps.map((s, i) => (
            <StepCard key={i}>
              <StepIcon>{s.icon}</StepIcon>
              <StepTitle>{t(s.titleKey)}</StepTitle>
              <StepDesc>{t(s.descKey)}</StepDesc>
            </StepCard>
          ))}
        </StepsGrid>
      </SectionWrapper>

      {/* ── Available Tasks ── */}
      <TasksSectionBg>
        <TasksContainer>
          <SectionTitle>
            {t("landing.tasksTitle1")}{" "}
            <span>{t("landing.tasksHighlight")}</span>
          </SectionTitle>

          {categories.length > 0 && (
            <FilterRow>
              <FilterChip
                $active={categoryFilter === ""}
                onClick={() => setCategoryFilter("")}
              >
                {t("tasks.allCategories")}
              </FilterChip>
              {categories.map((c) => (
                <FilterChip
                  key={c.id}
                  $active={categoryFilter === c.name}
                  onClick={() => setCategoryFilter(c.name)}
                >
                  {c.name}
                </FilterChip>
              ))}
            </FilterRow>
          )}

          {loading ? (
            <LoadingWrapper>{t("common.loading")}</LoadingWrapper>
          ) : filteredTasks.length === 0 ? (
            <EmptyState>{t("tasks.noTasks")}</EmptyState>
          ) : (
            <TasksGrid>
              {filteredTasks.map((task) => (
                <TaskCard key={task.id} onClick={() => setSelectedTask(task)}>
                  <CardHeader>
                    <CardTitle>{task.title}</CardTitle>
                    <OpenBadge>OPEN</OpenBadge>
                  </CardHeader>
                  <CardDesc>{task.description}</CardDesc>
                  <CardMeta>
                    <CategoryBadge>
                      {task.categoryName || "\u2014"}
                    </CategoryBadge>
                    <RewardBadge>{task.rewardAmount} ZION</RewardBadge>
                  </CardMeta>
                  <CardBottom>
                    <span>{task.locationText || "Remote"}</span>
                    <span>{formatDate(task.deadlineAt)}</span>
                  </CardBottom>
                </TaskCard>
              ))}
            </TasksGrid>
          )}
        </TasksContainer>
      </TasksSectionBg>

      {/* ── Task Detail Modal ── */}
      {selectedTask && (
        <ModalOverlay onClick={() => setSelectedTask(null)}>
          <ModalCard onClick={(e) => e.stopPropagation()}>
            <ModalClose onClick={() => setSelectedTask(null)}>
              &times;
            </ModalClose>
            <ModalTitle>{selectedTask.title}</ModalTitle>
            <ModalDesc>{selectedTask.description}</ModalDesc>

            <ModalGrid>
              <div>
                <ModalLabel>{t("tasks.category")}</ModalLabel>
                <CategoryBadge>
                  {selectedTask.categoryName || "\u2014"}
                </CategoryBadge>
              </div>
              <div>
                <ModalLabel>{t("tasks.reward")}</ModalLabel>
                <ModalReward>{selectedTask.rewardAmount} ZION</ModalReward>
              </div>
              <div>
                <ModalLabel>{t("tasks.location")}</ModalLabel>
                <ModalValue>
                  {selectedTask.locationText || "Remote"}
                </ModalValue>
              </div>
              <div>
                <ModalLabel>{t("tasks.deadline")}</ModalLabel>
                <ModalValue>{formatDate(selectedTask.deadlineAt)}</ModalValue>
              </div>
            </ModalGrid>

            {selectedTask.tags && selectedTask.tags.length > 0 && (
              <TagsRow>
                {selectedTask.tags.map((tag) => (
                  <TagChip key={tag}>#{tag}</TagChip>
                ))}
              </TagsRow>
            )}

            <ModalLoginBtn onClick={() => navigate({ to: "/login" })}>
              {t("landing.loginToTake")}
            </ModalLoginBtn>
          </ModalCard>
        </ModalOverlay>
      )}
    </PublicLayout>
  );
}
