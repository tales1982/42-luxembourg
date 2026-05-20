package com.transcendence.common.config;

import com.transcendence.task.entity.Task;
import com.transcendence.task.repository.TaskRepository;
import com.transcendence.user.entity.User;
import com.transcendence.user.repository.UserRepository;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.ApplicationArguments;
import org.springframework.boot.ApplicationRunner;
import org.springframework.core.annotation.Order;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Component;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.List;

@Slf4j
@Component
@Order(1)
@RequiredArgsConstructor
public class DataSeeder implements ApplicationRunner {

    private final UserRepository userRepository;
    private final TaskRepository taskRepository;
    private final PasswordEncoder passwordEncoder;

    private static final String DEFAULT_PASSWORD = "Password123!";

    private static final List<String[]> TASK_DATA = List.of(
        new String[]{"Build REST API", "Develop a RESTful API with CRUD operations, input validation, and JWT authentication. Document all endpoints using Swagger/OpenAPI.", "50"},
        new String[]{"Design UI Mockups", "Create high-fidelity wireframes for the main application screens using Figma. Include mobile and desktop breakpoints.", "80"},
        new String[]{"Write Unit Tests", "Implement unit and integration tests achieving at least 80% code coverage using JUnit 5 and Mockito.", "60"},
        new String[]{"Setup CI/CD Pipeline", "Configure automated build, test, and deployment pipeline using GitHub Actions. Include staging and production environments.", "100"},
        new String[]{"Database Optimization", "Analyze slow query logs, add appropriate indexes, and rewrite inefficient queries. Target: all queries under 100ms.", "120"},
        new String[]{"Code Review", "Review open pull requests, provide constructive feedback, identify bugs and suggest improvements following best practices.", "40"},
        new String[]{"API Documentation", "Write comprehensive API documentation using Swagger/OpenAPI 3.0. Include request/response examples for every endpoint.", "70"},
        new String[]{"Fix Security Vulnerabilities", "Audit the authentication flow, fix reported XSS and CSRF vulnerabilities, and implement proper input sanitization.", "150"},
        new String[]{"Performance Tuning", "Profile the application with JProfiler, identify memory leaks and CPU bottlenecks, optimize to achieve sub-200ms response times.", "130"},
        new String[]{"Deploy to Production", "Deploy the application to the production server using a blue-green deployment strategy with zero downtime and automated rollback.", "200"}
    );

    @Override
    public void run(ApplicationArguments args) {
        log.info("[DataSeeder] Starting data seeding...");
        User user1 = seedUser("user@email.com", "User One");
        User user2 = seedUser("user2@email.com", "User Two");
        seedTasks(user1, 10);
        seedTasks(user2, 5);
        log.info("[DataSeeder] Data seeding complete.");
    }

    private User seedUser(String email, String displayName) {
        if (userRepository.existsByEmail(email)) {
            log.info("[DataSeeder] User '{}' already exists, skipping.", email);
            return userRepository.findByEmail(email).orElseThrow();
        }

        User user = User.builder()
                .email(email)
                .password(passwordEncoder.encode(DEFAULT_PASSWORD))
                .displayName(displayName)
                .build();

        User saved = userRepository.save(user);
        log.info("[DataSeeder] Created user: {} (password: {})", email, DEFAULT_PASSWORD);
        return saved;
    }

    @SuppressWarnings("null")
    private void seedTasks(User creator, int count) {
        long existing = taskRepository.countByCreatorId(creator.getId());
        if (existing > 0) {
            log.info("[DataSeeder] User '{}' already has {} task(s), skipping.", creator.getEmail(), existing);
            return;
        }

        for (int i = 0; i < count; i++) {
            String[] data = TASK_DATA.get(i % TASK_DATA.size());
            Task task = Task.builder()
                    .title(data[0])
                    .description(data[1])
                    .rewardAmount(new BigDecimal(data[2]))
                    .currency("ZION")
                    .creator(creator)
                    .deadlineAt(LocalDateTime.now().plusDays(30L + i * 5))
                    .build();
            Task saved = taskRepository.save(task);
            log.debug("[DataSeeder] Saved task id={} for '{}'", saved.getId(), creator.getEmail());
        }

        log.info("[DataSeeder] Created {} task(s) for user '{}'.", count, creator.getEmail());
    }
}
