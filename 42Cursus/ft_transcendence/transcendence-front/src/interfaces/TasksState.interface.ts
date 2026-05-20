import type { CategoryResponse, TaskResponse } from "../types";

export interface TasksState {
  tasks: TaskResponse[];
  myCreatedTasks: TaskResponse[];
  myTakenTasks: TaskResponse[];
  categories: CategoryResponse[];
  selectedTask: TaskResponse | null;
  pagination: {
    totalElements: number;
    totalPages: number;
    currentPage: number;
    size: number;
  };
  loading: boolean;
  error: string | null;
}