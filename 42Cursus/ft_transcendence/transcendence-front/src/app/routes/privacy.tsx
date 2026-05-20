import { createFileRoute, Link } from '@tanstack/react-router'
import { useTranslation } from 'react-i18next'
import { PryPage, PryHeader, BackLink } from './privacy.styled'
import { PublicLayout } from '../../components/layout/PublicLayout'

export const Route = createFileRoute('/privacy')({
  component: PrivacyPage,
})

function PrivacyPage() {
  const { t } = useTranslation();
  const list = (key: string) => (t(key, { returnObjects: true }) as string[]);

  return (
    <PublicLayout>
      <PryPage>
        <BackLink><Link to="/register">← Back to Register</Link></BackLink>
        <PryHeader>
          <h1>{t("privacy.pageTitle")}</h1>
        </PryHeader>

        <h2>{t("privacy.s1.title")}</h2>
        <p>{t("privacy.s1.p1")}</p>

        <h2>{t("privacy.s2.title")}</h2>
        <p><strong>{t("privacy.s2.s21.title")}</strong></p>
        <ul>{list("privacy.s2.s21.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p><strong>{t("privacy.s2.s22.title")}</strong></p>
        <ul>{list("privacy.s2.s22.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p><strong>{t("privacy.s2.s23.title")}</strong></p>
        <ul>{list("privacy.s2.s23.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p><strong>{t("privacy.s2.s24.title")}</strong></p>
        <ul>{list("privacy.s2.s24.items").map((item, i) => <li key={i}>{item}</li>)}</ul>

        <h2>{t("privacy.s3.title")}</h2>
        <p>{t("privacy.s3.intro")}</p>
        <p><strong>{t("privacy.s3.s31.title")}</strong></p>
        <ul>{list("privacy.s3.s31.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p><strong>{t("privacy.s3.s32.title")}</strong></p>
        <ul>{list("privacy.s3.s32.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p><strong>{t("privacy.s3.s33.title")}</strong></p>
        <p>{t("privacy.s3.s33.p1")}</p>
        <p><strong>{t("privacy.s3.s34.title")}</strong></p>
        <ul>{list("privacy.s3.s34.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p>{t("privacy.s3.s34.p1")}</p>

        <h2>{t("privacy.s4.title")}</h2>
        <p>{t("privacy.s4.intro")}</p>
        <ul>{list("privacy.s4.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p>{t("privacy.s4.p1")}</p>

        <h2>{t("privacy.s5.title")}</h2>
        <p>{t("privacy.s5.intro")}</p>
        <ul>{list("privacy.s5.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p>{t("privacy.s5.p1")}</p>

        <h2>{t("privacy.s6.title")}</h2>
        <p>{t("privacy.s6.intro")}</p>
        <ul>{list("privacy.s6.items").map((item, i) => <li key={i}>{item}</li>)}</ul>

        <h2>{t("privacy.s7.title")}</h2>
        <p>{t("privacy.s7.intro")}</p>
        <ul>{list("privacy.s7.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p>{t("privacy.s7.p1")}</p>

        <h2>{t("privacy.s8.title")}</h2>
        <p>{t("privacy.s8.intro")}</p>
        <ul>{list("privacy.s8.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p>{t("privacy.s8.p1")}</p>

        <h2>{t("privacy.s9.title")}</h2>
        <p>{t("privacy.s9.intro")}</p>
        <ul>{list("privacy.s9.items").map((item, i) => <li key={i}>{item}</li>)}</ul>

        <h2>{t("privacy.s10.title")}</h2>
        <p>{t("privacy.s10.p1")}</p>
      </PryPage>
    </PublicLayout>
  );
}
