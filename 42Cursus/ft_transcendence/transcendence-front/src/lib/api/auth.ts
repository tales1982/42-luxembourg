import { api } from "./client";

export type LoginRequest = { email: string; password: string };
export type LoginResponse =
  | { accessToken: string; email: string; displayName: string; requiresTwoFactor?: false }
  | { requiresTwoFactor: true; challengeToken: string };

export type RegisterRequest = { email: string; password: string; displayName?: string };
export type RegisterResponse = { accessToken: string; email: string; displayName: string };

export type TwoFactorSetupResponse = { secret: string; qrCodeBase64: string };

export const authApi = {
  login: async (req: LoginRequest): Promise<LoginResponse> => {
    const { data } = await api.post<LoginResponse>("/api/auth/login", req);
    return data;
  },

  register: async (req: RegisterRequest): Promise<RegisterResponse> => {
    const { data } = await api.post<RegisterResponse>("/api/auth/register", req);
    return data;
  },

  verify2fa: async (req: { challengeToken: string; code: string }): Promise<{ accessToken: string; email: string; displayName: string }> => {
    const { data } = await api.post("/api/auth/2fa/verify", req);
    return data;
  },

  setup2fa: async (): Promise<TwoFactorSetupResponse> => {
    const { data } = await api.post<TwoFactorSetupResponse>("/api/auth/2fa/setup");
    return data;
  },

  enable2fa: async (code: string): Promise<void> => {
    await api.post("/api/auth/2fa/enable", { code });
  },

  disable2fa: async (code: string): Promise<void> => {
    await api.post("/api/auth/2fa/disable", { code });
  },

  get2faStatus: async (): Promise<{ enabled: boolean }> => {
    const { data } = await api.get<{ enabled: boolean }>("/api/auth/2fa/status");
    return data;
  },
};

export const login = authApi.login;
export const register = authApi.register;
