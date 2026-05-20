import { createFileRoute, Link } from "@tanstack/react-router";
import { useEffect, useState } from "react";
import { useTranslation } from "react-i18next";
import { profileApi } from "../../lib/api/profile";
import { reviewApi } from "../../lib/api/reviews";
import { taskApi } from "../../lib/api/tasks";
import { paymentApi } from "../../lib/api/payment";
import { friendsApi } from "../../lib/api/friends";
import { Spinner } from "../../components/ui/Loading";
import { Button } from "../../components/ui/Button";
import { showToast } from "../../components/ui/Toast";
import { env } from "../../config/env";
import type { UserProfileResponse, ReviewResponse, TaskStatsResponse, TokenAccountResponse } from "../../types";
import {
  PageHeader,
  AvatarLarge,
  AvatarPlaceholderLarge,
  UserInfo,
  UserName,
  UserMeta,
  StarsRow,
  Star,
  Section,
  SectionTitle,
  StatRow,
  StatItem,
  StatNum,
  StatTxt,
  ReviewCard,
  ReviewBody,
  ReviewMeta,
  CenterLoader,
  EmptyState,
} from "./users.styled";

export const Route = createFileRoute("/users/$userId")({
  component: UserProfilePage,
});

function resolveAvatar(url?: string): string | null {
  if (!url) return null;
  return url.startsWith("/") ? `${env.API_BASE_URL}${url}` : url;
}

function renderStars(avg: number) {
  return Array.from({ length: 5 }, (_, i) => (
    <Star key={i} $filled={i < Math.round(avg)}>★</Star>
  ));
}

function UserProfilePage() {
  const { t } = useTranslation();
  const { userId } = Route.useParams();
  const uid = Number(userId);

  const [profile, setProfile] = useState<UserProfileResponse | null>(null);
  const [stats, setStats] = useState<TaskStatsResponse | null>(null);
  const [reviews, setReviews] = useState<ReviewResponse[]>([]);
  const [account, setAccount] = useState<TokenAccountResponse | null>(null);
  const [avgRating, setAvgRating] = useState(0);
  const [loading, setLoading] = useState(true);
  const [addingFriend, setAddingFriend] = useState(false);

  useEffect(() => {
    Promise.all([
      profileApi.getProfile(uid),
      taskApi.getUserStats(uid),
      reviewApi.getUserReviews(uid, 0, 5).then((p) => p.content),
      reviewApi.getUserReviewStats(uid).catch(() => ({ averageRating: 0, totalReviews: 0 })),
      paymentApi.getAccount(uid).catch(() => null),
    ]).then(([p, s, r, rs, a]) => {
      setProfile(p);
      setStats(s);
      setReviews(r);
      setAvgRating(rs.averageRating ?? 0);
      setAccount(a);
    }).catch(() => {}).finally(() => setLoading(false));
  }, [uid]);

  async function handleAddFriend() {
    if (!profile) return;
    setAddingFriend(true);
    try {
      await friendsApi.sendRequestById(uid);
      showToast(t("friends.requestSent"));
    } catch {
      showToast(t("friends.requestError"), "error");
    } finally {
      setAddingFriend(false);
    }
  }

  if (loading) return <CenterLoader><Spinner $size="lg" /></CenterLoader>;
  if (!profile) return <EmptyState>{t("users.notFound")}</EmptyState>;

  const initials = String(uid).charAt(0).toUpperCase();

  return (
    <>
      <PageHeader>
        {resolveAvatar(profile.avatarUrl) ? (
          <AvatarLarge src={resolveAvatar(profile.avatarUrl)!} alt="avatar" />
        ) : (
          <AvatarPlaceholderLarge>{initials}</AvatarPlaceholderLarge>
        )}

        <UserInfo>
          <UserName>{profile.fullName || `User #${uid}`}</UserName>
          <UserMeta>{profile.country}</UserMeta>
          {avgRating > 0 && (
            <StarsRow>
              {renderStars(avgRating)}
              <span style={{ marginLeft: 6, fontSize: "0.8rem", color: "#888" }}>
                {avgRating.toFixed(1)}
              </span>
            </StarsRow>
          )}
          <Button
            type="button"
            $variant="outline"
            disabled={addingFriend}
            onClick={handleAddFriend}
            style={{ marginTop: "0.5rem", width: "fit-content" }}
          >
            {addingFriend ? <Spinner $size="sm" /> : `+ ${t("friends.addFriend")}`}
          </Button>
        </UserInfo>
      </PageHeader>

      {/* ── Stats ── */}
      <Section>
        <SectionTitle>{t("dashboard.title")}</SectionTitle>
        <StatRow>
          <StatItem>
            <StatNum>{stats?.totalCreated ?? 0}</StatNum>
            <StatTxt>{t("dashboard.tasksCreated")}</StatTxt>
          </StatItem>
          <StatItem>
            <StatNum>{stats?.completedCreated ?? 0}</StatNum>
            <StatTxt>{t("dashboard.tasksApproved")}</StatTxt>
          </StatItem>
          <StatItem>
            <StatNum>{stats?.totalTaken ?? 0}</StatNum>
            <StatTxt>{t("dashboard.tasksTaken")}</StatTxt>
          </StatItem>
          <StatItem>
            <StatNum>{account?.availableBalance ?? "—"}</StatNum>
            <StatTxt>ZION</StatTxt>
          </StatItem>
        </StatRow>
      </Section>

      {/* ── Reviews ── */}
      <Section>
        <SectionTitle>{t("users.reviews")}</SectionTitle>
        {reviews.length === 0 ? (
          <EmptyState style={{ padding: "1rem 0" }}>{t("users.noReviews")}</EmptyState>
        ) : (
          reviews.map((r) => (
            <ReviewCard key={r.id}>
              <StarsRow>{renderStars(r.rating)}</StarsRow>
              {r.comment && <ReviewBody>{r.comment}</ReviewBody>}
              <ReviewMeta>
                {new Date(r.createdAt).toLocaleDateString()}
              </ReviewMeta>
            </ReviewCard>
          ))
        )}
      </Section>

      <Link to="/marketplace" style={{ fontSize: "0.85rem" }}>
        ← {t("nav.marketplace")}
      </Link>
    </>
  );
}
