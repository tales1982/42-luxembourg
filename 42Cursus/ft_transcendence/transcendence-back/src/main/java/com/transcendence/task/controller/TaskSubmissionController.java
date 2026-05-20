package com.transcendence.task.controller;

import com.transcendence.task.dto.ReviewSubmissionRequest;
import com.transcendence.task.dto.TaskAttachmentResponse;
import com.transcendence.task.dto.TaskSubmissionRequest;
import com.transcendence.task.dto.TaskSubmissionResponse;
import com.transcendence.task.service.TaskAttachmentService;
import com.transcendence.task.service.TaskSubmissionService;
import com.transcendence.user.entity.User;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.tags.Tag;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springdoc.core.annotations.ParameterObject;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/api/submissions")
@RequiredArgsConstructor
@Tag(name = "Entregas", description = "Submissao e revisao de entregas de tasks")
public class TaskSubmissionController {

    private final TaskSubmissionService submissionService;
    private final TaskAttachmentService attachmentService;

    @GetMapping("/task/{taskId}")
    @Operation(summary = "Listar entregas de uma task", description = "Retorna todas as entregas feitas para uma task")
    public ResponseEntity<List<TaskSubmissionResponse>> getTaskSubmissions(@PathVariable Long taskId) {
        var submissions = submissionService.getSubmissionsByTask(taskId)
                .stream()
                .map(TaskSubmissionResponse::fromEntity)
                .collect(Collectors.toList());
        return ResponseEntity.ok(submissions);
    }

    @GetMapping("/my")
    @Operation(summary = "Minhas entregas", description = "Retorna as entregas do usuario autenticado")
    public ResponseEntity<Page<TaskSubmissionResponse>> getMySubmissions(
            @AuthenticationPrincipal User user,
            @ParameterObject Pageable pageable) {
        var submissions = submissionService.getSubmissionsByUser(user.getId(), pageable)
                .map(TaskSubmissionResponse::fromEntity);
        return ResponseEntity.ok(submissions);
    }

    @GetMapping("/{id}")
    @Operation(summary = "Buscar entrega por ID")
    public ResponseEntity<TaskSubmissionResponse> getSubmission(@PathVariable Long id) {
        return submissionService.getSubmissionById(id)
                .map(TaskSubmissionResponse::fromEntity)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping("/task/{taskId}")
    @Operation(summary = "Entregar uma task", description = "Submete a prova de conclusao de uma task")
    public ResponseEntity<TaskSubmissionResponse> submitTask(
            @AuthenticationPrincipal User user,
            @PathVariable Long taskId,
            @Valid @RequestBody TaskSubmissionRequest request) {
        var submission = submissionService.submitTask(taskId, user.getId(), request.getProofText());
        return ResponseEntity.ok(TaskSubmissionResponse.fromEntity(submission));
    }

    @PostMapping(value = "/{id}/upload", consumes = MediaType.MULTIPART_FORM_DATA_VALUE)
    @Operation(summary = "Enviar arquivo comprovante", description = "Faz upload de um arquivo como prova de conclusao")
    public ResponseEntity<TaskAttachmentResponse> uploadProofFile(
            @AuthenticationPrincipal User user,
            @PathVariable Long id,
            @RequestParam("file") MultipartFile file,
            HttpServletRequest request) {
        var attachment = attachmentService.uploadForSubmission(id, file, user);
        String baseUrl = request.getScheme() + "://" + request.getServerName()
                + (request.getServerPort() != 80 && request.getServerPort() != 443
                        ? ":" + request.getServerPort() : "");
        return ResponseEntity.ok(TaskAttachmentResponse.fromEntity(attachment, baseUrl));
    }

    @GetMapping("/{id}/attachments")
    @Operation(summary = "Listar arquivos de uma entrega")
    public ResponseEntity<List<TaskAttachmentResponse>> getAttachments(
            @PathVariable Long id,
            HttpServletRequest request) {
        String baseUrl = request.getScheme() + "://" + request.getServerName()
                + (request.getServerPort() != 80 && request.getServerPort() != 443
                        ? ":" + request.getServerPort() : "");
        var attachments = attachmentService.getBySubmission(id).stream()
                .map(a -> TaskAttachmentResponse.fromEntity(a, baseUrl))
                .collect(Collectors.toList());
        return ResponseEntity.ok(attachments);
    }

    @PostMapping("/{id}/review")
    @Operation(summary = "Revisar uma entrega", description = "Aprova ou rejeita a entrega de uma task")
    public ResponseEntity<TaskSubmissionResponse> reviewSubmission(
            @AuthenticationPrincipal User user,
            @PathVariable Long id,
            @Valid @RequestBody ReviewSubmissionRequest request) {
        var submission = request.getApproved()
                ? submissionService.approveSubmission(id, user.getId(), request.getReviewNotes())
                : submissionService.rejectSubmission(id, user.getId(), request.getReviewNotes());
        return ResponseEntity.ok(TaskSubmissionResponse.fromEntity(submission));
    }
}
