package com.transcendence.friend.dto;

import com.transcendence.user.entity.User;
import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class UserSearchResult {
    private Long id;
    private String email;
    private String displayName;

    public static UserSearchResult from(User u) {
        return UserSearchResult.builder()
                .id(u.getId())
                .email(u.getEmail())
                .displayName(u.getDisplayName())
                .build();
    }
}
