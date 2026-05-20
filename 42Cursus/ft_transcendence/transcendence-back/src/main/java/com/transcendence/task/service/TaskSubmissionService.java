package com.transcendence.task.service;

import com.transcendence.blockchain.BlockchainService;
import com.transcendence.payment.service.TokenAccountService;
import com.transcendence.task.entity.*;
import com.transcendence.task.repository.TaskRepository;
import com.transcendence.task.repository.TaskSubmissionRepository;
import com.transcendence.user.entity.User;
import com.transcendence.user.entity.UserWallet;
import com.transcendence.user.repository.UserRepository;
import com.transcendence.user.repository.UserWalletRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Optional;

@Slf4j
@Service
@RequiredArgsConstructor
public class TaskSubmissionService {

    private final TaskSubmissionRepository submissionRepository;
    private final TaskRepository taskRepository;
    private final UserRepository userRepository;
    private final TaskService taskService;
    private final TokenAccountService tokenAccountService;
    private final BlockchainService blockchainService;
    private final UserWalletRepository userWalletRepository;

    public List<TaskSubmission> getSubmissionsByTask(Long taskId) {
        return submissionRepository.findByTaskId(taskId);
    }

    public Page<TaskSubmission> getSubmissionsByUser(Long userId, Pageable pageable) {
        return submissionRepository.findBySubmittedById(userId, pageable);
    }

    public Optional<TaskSubmission> getSubmissionById(Long id) {
        return submissionRepository.findById(id);
    }

    @Transactional
    public TaskSubmission submitTask(Long taskId, Long userId, String proofText) {
        Task task = taskRepository.findById(taskId)
                .orElseThrow(() -> new RuntimeException("Task not found"));

        if (task.getStatus() != TaskStatus.IN_PROGRESS) {
            throw new RuntimeException("Task is not in progress");
        }

        if (task.getTakenBy() == null || !task.getTakenBy().getId().equals(userId)) {
            throw new RuntimeException("Only assigned user can submit");
        }

        User user = userRepository.findById(userId)
                .orElseThrow(() -> new RuntimeException("User not found"));

        TaskSubmission submission = TaskSubmission.builder()
                .task(task)
                .submittedBy(user)
                .proofText(proofText)
                .status(SubmissionStatus.SUBMITTED)
                .build();

        taskService.updateTaskStatus(taskId, TaskStatus.SUBMITTED, userId, "Task submitted for review");

        return submissionRepository.save(submission);
    }

    @Transactional
    public TaskSubmission approveSubmission(Long submissionId, Long reviewerId, String reviewNotes) {
        TaskSubmission submission = submissionRepository.findById(submissionId)
                .orElseThrow(() -> new RuntimeException("Submission not found"));

        Task task = submission.getTask();
        if (!task.getCreator().getId().equals(reviewerId)) {
            throw new RuntimeException("Only task creator can approve");
        }

        User reviewer = userRepository.findById(reviewerId)
                .orElseThrow(() -> new RuntimeException("User not found"));

        submission.setStatus(SubmissionStatus.APPROVED);
        submission.setReviewedBy(reviewer);
        submission.setReviewedAt(LocalDateTime.now());
        submission.setReviewNotes(reviewNotes);

        taskService.updateTaskStatus(task.getId(), TaskStatus.APPROVED, reviewerId, "Submission approved");

        // ── Token payout ────────────────────────────────────────────────────────
        User worker = task.getTakenBy();
        BigDecimal reward = task.getRewardAmount() != null ? task.getRewardAmount() : BigDecimal.ZERO;

        if (worker != null && reward.compareTo(BigDecimal.ZERO) > 0) {
            // 1. Try on-chain mint if worker has a primary wallet registered
            String txHash = null;
            Optional<UserWallet> workerWallet = userWalletRepository
                    .findByUserIdAndIsPrimaryTrue(worker.getId());

            if (workerWallet.isPresent()) {
                txHash = blockchainService.mintTaskReward(
                        workerWallet.get().getAddress(), reward, task.getId());
            } else {
                log.info("Worker {} has no primary wallet – skipping on-chain mint for task {}",
                        worker.getId(), task.getId());
            }

            // 2. Always record the payout in the off-chain ledger (txHash may be null)
            tokenAccountService.deposit(worker.getId(), reward, txHash);
        }
        // ────────────────────────────────────────────────────────────────────────

        return submissionRepository.save(submission);
    }

    @Transactional
    public TaskSubmission rejectSubmission(Long submissionId, Long reviewerId, String reviewNotes) {
        TaskSubmission submission = submissionRepository.findById(submissionId)
                .orElseThrow(() -> new RuntimeException("Submission not found"));

        Task task = submission.getTask();
        if (!task.getCreator().getId().equals(reviewerId)) {
            throw new RuntimeException("Only task creator can reject");
        }

        User reviewer = userRepository.findById(reviewerId)
                .orElseThrow(() -> new RuntimeException("User not found"));

        submission.setStatus(SubmissionStatus.REJECTED);
        submission.setReviewedBy(reviewer);
        submission.setReviewedAt(LocalDateTime.now());
        submission.setReviewNotes(reviewNotes);

        taskService.updateTaskStatus(task.getId(), TaskStatus.IN_PROGRESS, reviewerId,
                "Submission rejected: " + reviewNotes);

        return submissionRepository.save(submission);
    }
}
