import { useState, useEffect } from "react";
import { useTranslation } from "react-i18next";
import { Modal } from "../../ui/Modal";
import { Input, TextArea, Label, FormGroup } from "../../ui/Input";
import { Button } from "../../ui/Button";
import { useAppDispatch, useAppSelector } from "../../../store/hooks";
import { fetchCategories, createTaskWithCategory } from "../../../store/slices/tasks.slice";
import { showToast } from "../../ui/Toast";
import { Form, Footer } from "./MarkDoneModal.styled";
import { CategoryWrapper, Row, SuggestionItem, SuggestionList } from "./NewTaskModal.styled";
import type { NewTaskModalProps } from "../../../interfaces/NewTaskModalProps.interface";
import { fetchAccount } from "../../../store/slices/payment.slice";

export function NewTaskModal({ open, onClose }: NewTaskModalProps) {
  const { t } = useTranslation();
  const dispatch = useAppDispatch();
  const { categories, loading } = useAppSelector((s) => s.tasks);
  const { account } = useAppSelector((s) => s.payment);

  const [title, setTitle] = useState("");
  const [description, setDescription] = useState("");
  const [categorySearch, setCategorySearch] = useState("");
  const [categoryId, setCategoryId] = useState<number | undefined>();
  const [showSuggestions, setShowSuggestions] = useState(false);
  const [reward, setReward] = useState("");
  const [location, setLocation] = useState("");
  const [deadline, setDeadline] = useState("");

  useEffect(() => {
    if (open) {
      if (categories.length === 0) dispatch(fetchCategories());
      dispatch(fetchAccount());
    }
  }, [open, categories.length, dispatch]);

  useEffect(() => {
    if (open) {
      const tomorrow = new Date();
      tomorrow.setDate(tomorrow.getDate() + 1);
      setDeadline(tomorrow.toISOString().slice(0, 16));
    }
  }, [open]);

  const filteredCategories = categories.filter((c) =>
    c.name.toLowerCase().includes(categorySearch.toLowerCase())
  );

  const availableBalance = account ? Number(account.availableBalance) : 0;
  const rewardNum = reward ? Number(reward) : 0;
  const insufficientBalance = rewardNum > 0 && rewardNum > availableBalance;

  function resetForm() {
    setTitle("");
    setDescription("");
    setCategorySearch("");
    setCategoryId(undefined);
    setReward("");
    setLocation("");
    setDeadline("");
  }

  async function handleSubmit(e: { preventDefault(): void }) {
    e.preventDefault();
    try {
      const result = await dispatch(
        createTaskWithCategory({
          title,
          description,
          categoryId,
          categoryName: categorySearch,
          rewardAmount: reward ? Number(reward) : undefined,
          locationText: location || undefined,
          deadlineAt: deadline || undefined,
        })
      );
      if (createTaskWithCategory.fulfilled.match(result)) {
        showToast(t("tasks.created"));
        resetForm();
        onClose();
      } else {
        showToast(t("tasks.createError"), "error");
      }
    } finally {
      // loading handled by slice
    }
  }

  return (
    <Modal open={open} onClose={onClose} title={t("tasks.newTask")}>
      <Form onSubmit={handleSubmit}>
        <FormGroup>
          <Label>{t("tasks.title")} *</Label>
          <Input value={title} onChange={(e) => setTitle(e.target.value)} required />
        </FormGroup>

        <FormGroup>
          <Label>{t("tasks.description")} *</Label>
          <TextArea
            value={description}
            onChange={(e) => setDescription(e.target.value)}
            required
          />
        </FormGroup>

        <FormGroup>
          <Label>{t("tasks.category")} *</Label>
          <CategoryWrapper>
            <Input
              value={categorySearch}
              onChange={(e) => {
                setCategorySearch(e.target.value);
                setShowSuggestions(true);
                setCategoryId(undefined);
              }}
              onFocus={() => setShowSuggestions(true)}
              onBlur={() => setTimeout(() => setShowSuggestions(false), 150)}
              placeholder={t("tasks.categoryPlaceholder")}
              required
            />
            {showSuggestions && categorySearch && filteredCategories.length > 0 && (
              <SuggestionList>
                {filteredCategories.map((c) => (
                  <SuggestionItem
                    key={c.id}
                    onClick={() => {
                      setCategorySearch(c.name);
                      setCategoryId(c.id);
                      setShowSuggestions(false);
                    }}
                  >
                    {c.name}
                  </SuggestionItem>
                ))}
              </SuggestionList>
            )}
          </CategoryWrapper>
        </FormGroup>

        <Row>
          <FormGroup>
            <Label>
              {t("tasks.reward")} (ZION) * &nbsp;
              <span style={{ fontWeight: 400, color: "var(--color-muted, #888)" }}>
                {t("wallet.available")}: {availableBalance.toFixed(2)}
              </span>
            </Label>
            <Input
              type="number"
              min="1"
              value={reward}
              onChange={(e) => setReward(e.target.value)}
              required
              style={insufficientBalance ? { borderColor: "#f87171" } : undefined}
            />
            {insufficientBalance && (
              <span style={{ fontSize: "0.78rem", color: "#f87171" }}>
                {t("tasks.insufficientBalance")}
              </span>
            )}
          </FormGroup>

          <FormGroup>
            <Label>{t("tasks.location")} *</Label>
            <Input
              value={location}
              onChange={(e) => setLocation(e.target.value)}
              required
            />
          </FormGroup>
        </Row>

        <FormGroup>
          <Label>{t("tasks.deadline")} *</Label>
          <Input
            type="datetime-local"
            value={deadline}
            onChange={(e) => setDeadline(e.target.value)}
            required
          />
        </FormGroup>

        <Footer>
          <Button type="button" $variant="secondary" onClick={onClose}>
            {t("common.cancel")}
          </Button>
          <Button type="submit" disabled={loading || insufficientBalance}>
            {loading ? t("common.loading") : t("tasks.createTask")}
          </Button>
        </Footer>
      </Form>
    </Modal>
  );
}
