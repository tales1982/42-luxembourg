import { createFileRoute, Link } from '@tanstack/react-router'
import { useTranslation } from 'react-i18next'
import { PublicLayout } from '../../components/layout/PublicLayout'
import { TosPage, TosHeader, BackLink } from "./terms.styled";

export const Route = createFileRoute('/terms')({
  component: TermsPage,
})

function TermsPage() {
  const { t } = useTranslation();
  const list = (key: string) => (t(key, { returnObjects: true }) as string[]);

  return (
    <PublicLayout>
      <TosPage>
        <BackLink><Link to="/register">← Back to Register</Link></BackLink>
        <TosHeader>
          <h1>{t("terms.pageTitle")}</h1>
        </TosHeader>

        <h2>{t("terms.s1.title")}</h2>
        <p>{t("terms.s1.p1")}</p>
        <p>{t("terms.s1.p2")}</p>

        <h2>{t("terms.s2.title")}</h2>
        <p>{t("terms.s2.intro")}</p>
        <ul>{list("terms.s2.items").map((item, i) => <li key={i}>{item}</li>)}</ul>

        <h2>{t("terms.s3.title")}</h2>
        <p>{t("terms.s3.intro")}</p>
        <ul>{list("terms.s3.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p>{t("terms.s3.p1")}</p>

        <h2>{t("terms.s4.title")}</h2>
        <p>{t("terms.s4.intro")}</p>
        <ul>{list("terms.s4.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p><strong>{t("terms.s4.prohibLabel")}</strong> {t("terms.s4.prohibIntro")}</p>
        <ul>{list("terms.s4.prohibItems").map((item, i) => <li key={i}>{item}</li>)}</ul>

        <h2>{t("terms.s5.title")}</h2>
        <p>{t("terms.s5.p1")}</p>
        <p>{t("terms.s5.intro")}</p>
        <ul>{list("terms.s5.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p>{t("terms.s5.p2")}</p>

        <h2>{t("terms.s6.title")}</h2>
        <p>{t("terms.s6.p1")}</p>

        <h2>{t("terms.s7.title")}</h2>
        <p>{t("terms.s7.p1")}</p>
        <ul>{list("terms.s7.items").map((item, i) => <li key={i}>{item}</li>)}</ul>

        <h2>{t("terms.s8.title")}</h2>
        <p>{t("terms.s8.p1")}</p>

        <h2>{t("terms.s9.title")}</h2>
        <p>{t("terms.s9.intro")}</p>
        <ul>{list("terms.s9.items").map((item, i) => <li key={i}>{item}</li>)}</ul>
        <p>{t("terms.s9.p1")}</p>

        <h2>{t("terms.s10.title")}</h2>
        <p>{t("terms.s10.p1")}</p>
        <ul>{list("terms.s10.items").map((item, i) => <li key={i}>{item}</li>)}</ul>

        <h2>{t("terms.s11.title")}</h2>
        <p>{t("terms.s11.p1")}</p>

        <h2>{t("terms.s12.title")}</h2>
        <p>{t("terms.s12.p1")}</p>
      </TosPage>
    </PublicLayout>
  )
}
