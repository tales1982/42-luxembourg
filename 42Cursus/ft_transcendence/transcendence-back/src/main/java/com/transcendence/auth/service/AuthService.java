package com.transcendence.auth.service;

import com.transcendence.auth.dto.*;
import com.transcendence.common.security.JwtService;
import com.transcendence.user.entity.User;
import com.transcendence.user.repository.UserRepository;
import com.transcendence.user.service.UserService;
import lombok.RequiredArgsConstructor;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
@RequiredArgsConstructor
public class AuthService {

    private final UserService userService;
    private final UserRepository userRepository;
    private final PasswordEncoder passwordEncoder;
    private final JwtService jwtService;
    private final AuthenticationManager authenticationManager;
    private final TotpService totpService;

    public AuthResponse register(RegisterRequest request) {
        if (userService.existsByEmail(request.getEmail())) {
            throw new RuntimeException("Email already registered");
        }

        var user = User.builder()
                .email(request.getEmail())
                .password(passwordEncoder.encode(request.getPassword()))
                .displayName(request.getDisplayName() != null ? request.getDisplayName() : request.getEmail())
                .build();

        userService.save(user);
        var token = jwtService.generateToken(user);

        return AuthResponse.builder()
                .accessToken(token)
                .email(user.getEmail())
                .displayName(user.getDisplayName())
                .build();
    }

    public AuthResponse login(LoginRequest request) {
        authenticationManager.authenticate(
                new UsernamePasswordAuthenticationToken(request.getEmail(), request.getPassword())
        );

        var user = userService.findByEmail(request.getEmail())
                .orElseThrow(() -> new RuntimeException("User not found"));

        if (user.isTwoFactorEnabled()) {
            String challengeToken = jwtService.generateChallengeToken(user);
            return AuthResponse.builder()
                    .requiresTwoFactor(true)
                    .challengeToken(challengeToken)
                    .build();
        }

        var token = jwtService.generateToken(user);
        return AuthResponse.builder()
                .accessToken(token)
                .email(user.getEmail())
                .displayName(user.getDisplayName())
                .build();
    }

    public AuthResponse verify2fa(TwoFactorVerifyRequest request) {
        String token = request.getChallengeToken();

        if (!jwtService.isChallengeToken(token)) {
            throw new RuntimeException("Invalid challenge token");
        }

        String email = jwtService.extractUsername(token);
        var user = userService.findByEmail(email)
                .orElseThrow(() -> new RuntimeException("User not found"));

        if (!totpService.verifyCode(user.getTwoFactorSecret(), request.getCode())) {
            throw new RuntimeException("Invalid 2FA code");
        }

        var accessToken = jwtService.generateToken(user);
        return AuthResponse.builder()
                .accessToken(accessToken)
                .email(user.getEmail())
                .displayName(user.getDisplayName())
                .build();
    }

    @Transactional
    public TwoFactorSetupResponse setup2fa(String email) {
        var user = userService.findByEmail(email)
                .orElseThrow(() -> new RuntimeException("User not found"));

        String secret = totpService.generateSecret();
        user.setTwoFactorSecretPending(secret);
        userRepository.save(user);

        String qrCodeBase64 = totpService.buildQrCodeBase64(secret, email);
        return TwoFactorSetupResponse.builder()
                .secret(secret)
                .qrCodeBase64(qrCodeBase64)
                .build();
    }

    @Transactional
    public void enable2fa(String email, String code) {
        var user = userService.findByEmail(email)
                .orElseThrow(() -> new RuntimeException("User not found"));

        String pending = user.getTwoFactorSecretPending();
        if (pending == null) throw new RuntimeException("No pending 2FA setup. Call /setup first.");
        if (!totpService.verifyCode(pending, code)) throw new RuntimeException("Invalid 2FA code");

        user.setTwoFactorSecret(pending);
        user.setTwoFactorSecretPending(null);
        user.setTwoFactorEnabled(true);
        userRepository.save(user);
    }

    @Transactional
    public void disable2fa(String email, String code) {
        var user = userService.findByEmail(email)
                .orElseThrow(() -> new RuntimeException("User not found"));

        if (!user.isTwoFactorEnabled()) throw new RuntimeException("2FA is not enabled");
        if (!totpService.verifyCode(user.getTwoFactorSecret(), code)) throw new RuntimeException("Invalid 2FA code");

        user.setTwoFactorEnabled(false);
        user.setTwoFactorSecret(null);
        user.setTwoFactorSecretPending(null);
        userRepository.save(user);
    }

    public boolean get2faStatus(String email) {
        return userService.findByEmail(email)
                .map(User::isTwoFactorEnabled)
                .orElse(false);
    }
}
