import { createSlice, createAsyncThunk, type PayloadAction } from "@reduxjs/toolkit";
import { paymentApi } from "../../lib/api";
import type { TokenAccountResponse, DepositRequest, WithdrawRequest } from "../../types";
import type { PaymentState } from "../../interfaces/PaymentState.interface";

const initialState: PaymentState = {
  account: null,
  ledger: [],
  ledgerLoading: false,
  loading: false,
  error: null,
};

// Async thunks
export const fetchAccount = createAsyncThunk(
  "payment/fetchAccount",
  async () => {
    return await paymentApi.getMyAccount();
  }
);

export const fetchLedger = createAsyncThunk(
  "payment/fetchLedger",
  async (page: number = 0) => {
    return await paymentApi.getLedger(page, 20);
  }
);

export const deposit = createAsyncThunk(
  "payment/deposit",
  async (data: DepositRequest) => {
    return await paymentApi.deposit(data);
  }
);

export const withdraw = createAsyncThunk(
  "payment/withdraw",
  async (data: WithdrawRequest) => {
    return await paymentApi.withdraw(data);
  }
);

const paymentSlice = createSlice({
  name: "payment",
  initialState,
  reducers: {
    clearPaymentError: (state) => {
      state.error = null;
    },
  },
  extraReducers: (builder) => {
    // fetchAccount
    builder.addCase(fetchAccount.pending, (state) => {
      state.loading = true;
      state.error = null;
    });
    builder.addCase(fetchAccount.fulfilled, (state, action: PayloadAction<TokenAccountResponse>) => {
      state.loading = false;
      state.account = action.payload;
    });
    builder.addCase(fetchAccount.rejected, (state, action) => {
      state.loading = false;
      state.error = action.error.message || "Failed to fetch account";
    });

    // fetchLedger
    builder.addCase(fetchLedger.pending, (state) => {
      state.ledgerLoading = true;
    });
    builder.addCase(fetchLedger.fulfilled, (state, action) => {
      state.ledgerLoading = false;
      state.ledger = action.payload.content;
    });
    builder.addCase(fetchLedger.rejected, (state) => {
      state.ledgerLoading = false;
    });

    // deposit
    builder.addCase(deposit.pending, (state) => {
      state.loading = true;
      state.error = null;
    });
    builder.addCase(deposit.fulfilled, (state, action: PayloadAction<TokenAccountResponse>) => {
      state.loading = false;
      state.account = action.payload;
    });
    builder.addCase(deposit.rejected, (state, action) => {
      state.loading = false;
      state.error = action.error.message || "Deposit failed";
    });

    // withdraw
    builder.addCase(withdraw.pending, (state) => {
      state.loading = true;
      state.error = null;
    });
    builder.addCase(withdraw.fulfilled, (state, action: PayloadAction<TokenAccountResponse>) => {
      state.loading = false;
      state.account = action.payload;
    });
    builder.addCase(withdraw.rejected, (state, action) => {
      state.loading = false;
      state.error = action.error.message || "Withdrawal failed";
    });
  },
});

export const { clearPaymentError } = paymentSlice.actions;
export default paymentSlice.reducer;
