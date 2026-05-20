import { useEffect, useState } from "react";
import { Container, Icon, Message, type ToastType} from "./Toast.styled";
import type { ToastData } from "../../interfaces/ToastData.interface";






let showToastFn: ((data: ToastData) => void) | null = null;

export function showToast(message: string, type: ToastType = "success", duration = 3000) {
  showToastFn?.({ message, type, duration });
}

export function ToastProvider() {
  const [toast, setToast] = useState<ToastData | null>(null);
  const [visible, setVisible] = useState(false);

  useEffect(() => {
    showToastFn = (data) => {
      setToast(data);
      setVisible(true);
    };
    return () => { showToastFn = null; };
  }, []);

  useEffect(() => {
    if (!visible || !toast) return;
    const timer = setTimeout(() => {
      setVisible(false);
      setTimeout(() => setToast(null), 300);
    }, toast.duration || 3000);
    return () => clearTimeout(timer);
  }, [visible, toast]);

  if (!toast) return null;

  const iconMap: Record<ToastType, string> = {
    success: "\u2713",
    error: "\u2717",
    warning: "\u26A0",
    info: "\u2139",
  };

  return (
    <Container $visible={visible}>
      <Icon $type={toast.type || "success"}>{iconMap[toast.type || "success"]}</Icon>
      <Message>{toast.message}</Message>
    </Container>
  );
}
