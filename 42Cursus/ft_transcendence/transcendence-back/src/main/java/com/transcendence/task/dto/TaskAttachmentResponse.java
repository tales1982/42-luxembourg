package com.transcendence.task.dto;

import com.transcendence.task.entity.TaskAttachment;
import lombok.Builder;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@Builder
public class TaskAttachmentResponse {

    private Long id;
    private Long submissionId;
    private String fileName;
    private String mimeType;
    private Long sizeBytes;
    private String url;
    private LocalDateTime createdAt;

    public static TaskAttachmentResponse fromEntity(TaskAttachment attachment, String baseUrl) {
        return TaskAttachmentResponse.builder()
                .id(attachment.getId())
                .submissionId(attachment.getSubmission() != null ? attachment.getSubmission().getId() : null)
                .fileName(attachment.getFileName())
                .mimeType(attachment.getMimeType())
                .sizeBytes(attachment.getSizeBytes())
                .url(baseUrl + "/api/files/" + attachment.getStorageUrl())
                .createdAt(attachment.getCreatedAt())
                .build();
    }
}
