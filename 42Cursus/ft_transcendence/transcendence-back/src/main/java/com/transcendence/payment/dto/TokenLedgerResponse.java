package com.transcendence.payment.dto;

import com.transcendence.payment.entity.TokenLedger;
import com.transcendence.payment.entity.TransactionType;
import lombok.Builder;
import lombok.Data;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Data
@Builder
public class TokenLedgerResponse {

    private Long id;
    private TransactionType txType;
    private Long fromUserId;
    private Long toUserId;
    private Long taskId;
    private BigDecimal amount;
    private String chainTxHash;
    private LocalDateTime createdAt;

    public static TokenLedgerResponse fromEntity(TokenLedger ledger) {
        return TokenLedgerResponse.builder()
                .id(ledger.getId())
                .txType(ledger.getTxType())
                .fromUserId(ledger.getFromUser() != null ? ledger.getFromUser().getId() : null)
                .toUserId(ledger.getToUser() != null ? ledger.getToUser().getId() : null)
                .taskId(ledger.getTask() != null ? ledger.getTask().getId() : null)
                .amount(ledger.getAmount())
                .chainTxHash(ledger.getChainTxHash())
                .createdAt(ledger.getCreatedAt())
                .build();
    }
}
