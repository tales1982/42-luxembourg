export type User = {
  email: string;
  displayName: string;
};

export type AuthState = {
  accessToken: string | null;
  user: User | null;
  status: "guest" | "authenticated" | "2fa_pending";
  challengeToken: string | null;
  pendingEmail: string | null;
};
