package com.transcendence.chat.dto;

import com.transcendence.chat.entity.Conversation;
import com.transcendence.user.entity.User;
import lombok.Builder;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;

@Data
@Builder
public class ConversationResponse {

    private Long id;
    private Long taskId;
    private LocalDateTime createdAt;
    private List<Long> participantIds;
    private List<String> participantEmails;
    private List<String> participantDisplayNames;

    public static ConversationResponse fromEntity(Conversation conversation) {
        return ConversationResponse.builder()
                .id(conversation.getId())
                .taskId(conversation.getTask() != null ? conversation.getTask().getId() : null)
                .createdAt(conversation.getCreatedAt())
                .participantIds(conversation.getParticipants().stream()
                        .map(p -> p.getUser().getId())
                        .collect(Collectors.toList()))
                .participantEmails(conversation.getParticipants().stream()
                        .map(p -> p.getUser().getEmail())
                        .collect(Collectors.toList()))
                .participantDisplayNames(conversation.getParticipants().stream()
                        .map(p -> resolveDisplayName(p.getUser()))
                        .collect(Collectors.toList()))
                .build();
    }

    private static String resolveDisplayName(User user) {
        var displayName = user.getDisplayName();
        if (displayName != null && !displayName.trim().isEmpty()) {
            return displayName;
        }
        if (user.getProfile() != null) {
            var fullName = user.getProfile().getFullName();
            if (fullName != null && !fullName.trim().isEmpty()) {
                return fullName;
            }
        }
        return user.getEmail();
    }
}
