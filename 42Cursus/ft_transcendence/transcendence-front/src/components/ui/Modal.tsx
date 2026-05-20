import { useEffect, type PropsWithChildren } from "react";
import { Body, CloseBtn, Header, Overlay, Panel, Title } from "./Modal.styled";
import type { ModalProps } from "../../interfaces/ModalProps.interface";





export function Modal({ open, onClose, title, maxWidth, children }: PropsWithChildren<ModalProps>) {
  useEffect(() => {
    if (!open) return;
    const handleEsc = (e: KeyboardEvent) => {
      if (e.key === "Escape") onClose();
    };
    document.addEventListener("keydown", handleEsc);
    return () => document.removeEventListener("keydown", handleEsc);
  }, [open, onClose]);

  if (!open) return null;

  return (
    <Overlay onClick={(e) => e.target === e.currentTarget && onClose()}>
      <Panel $maxWidth={maxWidth}>
        <Header>
          <Title>{title}</Title>
          <CloseBtn onClick={onClose}>&times;</CloseBtn>
        </Header>
        <Body>{children}</Body>
      </Panel>
    </Overlay>
  );
}
