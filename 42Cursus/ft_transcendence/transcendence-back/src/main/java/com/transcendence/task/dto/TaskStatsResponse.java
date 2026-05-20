package com.transcendence.task.dto;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class TaskStatsResponse {
    private long totalCreated;
    private long openCreated;
    private long completedCreated;   // APPROVED tasks I created
    private long cancelledCreated;
    private long totalTaken;
    private long inProgressTaken;
    private long completedTaken;     // APPROVED tasks I executed
}
