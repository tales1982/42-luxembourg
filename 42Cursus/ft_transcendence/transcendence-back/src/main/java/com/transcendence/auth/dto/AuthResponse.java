package com.transcendence.auth.dto;

import com.fasterxml.jackson.annotation.JsonInclude;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
@JsonInclude(JsonInclude.Include.NON_NULL)
public class AuthResponse {

    private String accessToken;
    private String email;
    private String displayName;

    // 2FA challenge fields (only populated when 2FA is required)
    private Boolean requiresTwoFactor;
    private String challengeToken;
}
