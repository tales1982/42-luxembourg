import { createAsyncThunk, createSlice } from "@reduxjs/toolkit";
import { submissionApi } from "../../lib/api";
import type { TaskSubmissionResponse, TaskAttachmentResponse } from "../../types";

interface SubmissionState {
  taskSubmissions: Record<number, TaskSubmissionResponse[]>;       // keyed by taskId
  submissionAttachments: Record<number, TaskAttachmentResponse[]>; // keyed by submissionId
  loading: boolean;
  error: string | null;
}

const initialState: SubmissionState = {
  taskSubmissions: {},
  submissionAttachments: {},
  loading: false,
  error: null,
};

export const fetchTaskSubmissions = createAsyncThunk(
  "submissions/fetchTaskSubmissions",
  async (taskId: number) => {
    const subs = await submissionApi.getTaskSubmissions(taskId);
    return { taskId, subs };
  }
);

export const fetchSubmissionAttachments = createAsyncThunk(
  "submissions/fetchSubmissionAttachments",
  async (submissionId: number) => {
    const files = await submissionApi.getAttachments(submissionId);
    return { submissionId, files };
  }
);

export const fetchSubmittedTaskProofs = createAsyncThunk(
  "submissions/fetchSubmittedTaskProofs",
  async (taskIds: number[], { dispatch }) => {
    for (const taskId of taskIds) {
      const action = await dispatch(fetchTaskSubmissions(taskId));
      if (fetchTaskSubmissions.fulfilled.match(action)) {
        const pending = action.payload.subs.find((s) => s.status === "SUBMITTED");
        if (pending) {
          await dispatch(fetchSubmissionAttachments(pending.id));
        }
      }
    }
    return taskIds;
  }
);

export const approveTaskSubmission = createAsyncThunk(
  "submissions/approve",
  async (submissionId: number) => {
    return await submissionApi.approveSubmission(submissionId);
  }
);

export const rejectTaskSubmission = createAsyncThunk(
  "submissions/reject",
  async (submissionId: number) => {
    return await submissionApi.rejectSubmission(submissionId);
  }
);

const submissionSlice = createSlice({
  name: "submissions",
  initialState,
  reducers: {
    clearSubmissions: (state) => {
      state.taskSubmissions = {};
      state.submissionAttachments = {};
    },
  },
  extraReducers: (builder) => {
    builder
      .addCase(fetchTaskSubmissions.pending, (state) => {
        state.loading = true;
        state.error = null;
      })
      .addCase(fetchTaskSubmissions.fulfilled, (state, action) => {
        state.loading = false;
        state.taskSubmissions[action.payload.taskId] = action.payload.subs;
      })
      .addCase(fetchTaskSubmissions.rejected, (state, action) => {
        state.loading = false;
        state.error = action.error.message ?? null;
      })
      .addCase(fetchSubmissionAttachments.fulfilled, (state, action) => {
        state.submissionAttachments[action.payload.submissionId] = action.payload.files;
      })
      .addCase(fetchSubmittedTaskProofs.pending, (state) => {
        state.loading = true;
        state.error = null;
      })
      .addCase(fetchSubmittedTaskProofs.fulfilled, (state) => {
        state.loading = false;
      })
      .addCase(fetchSubmittedTaskProofs.rejected, (state, action) => {
        state.loading = false;
        state.error = action.error.message ?? null;
      })
      .addCase(approveTaskSubmission.pending, (state) => {
        state.loading = true;
      })
      .addCase(approveTaskSubmission.fulfilled, (state) => {
        state.loading = false;
      })
      .addCase(approveTaskSubmission.rejected, (state, action) => {
        state.loading = false;
        state.error = action.error.message ?? null;
      })
      .addCase(rejectTaskSubmission.pending, (state) => {
        state.loading = true;
      })
      .addCase(rejectTaskSubmission.fulfilled, (state) => {
        state.loading = false;
      })
      .addCase(rejectTaskSubmission.rejected, (state, action) => {
        state.loading = false;
        state.error = action.error.message ?? null;
      });
  },
});

export const { clearSubmissions } = submissionSlice.actions;
export default submissionSlice.reducer;
