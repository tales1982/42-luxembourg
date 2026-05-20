import type { TokenAccountResponse, TokenLedger } from "../types/payment.types";

export interface PaymentState {
  account: TokenAccountResponse | null;
  ledger: TokenLedger[];
  ledgerLoading: boolean;
  loading: boolean;
  error: string | null;
}
