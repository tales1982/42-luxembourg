import { createSlice, createAsyncThunk, type PayloadAction } from "@reduxjs/toolkit";
import { taskApi, categoryApi } from "../../lib/api";
import type { TaskResponse, CategoryResponse, Page } from "../../types";
import type { TasksState } from "../../interfaces/TasksState.interface";



const initialState: TasksState = {
  tasks: [],
  myCreatedTasks: [],
  myTakenTasks: [],
  categories: [],
  selectedTask: null,
  pagination: {
    totalElements: 0,
    totalPages: 0,
    currentPage: 0,
    size: 10,
  },
  loading: false,
  error: null,
};

// Async thunks
export const fetchOpenTasks = createAsyncThunk(
  "tasks/fetchOpenTasks",
  async ({ page = 0, size = 10 }: { page?: number; size?: number }) => {
    return await taskApi.getOpenTasks(page, size);
  }
);

export const fetchMyCreatedTasks = createAsyncThunk(
  "tasks/fetchMyCreatedTasks",
  async ({ page = 0, size = 10 }: { page?: number; size?: number }) => {
    return await taskApi.getMyCreatedTasks(page, size);
  }
);

export const fetchMyTakenTasks = createAsyncThunk(
  "tasks/fetchMyTakenTasks",
  async ({ page = 0, size = 10 }: { page?: number; size?: number }) => {
    return await taskApi.getMyTakenTasks(page, size);
  }
);

export const fetchCategories = createAsyncThunk(
  "tasks/fetchCategories",
  async () => {
    return await categoryApi.getCategories();
  }
);

export const fetchTaskById = createAsyncThunk(
  "tasks/fetchTaskById",
  async (taskId: number) => {
    return await taskApi.getTask(taskId);
  }
);

export const createTaskWithCategory = createAsyncThunk(
  "tasks/createTaskWithCategory",
  async (
    {
      title,
      description,
      categoryId,
      categoryName,
      rewardAmount,
      locationText,
      deadlineAt,
    }: {
      title: string;
      description: string;
      categoryId?: number;
      categoryName?: string;
      rewardAmount?: number;
      locationText?: string;
      deadlineAt?: string;
    },
    { dispatch, getState }
  ) => {
    let resolvedCategoryId = categoryId;
    if (!resolvedCategoryId && categoryName?.trim()) {
      const name = categoryName.trim();
      const state = getState() as { tasks: TasksState };
      const existing = state.tasks.categories.find(
        (c) => c.name.toLowerCase() === name.toLowerCase()
      );
      if (existing) {
        resolvedCategoryId = existing.id;
      } else {
        const created = await categoryApi.createCategory({ name });
        resolvedCategoryId = created.id;
        dispatch(fetchCategories());
      }
    }

    const createdTask = await taskApi.createTask({
      title,
      description,
      categoryId: resolvedCategoryId,
      rewardAmount,
      locationText,
      deadlineAt,
    });

    dispatch(fetchMyCreatedTasks({ page: 0, size: 50 }));
    return createdTask;
  }
);

const tasksSlice = createSlice({
  name: "tasks",
  initialState,
  reducers: {
    setSelectedTask: (state, action: PayloadAction<TaskResponse | null>) => {
      state.selectedTask = action.payload;
    },
    clearError: (state) => {
      state.error = null;
    },
    updateTaskInList: (state, action: PayloadAction<TaskResponse>) => {
      const index = state.tasks.findIndex((t) => t.id === action.payload.id);
      if (index !== -1) {
        state.tasks[index] = action.payload;
      }
    },
  },
  extraReducers: (builder) => {
    // Fetch open tasks
    builder.addCase(fetchOpenTasks.pending, (state) => {
      state.loading = true;
      state.error = null;
    });
    builder.addCase(fetchOpenTasks.fulfilled, (state, action: PayloadAction<Page<TaskResponse>>) => {
      state.loading = false;
      state.tasks = action.payload.content;
      state.pagination = {
        totalElements: action.payload.totalElements,
        totalPages: action.payload.totalPages,
        currentPage: action.payload.number,
        size: action.payload.size,
      };
    });
    builder.addCase(fetchOpenTasks.rejected, (state, action) => {
      state.loading = false;
      state.error = action.error.message || "Failed to fetch tasks";
    });

    // Fetch my created tasks
    builder.addCase(fetchMyCreatedTasks.fulfilled, (state, action: PayloadAction<Page<TaskResponse>>) => {
      state.myCreatedTasks = action.payload.content;
    });

    // Fetch my taken tasks
    builder.addCase(fetchMyTakenTasks.fulfilled, (state, action: PayloadAction<Page<TaskResponse>>) => {
      state.myTakenTasks = action.payload.content;
    });

    // Fetch categories
    builder.addCase(fetchCategories.fulfilled, (state, action: PayloadAction<CategoryResponse[]>) => {
      state.categories = action.payload;
    });

    // Fetch task by ID
    builder.addCase(fetchTaskById.fulfilled, (state, action: PayloadAction<TaskResponse>) => {
      state.selectedTask = action.payload;
    });

    // Create task with category
    builder.addCase(createTaskWithCategory.pending, (state) => {
      state.loading = true;
      state.error = null;
    });
    builder.addCase(createTaskWithCategory.fulfilled, (state, action: PayloadAction<TaskResponse>) => {
      state.loading = false;
      state.myCreatedTasks.unshift(action.payload);
    });
    builder.addCase(createTaskWithCategory.rejected, (state, action) => {
      state.loading = false;
      state.error = action.error.message || "Failed to create task";
    });
  },
});

export const { setSelectedTask, clearError, updateTaskInList } = tasksSlice.actions;
export default tasksSlice.reducer;
