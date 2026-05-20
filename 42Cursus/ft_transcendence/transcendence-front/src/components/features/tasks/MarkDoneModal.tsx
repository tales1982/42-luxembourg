import { useState, useRef } from "react";
import { useTranslation } from "react-i18next";
import { Modal } from "../../ui/Modal";
import { TextArea, Label, FormGroup } from "../../ui/Input";
import { Button } from "../../ui/Button";
import { submissionApi } from "../../../lib/api";
import { showToast } from "../../ui/Toast";
import { Footer, Form, UploadSub, UploadText, UploadZone, SelectedFile, RemoveFile } from "./MarkDoneModal.styled";
import type { MarkDoneModalProps } from "../../../interfaces/MarkDoneModalProps.interface";

const ACCEPTED = "image/png,image/jpeg,image/jpg,application/pdf";
const MAX_BYTES = 10 * 1024 * 1024; // 10 MB

export function MarkDoneModal({ open, onClose, taskId, onSubmitted }: MarkDoneModalProps) {
  const { t } = useTranslation();
  const [proofText, setProofText] = useState("");
  const [file, setFile] = useState<File | null>(null);
  const [loading, setLoading] = useState(false);
  const inputRef = useRef<HTMLInputElement>(null);

  function handleFileChange(e: React.ChangeEvent<HTMLInputElement>) {
    const selected = e.target.files?.[0];
    if (!selected) return;
    if (selected.size > MAX_BYTES) {
      showToast(t("tasks.fileTooLarge"), "error");
      return;
    }
    setFile(selected);
  }

  function handleDrop(e: React.DragEvent) {
    e.preventDefault();
    const dropped = e.dataTransfer.files[0];
    if (!dropped) return;
    if (dropped.size > MAX_BYTES) {
      showToast(t("tasks.fileTooLarge"), "error");
      return;
    }
    setFile(dropped);
  }

  function resetForm() {
    setProofText("");
    setFile(null);
    if (inputRef.current) inputRef.current.value = "";
  }

  async function handleSubmit(e: { preventDefault(): void }) {
    e.preventDefault();
    if (!taskId) return;
    setLoading(true);
    try {
      const submission = await submissionApi.submitTask(taskId, { proofText: proofText || undefined });

      if (file) {
        try {
          await submissionApi.uploadProofFile(submission.id, file);
        } catch {
          showToast(t("tasks.fileUploadError"), "error");
        }
      }

      showToast(t("tasks.submitted"));
      resetForm();
      onSubmitted?.();
      onClose();
    } catch {
      showToast(t("tasks.submitError"), "error");
    } finally {
      setLoading(false);
    }
  }

  return (
    <Modal open={open} onClose={onClose} title={t("tasks.markDone")} maxWidth="480px">
      <Form onSubmit={handleSubmit}>
        <FormGroup>
          <Label>{t("tasks.proofDescription")} *</Label>
          <TextArea
            value={proofText}
            onChange={(e) => setProofText(e.target.value)}
            placeholder={t("tasks.proofPlaceholder")}
            required
          />
        </FormGroup>

        <FormGroup>
          <Label>{t("tasks.uploadProof")}</Label>
          <UploadZone
            onClick={() => inputRef.current?.click()}
            onDrop={handleDrop}
            onDragOver={(e) => e.preventDefault()}
          >
            <UploadText>{t("tasks.uploadClick")}</UploadText>
            <UploadSub>PNG, JPG, PDF — max 10MB</UploadSub>
          </UploadZone>

          <input
            ref={inputRef}
            type="file"
            accept={ACCEPTED}
            style={{ display: "none" }}
            onChange={handleFileChange}
          />

          {file && (
            <SelectedFile>
              📎 {file.name} ({(file.size / 1024).toFixed(0)} KB)
              <RemoveFile type="button" onClick={() => setFile(null)}>✕</RemoveFile>
            </SelectedFile>
          )}
        </FormGroup>

        <Footer>
          <Button type="button" $variant="secondary" onClick={onClose}>
            {t("common.cancel")}
          </Button>
          <Button type="submit" disabled={loading}>
            {loading ? t("common.loading") : t("tasks.submitProof")}
          </Button>
        </Footer>
      </Form>
    </Modal>
  );
}
