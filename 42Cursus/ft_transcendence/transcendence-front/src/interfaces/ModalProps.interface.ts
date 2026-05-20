export interface ModalProps {
  open: boolean;
  onClose: () => void;
  title: string;
  maxWidth?: string;
}