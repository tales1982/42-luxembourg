package com.transcendence.payment.controller;

import com.transcendence.payment.dto.DepositRequest;
import com.transcendence.payment.dto.TokenAccountResponse;
import com.transcendence.payment.dto.TokenLedgerResponse;
import com.transcendence.payment.dto.WithdrawRequest;
import com.transcendence.payment.service.TokenAccountService;
import com.transcendence.user.entity.User;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.tags.Tag;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/account")
@RequiredArgsConstructor
@Tag(name = "Conta de Tokens", description = "Depositos e saques de tokens")
public class TokenAccountController {

    private final TokenAccountService accountService;

    @GetMapping
    @Operation(summary = "Minha conta", description = "Retorna o saldo da conta do usuario")
    public ResponseEntity<TokenAccountResponse> getMyAccount(@AuthenticationPrincipal User user) {
        var account = accountService.getOrCreateAccount(user.getId());
        return ResponseEntity.ok(TokenAccountResponse.fromEntity(account));
    }

    @GetMapping("/ledger")
    @Operation(summary = "Historico de transacoes", description = "Retorna o historico de transacoes do usuario")
    public ResponseEntity<Page<TokenLedgerResponse>> getMyLedger(
            @AuthenticationPrincipal User user,
            @RequestParam(defaultValue = "0") int page,
            @RequestParam(defaultValue = "20") int size) {
        var pageable = PageRequest.of(page, size, Sort.by("createdAt").descending());
        return ResponseEntity.ok(accountService.getUserLedger(user.getId(), pageable));
    }

    @GetMapping("/{userId}")
    @Operation(summary = "Conta por ID de usuario", description = "Retorna a conta de tokens de um usuario")
    public ResponseEntity<TokenAccountResponse> getAccount(@PathVariable Long userId) {
        return accountService.getAccount(userId)
                .map(TokenAccountResponse::fromEntity)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping("/deposit")
    @Operation(summary = "Depositar tokens", description = "Adiciona tokens na conta do usuario")
    public ResponseEntity<TokenAccountResponse> deposit(
            @AuthenticationPrincipal User user,
            @Valid @RequestBody DepositRequest request) {
        var account = accountService.deposit(user.getId(), request.getAmount(), request.getChainTxHash());
        return ResponseEntity.ok(TokenAccountResponse.fromEntity(account));
    }

    @PostMapping("/withdraw")
    @Operation(summary = "Sacar tokens", description = "Retira tokens da conta do usuario")
    public ResponseEntity<TokenAccountResponse> withdraw(
            @AuthenticationPrincipal User user,
            @Valid @RequestBody WithdrawRequest request) {
        var account = accountService.withdraw(user.getId(), request.getAmount(), null);
        return ResponseEntity.ok(TokenAccountResponse.fromEntity(account));
    }
}
