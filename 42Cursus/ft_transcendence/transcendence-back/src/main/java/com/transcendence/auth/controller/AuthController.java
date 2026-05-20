package com.transcendence.auth.controller;

import com.transcendence.auth.dto.*;
import com.transcendence.auth.service.AuthService;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.tags.Tag;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@RestController
@RequestMapping("/api/auth")
@RequiredArgsConstructor
@Tag(name = "Autenticacao", description = "Registro e login de usuarios")
public class AuthController {

    private final AuthService authService;

    @PostMapping("/register")
    @Operation(summary = "Registrar novo usuario")
    public ResponseEntity<AuthResponse> register(@Valid @RequestBody RegisterRequest request) {
        return ResponseEntity.ok(authService.register(request));
    }

    @PostMapping("/login")
    @Operation(summary = "Fazer login — retorna JWT ou challenge de 2FA")
    public ResponseEntity<AuthResponse> login(@Valid @RequestBody LoginRequest request) {
        return ResponseEntity.ok(authService.login(request));
    }

    // ── 2FA endpoints ──────────────────────────────────────────────────────────

    @PostMapping("/2fa/verify")
    @Operation(summary = "Verificar código TOTP após login com 2FA ativo")
    public ResponseEntity<AuthResponse> verify2fa(@Valid @RequestBody TwoFactorVerifyRequest request) {
        return ResponseEntity.ok(authService.verify2fa(request));
    }

    @PostMapping("/2fa/setup")
    @Operation(summary = "Iniciar configuração de 2FA — gera segredo e QR code")
    public ResponseEntity<TwoFactorSetupResponse> setup2fa(@AuthenticationPrincipal UserDetails user) {
        return ResponseEntity.ok(authService.setup2fa(user.getUsername()));
    }

    @PostMapping("/2fa/enable")
    @Operation(summary = "Confirmar código TOTP e ativar 2FA")
    public ResponseEntity<Map<String, String>> enable2fa(
            @AuthenticationPrincipal UserDetails user,
            @Valid @RequestBody TwoFactorCodeRequest request) {
        authService.enable2fa(user.getUsername(), request.getCode());
        return ResponseEntity.ok(Map.of("message", "2FA enabled successfully"));
    }

    @PostMapping("/2fa/disable")
    @Operation(summary = "Desativar 2FA (requer código TOTP válido)")
    public ResponseEntity<Map<String, String>> disable2fa(
            @AuthenticationPrincipal UserDetails user,
            @Valid @RequestBody TwoFactorCodeRequest request) {
        authService.disable2fa(user.getUsername(), request.getCode());
        return ResponseEntity.ok(Map.of("message", "2FA disabled successfully"));
    }

    @GetMapping("/2fa/status")
    @Operation(summary = "Verificar se 2FA está ativo para o usuário")
    public ResponseEntity<Map<String, Boolean>> get2faStatus(@AuthenticationPrincipal UserDetails user) {
        boolean enabled = authService.get2faStatus(user.getUsername());
        return ResponseEntity.ok(Map.of("enabled", enabled));
    }
}
