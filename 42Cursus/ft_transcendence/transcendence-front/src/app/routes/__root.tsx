import { Outlet, createRootRoute, useRouterState, useNavigate } from "@tanstack/react-router";
import { useEffect } from "react";
import { AppShell } from "../../components/layout/AppShell";
import { ToastProvider } from "../../components/ui/Toast";
import { useAppSelector } from "../../store/hooks";

export const Route = createRootRoute({
  component: RootLayout,
});

function RootLayout() {
  const pathname = useRouterState({ select: (s) => s.location.pathname });
  const navigate = useNavigate();
  const authStatus = useAppSelector((s) => s.auth.status);
  const isAuthenticated = authStatus === "authenticated";
  const is2faPending = authStatus === "2fa_pending";
  const isPublicPage =
    pathname === "/" || pathname === "/login" || pathname === "/register" ||
    pathname === "/terms" || pathname === "/privacy" || pathname === "/2fa-verify";

  useEffect(() => {
    if (is2faPending && pathname !== "/2fa-verify") {
      navigate({ to: "/2fa-verify", replace: true });
      return;
    }
    if (!isAuthenticated && !is2faPending && !isPublicPage) {
      navigate({ to: "/login", replace: true });
    }
  }, [isAuthenticated, is2faPending, isPublicPage, pathname, navigate]);

  if (!isAuthenticated && !is2faPending && !isPublicPage) {
    return null;
  }

  const showShell = isAuthenticated && !isPublicPage;

  return (
    <>
      {showShell ? (
        <AppShell>
          <Outlet />
        </AppShell>
      ) : (
        <Outlet />
      )}
      <ToastProvider />
    </>
  );
}
