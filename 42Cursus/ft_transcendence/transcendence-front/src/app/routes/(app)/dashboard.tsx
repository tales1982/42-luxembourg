import { createFileRoute } from "@tanstack/react-router";
import { useEffect, useState } from "react";
import { useTranslation } from "react-i18next";
import { taskApi } from "../../../lib/api/tasks";
import { paymentApi } from "../../../lib/api/payment";
import { Spinner } from "../../../components/ui/Loading";
import type { TaskStatsResponse, TokenAccountResponse } from "../../../types";
import {
  Title,
  StatsGrid,
  StatCard,
  StatNum,
  StatLabel,
  Section,
  SectionTitle,
  BreakdownRow,
  BreakdownItem,
  BreakdownBar,
  ZionBadge,
  CenterLoader,
} from "./dashboard.styled";

export const Route = createFileRoute("/(app)/dashboard")({
  component: DashboardPage,
});

function pct(part: number, total: number) {
  if (!total) return 0;
  return Math.round((part / total) * 100);
}

function DashboardPage() {
  const { t } = useTranslation();
  const [stats, setStats] = useState<TaskStatsResponse | null>(null);
  const [account, setAccount] = useState<TokenAccountResponse | null>(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    Promise.all([
      taskApi.getMyStats(),
      paymentApi.getMyAccount().catch(() => null),
    ]).then(([s, a]) => {
      setStats(s);
      setAccount(a);
    }).catch(() => {}).finally(() => setLoading(false));
  }, []);

  if (loading) return <CenterLoader><Spinner $size="lg" /></CenterLoader>;

  return (
    <>
      <Title>{t("dashboard.title")}</Title>

      {/* ── ZION Balance ── */}
      {account && (
        <Section>
          <SectionTitle>{t("dashboard.zionBalance")}</SectionTitle>
          <ZionBadge>
            ◈ {Number(account.availableBalance ?? 0).toFixed(2)} ZION
          </ZionBadge>
        </Section>
      )}

      {/* ── Top Stats ── */}
      <Section>
        <SectionTitle>{t("dashboard.taskBreakdown")}</SectionTitle>
        <StatsGrid>
          <StatCard>
            <StatNum>{stats?.totalCreated ?? 0}</StatNum>
            <StatLabel>{t("dashboard.tasksCreated")}</StatLabel>
          </StatCard>
          <StatCard>
            <StatNum>{stats?.completedCreated ?? 0}</StatNum>
            <StatLabel>{t("dashboard.tasksApproved")}</StatLabel>
          </StatCard>
          <StatCard>
            <StatNum>{stats?.totalTaken ?? 0}</StatNum>
            <StatLabel>{t("dashboard.tasksTaken")}</StatLabel>
          </StatCard>
          <StatCard>
            <StatNum>{stats?.completedTaken ?? 0}</StatNum>
            <StatLabel>{t("dashboard.takenCompleted")}</StatLabel>
          </StatCard>
        </StatsGrid>
      </Section>

      {/* ── Created breakdown ── */}
      {stats && stats.totalCreated > 0 && (
        <Section>
          <SectionTitle>{t("dashboard.createdBreakdown")}</SectionTitle>
          <BreakdownRow>
            <div>
              <BreakdownItem>
                <span>{t("dashboard.createdOpen")} ({stats.openCreated})</span>
                <span>{pct(stats.openCreated, stats.totalCreated)}%</span>
              </BreakdownItem>
              <BreakdownBar $pct={pct(stats.openCreated, stats.totalCreated)} $color="#3b82f6" />
            </div>
            <div>
              <BreakdownItem>
                <span>{t("dashboard.createdCompleted")} ({stats.completedCreated})</span>
                <span>{pct(stats.completedCreated, stats.totalCreated)}%</span>
              </BreakdownItem>
              <BreakdownBar $pct={pct(stats.completedCreated, stats.totalCreated)} $color="#34d399" />
            </div>
            <div>
              <BreakdownItem>
                <span>{t("dashboard.createdCancelled")} ({stats.cancelledCreated})</span>
                <span>{pct(stats.cancelledCreated, stats.totalCreated)}%</span>
              </BreakdownItem>
              <BreakdownBar $pct={pct(stats.cancelledCreated, stats.totalCreated)} $color="#f87171" />
            </div>
          </BreakdownRow>
        </Section>
      )}

      {/* ── Taken breakdown ── */}
      {stats && stats.totalTaken > 0 && (
        <Section>
          <SectionTitle>{t("dashboard.takenBreakdown")}</SectionTitle>
          <BreakdownRow>
            <div>
              <BreakdownItem>
                <span>{t("dashboard.takenInProgress")} ({stats.inProgressTaken})</span>
                <span>{pct(stats.inProgressTaken, stats.totalTaken)}%</span>
              </BreakdownItem>
              <BreakdownBar $pct={pct(stats.inProgressTaken, stats.totalTaken)} $color="#f59e0b" />
            </div>
            <div>
              <BreakdownItem>
                <span>{t("dashboard.takenCompleted")} ({stats.completedTaken})</span>
                <span>{pct(stats.completedTaken, stats.totalTaken)}%</span>
              </BreakdownItem>
              <BreakdownBar $pct={pct(stats.completedTaken, stats.totalTaken)} $color="#34d399" />
            </div>
          </BreakdownRow>
        </Section>
      )}
    </>
  );
}

export default DashboardPage;
