package com.transcendence.auth.dto;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;
import lombok.Data;

@Data
public class TwoFactorCodeRequest {
    @NotBlank
    @Size(min = 6, max = 6)
    private String code;
}
