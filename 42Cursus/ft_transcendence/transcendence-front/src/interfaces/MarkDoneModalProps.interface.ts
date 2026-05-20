export interface MarkDoneModalProps {
  open: boolean;
  onClose: () => void;
  taskId: number | null;
  onSubmitted?: () => void;
}
