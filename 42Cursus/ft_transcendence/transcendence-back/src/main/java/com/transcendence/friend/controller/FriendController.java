package com.transcendence.friend.controller;

import com.transcendence.friend.dto.FriendResponse;
import com.transcendence.friend.dto.UserSearchResult;
import com.transcendence.friend.service.FriendService;
import com.transcendence.user.entity.User;
import com.transcendence.user.repository.UserRepository;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.tags.Tag;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/friends")
@RequiredArgsConstructor
@Tag(name = "Amigos", description = "Gerenciamento de amizades")
public class FriendController {

    private final FriendService friendService;
    private final UserRepository userRepository;

    @GetMapping
    @Operation(summary = "Listar amigos aceitos")
    public ResponseEntity<List<FriendResponse>> listFriends(@AuthenticationPrincipal User user) {
        return ResponseEntity.ok(friendService.listFriends(user.getId()));
    }

    @GetMapping("/pending/received")
    @Operation(summary = "Pedidos de amizade recebidos (pendentes)")
    public ResponseEntity<List<FriendResponse>> pendingReceived(@AuthenticationPrincipal User user) {
        return ResponseEntity.ok(friendService.listPendingReceived(user.getId()));
    }

    @GetMapping("/pending/sent")
    @Operation(summary = "Pedidos de amizade enviados (pendentes)")
    public ResponseEntity<List<FriendResponse>> pendingSent(@AuthenticationPrincipal User user) {
        return ResponseEntity.ok(friendService.listPendingSent(user.getId()));
    }

    @PostMapping("/request")
    @Operation(summary = "Enviar pedido de amizade por email")
    public ResponseEntity<FriendResponse> sendRequest(
            @AuthenticationPrincipal User user,
            @RequestParam String email) {
        return ResponseEntity.ok(friendService.sendRequest(user.getId(), email));
    }

    @PostMapping("/request/user/{targetUserId}")
    @Operation(summary = "Enviar pedido de amizade por ID de usuario")
    public ResponseEntity<FriendResponse> sendRequestById(
            @AuthenticationPrincipal User user,
            @PathVariable Long targetUserId) {
        User target = userRepository.findById(targetUserId)
                .orElseThrow(() -> new RuntimeException("User not found"));
        return ResponseEntity.ok(friendService.sendRequest(user.getId(), target.getEmail()));
    }

    @PostMapping("/{id}/accept")
    @Operation(summary = "Aceitar pedido de amizade")
    public ResponseEntity<FriendResponse> accept(
            @AuthenticationPrincipal User user,
            @PathVariable Long id) {
        return ResponseEntity.ok(friendService.accept(id, user.getId()));
    }

    @PostMapping("/{id}/reject")
    @Operation(summary = "Recusar pedido de amizade")
    public ResponseEntity<Map<String, String>> reject(
            @AuthenticationPrincipal User user,
            @PathVariable Long id) {
        friendService.reject(id, user.getId());
        return ResponseEntity.ok(Map.of("message", "Friend request rejected"));
    }

    @DeleteMapping("/{id}")
    @Operation(summary = "Remover amigo")
    public ResponseEntity<Map<String, String>> remove(
            @AuthenticationPrincipal User user,
            @PathVariable Long id) {
        friendService.remove(id, user.getId());
        return ResponseEntity.ok(Map.of("message", "Friend removed"));
    }

    @GetMapping("/search")
    @Operation(summary = "Buscar usuarios por email ou nome")
    public ResponseEntity<List<UserSearchResult>> searchUsers(
            @RequestParam String q) {
        if (q == null || q.trim().length() < 2) {
            return ResponseEntity.ok(List.of());
        }
        List<UserSearchResult> results = userRepository.findAll().stream()
                .filter(u -> u.getEmail().toLowerCase().contains(q.toLowerCase())
                        || (u.getDisplayName() != null && u.getDisplayName().toLowerCase().contains(q.toLowerCase())))
                .limit(10)
                .map(UserSearchResult::from)
                .toList();
        return ResponseEntity.ok(results);
    }
}
