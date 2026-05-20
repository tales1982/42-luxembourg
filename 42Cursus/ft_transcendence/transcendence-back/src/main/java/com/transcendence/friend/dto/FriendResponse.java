package com.transcendence.friend.dto;

import com.fasterxml.jackson.annotation.JsonInclude;
import com.transcendence.friend.entity.Friend;
import com.transcendence.friend.entity.FriendStatus;
import com.transcendence.user.entity.User;
import lombok.Builder;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@Builder
@JsonInclude(JsonInclude.Include.NON_NULL)
public class FriendResponse {
    private Long id;
    private Long userId;
    private String email;
    private String displayName;
    private FriendStatus status;
    private boolean iAmRequester;
    private LocalDateTime createdAt;

    public static FriendResponse from(Friend f, Long currentUserId) {
        boolean iAmRequester = f.getRequester().getId().equals(currentUserId);
        User other = iAmRequester ? f.getAddressee() : f.getRequester();
        return FriendResponse.builder()
                .id(f.getId())
                .userId(other.getId())
                .email(other.getEmail())
                .displayName(other.getDisplayName())
                .status(f.getStatus())
                .iAmRequester(iAmRequester)
                .createdAt(f.getCreatedAt())
                .build();
    }
}
