import { api } from "./client";
import type {
  TokenAccountResponse,
  TokenLedger,
  DepositRequest,
  WithdrawRequest,
} from "../../types";

interface PageResponse<T> {
  content: T[];
  totalElements: number;
  totalPages: number;
  number: number;
  size: number;
}

// Payment / Token Account API
export const paymentApi = {
  // Get current user's account
  getMyAccount: () =>
    api.get<TokenAccountResponse>("/api/account").then((res) => res.data),

  // Get account by user ID
  getAccount: (userId: number) =>
    api.get<TokenAccountResponse>(`/api/account/${userId}`).then((res) => res.data),

  // Get transaction ledger
  getLedger: (page = 0, size = 20) =>
    api.get<PageResponse<TokenLedger>>(`/api/account/ledger?page=${page}&size=${size}`).then((res) => res.data),

  // Deposit tokens
  deposit: (data: DepositRequest) =>
    api.post<TokenAccountResponse>("/api/account/deposit", data).then((res) => res.data),

  // Withdraw tokens
  withdraw: (data: WithdrawRequest) =>
    api.post<TokenAccountResponse>("/api/account/withdraw", data).then((res) => res.data),
};
