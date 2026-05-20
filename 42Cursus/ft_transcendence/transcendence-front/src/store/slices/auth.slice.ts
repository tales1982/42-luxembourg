import { createSlice } from "@reduxjs/toolkit";
import type { PayloadAction } from "@reduxjs/toolkit";
import type { AuthState, User } from "../../types/auth.types";

function loadAuthState(): AuthState {
  try {
    const token = localStorage.getItem("accessToken");
    const userJson = localStorage.getItem("user");
    if (token && userJson) {
      return {
        accessToken: token,
        user: JSON.parse(userJson) as User,
        status: "authenticated",
        challengeToken: null,
        pendingEmail: null,
      };
    }
  } catch {
    // ignore parse errors
  }
  return { accessToken: null, user: null, status: "guest", challengeToken: null, pendingEmail: null };
}

const initialState: AuthState = loadAuthState();

const authSlice = createSlice({
  name: "auth",
  initialState,
  reducers: {
    setCredentials: (
      state,
      action: PayloadAction<{ accessToken: string; email: string; displayName: string }>
    ) => {
      state.accessToken = action.payload.accessToken;
      state.user = { email: action.payload.email, displayName: action.payload.displayName };
      state.status = "authenticated";
      state.challengeToken = null;
      state.pendingEmail = null;
      localStorage.setItem("accessToken", action.payload.accessToken);
      localStorage.setItem("user", JSON.stringify(state.user));
    },
    set2faChallenge: (
      state,
      action: PayloadAction<{ challengeToken: string; email: string }>
    ) => {
      state.status = "2fa_pending";
      state.challengeToken = action.payload.challengeToken;
      state.pendingEmail = action.payload.email;
      state.accessToken = null;
      state.user = null;
    },
    logout: (state) => {
      state.accessToken = null;
      state.user = null;
      state.status = "guest";
      state.challengeToken = null;
      state.pendingEmail = null;
      localStorage.removeItem("accessToken");
      localStorage.removeItem("user");
    },
  },
});

export const { setCredentials, set2faChallenge, logout } = authSlice.actions;
export default authSlice.reducer;
