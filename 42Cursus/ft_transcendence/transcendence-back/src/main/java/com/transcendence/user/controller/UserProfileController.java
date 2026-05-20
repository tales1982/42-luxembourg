package com.transcendence.user.controller;

import com.transcendence.task.service.FileStorageService;
import com.transcendence.user.dto.UserProfileRequest;
import com.transcendence.user.dto.UserProfileResponse;
import com.transcendence.user.entity.User;
import com.transcendence.user.service.UserProfileService;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.tags.Tag;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ContentDisposition;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.time.LocalDateTime;
import java.util.LinkedHashMap;
import java.util.Map;

@RestController
@RequestMapping("/api/profile")
@RequiredArgsConstructor
@Tag(name = "Perfil", description = "Gerenciamento de perfil do usuario")
public class UserProfileController {

    private final UserProfileService profileService;
    private final FileStorageService fileStorageService;

    @GetMapping
    @Operation(summary = "Meu perfil", description = "Retorna o perfil do usuario autenticado")
    public ResponseEntity<UserProfileResponse> getMyProfile(@AuthenticationPrincipal User user) {
        return profileService.getProfile(user.getId())
                .map(UserProfileResponse::fromEntity)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @GetMapping("/{userId}")
    @Operation(summary = "Buscar perfil por ID", description = "Retorna o perfil de um usuario especifico")
    public ResponseEntity<UserProfileResponse> getProfile(@PathVariable Long userId) {
        return profileService.getProfile(userId)
                .map(UserProfileResponse::fromEntity)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping(value = "/avatar", consumes = MediaType.MULTIPART_FORM_DATA_VALUE)
    @Operation(summary = "Upload de avatar", description = "Faz upload da foto de perfil do usuario")
    public ResponseEntity<UserProfileResponse> uploadAvatar(
            @AuthenticationPrincipal User user,
            @RequestParam("file") MultipartFile file) {
        String contentType = file.getContentType();
        if (contentType == null || !contentType.startsWith("image/")) {
            return ResponseEntity.badRequest().build();
        }
        if (file.getSize() > 5 * 1024 * 1024) {
            return ResponseEntity.badRequest().build();
        }
        String storedName = fileStorageService.store(file);
        String avatarUrl = "/api/files/" + storedName;
        var profile = profileService.updateAvatar(user.getId(), avatarUrl);
        return ResponseEntity.ok(UserProfileResponse.fromEntity(profile));
    }

    @GetMapping("/export")
    @Operation(summary = "Exportar meus dados (GDPR)", description = "Retorna todos os dados do usuario em JSON para download")
    public ResponseEntity<Map<String, Object>> exportMyData(@AuthenticationPrincipal User user) {
        Map<String, Object> data = new LinkedHashMap<>();
        data.put("exportedAt", LocalDateTime.now().toString());
        data.put("userId", user.getId());
        data.put("email", user.getEmail());
        data.put("displayName", user.getDisplayName());
        data.put("createdAt", user.getCreatedAt() != null ? user.getCreatedAt().toString() : null);
        profileService.getProfile(user.getId()).ifPresent(profile -> {
            Map<String, Object> profileMap = new LinkedHashMap<>();
            profileMap.put("fullName", profile.getFullName());
            profileMap.put("country", profile.getCountry());
            profileMap.put("phone", profile.getPhone());
            profileMap.put("address", profile.getAddress());
            profileMap.put("avatarUrl", profile.getAvatarUrl());
            data.put("profile", profileMap);
        });

        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.APPLICATION_JSON);
        headers.setContentDisposition(
            ContentDisposition.attachment().filename("my-data.json").build()
        );
        return ResponseEntity.ok().headers(headers).body(data);
    }

    @PutMapping
    @Operation(summary = "Atualizar meu perfil", description = "Atualiza o perfil do usuario autenticado")
    public ResponseEntity<UserProfileResponse> updateProfile(
            @AuthenticationPrincipal User user,
            @Valid @RequestBody UserProfileRequest request) {
        var profile = profileService.createOrUpdateProfile(
                user.getId(),
                request.getFullName(),
                request.getCountry(),
                request.getPhone(),
                request.getAddress(),
                request.getAvatarUrl()
        );
        return ResponseEntity.ok(UserProfileResponse.fromEntity(profile));
    }
}
