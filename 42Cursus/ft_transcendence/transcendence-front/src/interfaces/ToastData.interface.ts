import type { ToastType } from "../types/ToastType.types";

export interface ToastData {
  message: string;
  type?: ToastType;
  duration?: number;
}