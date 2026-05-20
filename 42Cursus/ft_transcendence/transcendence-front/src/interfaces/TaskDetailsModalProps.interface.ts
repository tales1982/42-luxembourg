import type { TaskResponse } from "../types";



export interface TaskDetailsModalProps {
  open: boolean;
  onClose: () => void;
  task: TaskResponse | null;
  onTaken?: () => void;
  onMessageCreator?: () => void;
}