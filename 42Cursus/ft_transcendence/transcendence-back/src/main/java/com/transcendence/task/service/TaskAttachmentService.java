package com.transcendence.task.service;

import com.transcendence.task.entity.TaskAttachment;
import com.transcendence.task.entity.TaskSubmission;
import com.transcendence.task.repository.TaskAttachmentRepository;
import com.transcendence.task.repository.TaskSubmissionRepository;
import com.transcendence.user.entity.User;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;

@Service
@RequiredArgsConstructor
public class TaskAttachmentService {

    private final TaskAttachmentRepository attachmentRepository;
    private final TaskSubmissionRepository submissionRepository;
    private final FileStorageService fileStorageService;

    public TaskAttachment uploadForSubmission(Long submissionId, MultipartFile file, User uploader) {
        TaskSubmission submission = submissionRepository.findById(submissionId)
                .orElseThrow(() -> new RuntimeException("Submission not found"));

        if (!submission.getSubmittedBy().getId().equals(uploader.getId())) {
            throw new RuntimeException("Only the submitter can upload proof files");
        }

        String storedName = fileStorageService.store(file);

        TaskAttachment attachment = TaskAttachment.builder()
                .task(submission.getTask())
                .submission(submission)
                .uploadedBy(uploader)
                .fileName(file.getOriginalFilename() != null ? file.getOriginalFilename() : storedName)
                .mimeType(file.getContentType())
                .sizeBytes(file.getSize())
                .storageUrl(storedName)
                .build();

        return attachmentRepository.save(attachment);
    }

    public List<TaskAttachment> getBySubmission(Long submissionId) {
        return attachmentRepository.findBySubmissionId(submissionId);
    }
}
