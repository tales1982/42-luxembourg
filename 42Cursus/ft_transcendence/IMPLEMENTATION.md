# ft_transcendence — Documentação de Implementação

## Visão Geral

**ft_transcendence** é um marketplace de tarefas com sistema de tokens ERC-20 (ZION), chat em tempo real, sistema de amizades e autenticação com dois fatores. O projeto foi desenvolvido para o currículo da 42 Luxembourg com foco nos módulos de **Blockchain** e **Cibersegurança**.

---

## Arquitetura

```
┌─────────────────────────────────────────────────────────────────┐
│                        USUÁRIO (Browser)                        │
│                     http://localhost:3000                       │
└────────────────────────────┬────────────────────────────────────┘
                             │ HTTP
┌────────────────────────────▼────────────────────────────────────┐
│           WAF — Nginx + ModSecurity v3 + OWASP CRS              │
│                     port 80  (porta única)                      │
│   Bloqueia: SQL Injection · XSS · RCE · Command Injection       │
└──────┬──────────────────────────────────┬───────────────────────┘
       │ /api/** e /ws/**                  │ /*
       │ proxy_pass HTTPS                  │ proxy_pass HTTP
┌──────▼──────────────────┐   ┌───────────▼───────────────────────┐
│  BACKEND Spring Boot    │   │  FRONTEND React + Vite            │
│  port 8443 (HTTPS)      │   │  port 3000                        │
│  REST API · WebSocket   │   │  TanStack Router · Redux          │
└──────┬──────────────────┘   └───────────────────────────────────┘
       │
┌──────┴──────────────────────────────────────────────────────────┐
│  PostgreSQL (5432)   │  HashiCorp Vault (8200)                  │
│  Dados persistidos   │  jwt.secret · blockchain.private-key     │
└──────────────────────┴──────────────────────────────────────────┘
                       │
           ┌───────────▼───────────────────┐
           │  Sepolia Testnet (Ethereum)    │
           │  ZION ERC-20 Token Contract    │
           └───────────────────────────────┘
```

---

## Stack Tecnológica

### Backend
| Componente | Tecnologia |
|---|---|
| Framework | Spring Boot 3.4.1 |
| Linguagem | Java 21 |
| ORM | Spring Data JPA + Hibernate |
| Banco de dados | PostgreSQL 16 |
| Segurança | Spring Security + JWT (jjwt 0.12.6) |
| 2FA | dev.samstevens.totp 1.7.1 (TOTP RFC 6238) |
| Blockchain | Web3j 4.12.0 |
| Secrets | HashiCorp Vault (Spring Cloud Vault) |
| WebSocket | STOMP over SockJS |
| Documentação API | SpringDoc OpenAPI 2.8.14 (Swagger UI) |

### Frontend
| Componente | Tecnologia |
|---|---|
| Framework | React 19 + Vite |
| Linguagem | TypeScript 5.9 |
| Roteamento | TanStack Router 1.x (file-based) |
| Estado global | Redux Toolkit 2.x |
| HTTP client | Axios 1.x |
| Estilos | styled-components 6.x |
| i18n | i18next + react-i18next (EN / PT / FR) |
| WebSocket | STOMP.js + SockJS |
| Blockchain | wagmi 3.x + viem 2.x (MetaMask) |
| Formularios | react-hook-form + zod |

### WAF
| Componente | Tecnologia |
|---|---|
| Proxy reverso | Nginx 1.28 |
| WAF Engine | ModSecurity v3.0.14 |
| Regras | OWASP CRS 3.3.8 (928 regras) |
| Imagem base | owasp/modsecurity-crs:nginx-alpine |

---

## Módulos Implementados

### 1. Autenticação — JWT + 2FA (Módulo Cibersegurança)

#### Fluxo de login sem 2FA
```
POST /api/auth/login  →  { accessToken, email, displayName }
```

#### Fluxo de login com 2FA ativo
```
POST /api/auth/login  →  { requiresTwoFactor: true, challengeToken }
      ↓ (token JWT restrito, válido 5 min)
POST /api/auth/2fa/verify  →  { accessToken, email, displayName }
```

#### Endpoints de Autenticação

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `POST` | `/api/auth/register` | — | Criar conta |
| `POST` | `/api/auth/login` | — | Login (retorna JWT ou challenge) |
| `POST` | `/api/auth/2fa/verify` | — | Verificar código TOTP |
| `POST` | `/api/auth/2fa/setup` | JWT | Gerar segredo + QR code |
| `POST` | `/api/auth/2fa/enable` | JWT + código | Ativar 2FA |
| `POST` | `/api/auth/2fa/disable` | JWT + código | Desativar 2FA |
| `GET`  | `/api/auth/2fa/status` | JWT | Verificar status do 2FA |

#### Padrão TOTP
- **Algoritmo:** SHA-1 · **Dígitos:** 6 · **Período:** 30 segundos
- **Janela de tolerância:** ±1 período (clock drift)
- Compatível com **Google Authenticator**, **Authy**, **Microsoft Authenticator**
- QR code gerado como PNG base64 via ZxingPngQrGenerator

#### Estados Redux de autenticação
```
"guest" → login com senha → "2fa_pending" → verify code → "authenticated"
```

---

### 2. HashiCorp Vault (Módulo Cibersegurança)

Segredos armazenados no Vault ao invés de variáveis de ambiente:

| Segredo | Caminho no Vault |
|---|---|
| `jwt.secret` | `secret/transcendence` |
| `blockchain.private-key` | `secret/transcendence` |
| `spring.datasource.password` | `secret/transcendence` |

- Vault inicializado automaticamente via `vault-init` container no `docker-compose.yml`
- Spring Cloud Vault carrega os segredos no bootstrap da aplicação

---

### 3. Blockchain ERC-20 — Token ZION (Módulo Major)

#### Contratos
- Rede: **Sepolia Testnet** (Ethereum)
- Token: **ZION** — ERC-20 padrão

#### Fluxo de tokens

```
Usuário deposita ZION (MetaMask)
       ↓
Backend registra saldo off-chain (TokenAccount)
       ↓
Usuário cria task → saldo bloqueado (TaskEscrow)
       ↓
Executor completa task → criador aprova
       ↓
Backend chama mint() no contrato on-chain para o executor
Backend credita saldo off-chain
       ↓
Executor pode sacar → backend chama transfer() on-chain
```

#### Endpoints de Conta de Tokens (ZION off-chain)

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `GET` | `/api/account` | JWT | Meu saldo off-chain (available + locked) |
| `GET` | `/api/account/{userId}` | — | Saldo de outro usuário |
| `GET` | `/api/account/ledger` | JWT | Histórico de transações (paginado) |
| `POST` | `/api/account/deposit` | JWT | Registrar depósito (com txHash on-chain) |
| `POST` | `/api/account/withdraw` | JWT | Solicitar saque para carteira MetaMask |

#### Endpoints de Carteiras MetaMask

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `GET` | `/api/wallets` | JWT | Listar minhas carteiras conectadas |
| `GET` | `/api/wallets/primary` | JWT | Carteira principal |
| `POST` | `/api/wallets` | JWT | Conectar carteira MetaMask |
| `DELETE` | `/api/wallets/{walletId}` | JWT | Desconectar carteira |
| `PUT` | `/api/wallets/{walletId}/primary` | JWT | Definir carteira como principal |

#### Entidades de pagamento
- `TokenAccount` — saldo disponível e bloqueado por usuário
- `TokenLedger` — histórico de todas as transações
- `TaskEscrow` — escrow de recompensa por task (LOCKED → RELEASED / REFUNDED)
- `UserWallet` — endereços MetaMask associados ao usuário

---

### 4. Tasks (Marketplace)

#### Status de uma task
```
OPEN → IN_PROGRESS → SUBMITTED → APPROVED
                               → REJECTED (volta a IN_PROGRESS)
             ↓
         CANCELLED
```

#### Endpoints de Tasks

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `GET` | `/api/tasks` | — | Listar todas as tasks (paginado) |
| `GET` | `/api/tasks/open` | — | Apenas tasks abertas |
| `GET` | `/api/tasks/my-created` | JWT | Tasks criadas pelo usuário |
| `GET` | `/api/tasks/my-taken` | JWT | Tasks aceitas pelo usuário |
| `GET` | `/api/tasks/status/{status}` | — | Filtrar por status |
| `GET` | `/api/tasks/category/{id}` | — | Filtrar por categoria |
| `GET` | `/api/tasks/{id}` | — | Detalhe de uma task |
| `POST` | `/api/tasks` | JWT | Criar task |
| `POST` | `/api/tasks/{id}/take` | JWT | Aceitar task |
| `POST` | `/api/tasks/{id}/cancel` | JWT | Cancelar task |
| `GET` | `/api/tasks/my-stats` | JWT | Minhas estatísticas de tasks |
| `GET` | `/api/tasks/stats/{userId}` | — | Estatísticas de tasks de um usuário |

#### Endpoints de Submissões

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `GET` | `/api/submissions/my` | JWT | Minhas submissões (paginado) |
| `GET` | `/api/submissions/task/{id}` | JWT | Submissões de uma task |
| `POST` | `/api/submissions/task/{id}` | JWT | Submeter prova de conclusão |
| `POST` | `/api/submissions/{id}/review` | JWT | Aprovar / Rejeitar submissão |
| `POST` | `/api/submissions/{id}/upload` | JWT | Upload de arquivo de prova |
| `GET` | `/api/submissions/{id}/attachments` | JWT | Listar anexos |

---

### 5. Sistema de Amizades

#### Status de uma amizade
```
(sem relacionamento) → PENDING → ACCEPTED
                              → (rejeitado = deletado)
```

#### Endpoints de Amizades

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `GET` | `/api/friends` | JWT | Listar amigos aceitos |
| `GET` | `/api/friends/pending/received` | JWT | Pedidos recebidos |
| `GET` | `/api/friends/pending/sent` | JWT | Pedidos enviados |
| `POST` | `/api/friends/request?email=` | JWT | Enviar pedido por e-mail |
| `POST` | `/api/friends/request/user/{userId}` | JWT | Enviar pedido por ID |
| `POST` | `/api/friends/{id}/accept` | JWT | Aceitar pedido |
| `POST` | `/api/friends/{id}/reject` | JWT | Recusar pedido |
| `DELETE` | `/api/friends/{id}` | JWT | Remover amigo |
| `GET` | `/api/friends/search?q=` | JWT | Buscar usuários |

---

### 6. Chat em Tempo Real

#### Tecnologia
- WebSocket com protocolo STOMP
- SockJS como fallback HTTP
- Conversas ligadas a tasks ou mensagens diretas

#### Endpoints REST

| Método | Endpoint | Descrição |
|---|---|---|
| `GET` | `/api/conversations` | Minhas conversas |
| `GET` | `/api/conversations/{id}/messages` | Mensagens de uma conversa |
| `POST` | `/api/conversations/task/{taskId}` | Criar/abrir conversa de task |

#### Tópicos WebSocket
| Tópico | Direção | Descrição |
|---|---|---|
| `/app/chat.send` | Cliente → Servidor | Enviar mensagem |
| `/topic/conversation.{id}` | Servidor → Cliente | Receber mensagens |
| `/user/queue/notifications` | Servidor → Cliente | Notificações privadas |

---

### 7. Perfil de Usuário

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `GET` | `/api/profile` | JWT | Meu perfil |
| `GET` | `/api/profile/{userId}` | — | Perfil público de outro usuário |
| `PUT` | `/api/profile` | JWT | Atualizar perfil (fullName, country, phone, address, avatarUrl) |
| `POST` | `/api/profile/avatar` | JWT | Upload de foto de perfil (multipart/form-data, max 5 MB) |
| `GET` | `/api/profile/export` | JWT | Exportar dados pessoais em JSON (GDPR Art. 20) |

**Campos:** fullName, country (obrigatório), phone, address, avatarUrl
**Avatar:** enviado como `multipart/form-data`, aceita image/* até 5 MB. A URL retornada é `/api/files/{uuid}` e resolvida para `{API_BASE_URL}/api/files/{uuid}` no frontend.
**Export:** retorna `Content-Disposition: attachment; filename="my-data.json"` com todos os dados pessoais do usuário.

---

### 8. Avaliações (Reviews)

Sistema de avaliação entre usuários após conclusão de tasks.

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `POST` | `/api/reviews` | JWT | Criar avaliação (1–5 estrelas + comentário) |
| `GET` | `/api/reviews/task/{taskId}` | — | Avaliações de uma task |
| `GET` | `/api/reviews/user/{userId}` | — | Avaliações recebidas por um usuário (paginado) |
| `GET` | `/api/reviews/user/{userId}/stats` | — | Média e total de avaliações de um usuário |
| `GET` | `/api/reviews/{id}` | — | Buscar avaliação por ID |

---

### 9. Notificações

| Método | Endpoint | Descrição |
|---|---|---|
| `GET` | `/api/notifications` | Listar notificações (paginado, param: page, size) |
| `GET` | `/api/notifications/unread` | Notificações não lidas |
| `GET` | `/api/notifications/unread/count` | Contagem de não lidas |
| `POST` | `/api/notifications/{id}/read` | Marcar notificação como lida |
| `POST` | `/api/notifications/read-all` | Marcar todas como lidas |

**Tipos:** `NEW_MESSAGE`, `TASK_UPDATE`, `PAYMENT`

**Frontend:** Sidebar exibe badge com contagem (atualizado a cada 30s). Página `/notifications` mostra lista com ícones por tipo, destaque para não lidas e botão "Marcar todas como lidas".

---

### 10. Dashboard de Estatísticas (Bônus)

Dashboard pessoal exibindo:
- **Saldo ZION** disponível (off-chain)
- **Visão geral**: tasks criadas, aprovadas, aceitas, concluídas
- **Breakdown de tasks criadas**: barra de progresso Open / Completed / Cancelled
- **Breakdown de tasks aceitas**: barra de progresso In Progress / Completed

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `GET` | `/api/tasks/my-stats` | JWT | Estatísticas do usuário logado |
| `GET` | `/api/tasks/stats/{userId}` | JWT | Estatísticas de qualquer usuário |

---

### 11. Perfil Público de Usuário (Bônus)

Página `/users/:userId` exibindo:
- Avatar, nome completo, país
- Avaliação média em estrelas (1–5)
- Estatísticas de tasks (criadas, aprovadas, aceitas, concluídas)
- Saldo ZION disponível
- Lista de últimas 5 avaliações recebidas
- Botão "Add Friend" (envia pedido de amizade via `POST /api/friends/request/user/{userId}`)

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `POST` | `/api/friends/request/user/{userId}` | JWT | Enviar pedido de amizade por ID |

---

### 12. Exportação de Dados GDPR (Bônus)

Endpoint GDPR Article 20 — Portabilidade de dados:

| Método | Endpoint | Auth | Descrição |
|---|---|---|---|
| `GET` | `/api/profile/export` | JWT | Download dos dados pessoais em JSON |

**Resposta:** arquivo `my-data.json` com `Content-Disposition: attachment`, contendo:
- `userId`, `email`, `displayName` — dados da conta
- `fullName`, `country`, `phone`, `address`, `avatarUrl` — dados do perfil
- `exportedAt` — timestamp da exportação

**Frontend:** botão "↓ Exportar Meus Dados" na página de perfil, ao lado do botão de logout.

---

## Rotas do Frontend

### Páginas Públicas
| Rota | Descrição |
|---|---|
| `/` | Landing page |
| `/login` | Login |
| `/register` | Criar conta |
| `/2fa-verify` | Verificação de código 2FA |
| `/terms` | Termos de serviço |
| `/privacy` | Política de privacidade |

### Páginas Autenticadas
| Rota | Descrição |
|---|---|
| `/marketplace` | Marketplace de tasks abertas (busca por texto, filtro por categoria, ordenação por data/recompensa) |
| `/my-tasks` | Tasks criadas pelo usuário (aprovar/rejeitar submissões) |
| `/taken` | Tasks aceitas pelo usuário (enviar prova de conclusão) |
| `/friends` | Gerenciar amizades (lista, pedidos, busca de usuários) |
| `/history` | Histórico de tasks e submissões (abas: Criadas / Aceitas / Envios) |
| `/chat` | Chat em tempo real |
| `/wallet` | Carteira ZION: saldo on-chain (MetaMask) + off-chain, depósito, saque, histórico de transações |
| `/profile` | Editar perfil + upload de avatar + configurar 2FA + exportar dados GDPR |
| `/notifications` | Central de notificações (lidas/não lidas, marcar como lida) |
| `/dashboard` | Dashboard pessoal: saldo ZION, estatísticas de tasks, breakdown por status |
| `/users/:userId` | Perfil público de outro usuário (stats, reviews, botão add friend) |

---

## Banco de Dados — Tabelas Principais

| Tabela | Módulo | Descrição |
|---|---|---|
| `users` | Auth / User | Conta do usuário + campos 2FA |
| `user_profile` | User | Perfil público (nome, país, telefone) |
| `user_wallets` | Blockchain | Endereços de carteira MetaMask |
| `tasks` | Task | Tasks do marketplace |
| `task_submissions` | Task | Submissões de prova de conclusão |
| `task_submission_attachments` | Task | Arquivos anexados a submissões |
| `task_categories` | Task | Categorias das tasks |
| `task_tags` | Task | Tags das tasks |
| `task_tag_map` | Task | Relação N:N task ↔ tag |
| `task_status_history` | Task | Auditoria de mudanças de status |
| `token_accounts` | Payment | Saldo off-chain (available + locked) |
| `token_ledger` | Payment | Histórico de todas as transações |
| `task_escrow` | Payment | Recompensa bloqueada por task |
| `friends` | Friends | Relacionamentos de amizade |
| `conversations` | Chat | Conversas (task ou diretas) |
| `messages` | Chat | Mensagens das conversas |
| `reviews` | Review | Avaliações entre usuários |
| `notifications` | Notification | Notificações do sistema |

---

## Segurança

### JWT
- Algoritmo: HMAC-SHA256
- Segredo armazenado no **HashiCorp Vault**
- Expiração configurável via `jwt.expiration`
- **Challenge token** para 2FA: 5 minutos de validade, claim `scope: "2fa_challenge"`

### HTTPS
- Backend exposto apenas via HTTPS (porta 8443)
- Certificado autoassinado em desenvolvimento

### CORS
Origens permitidas:
- `http://localhost:3000`
- `http://localhost:5173`
- `https://*.devtunnels.ms` (para desenvolvimento remoto)

### Endpoints públicos
Não requerem autenticação:
- `/api/auth/**` — registro e login
- `/api/tasks/open` — tasks abertas (marketplace público)
- `/api/categories` — categorias
- `/api/files/**` — arquivos
- `/ws/**` — WebSocket

---

## Como Executar

### Pré-requisitos
- Docker + Docker Compose
- MetaMask (para funcionalidades blockchain)

### Subir o ambiente
```bash
make up
# ou
docker compose up -d
```

### Acessar
| Serviço | URL |
|---|---|
| Frontend | http://localhost:3000 |
| Backend API | https://localhost:8443/swagger-ui.html |
| HashiCorp Vault | http://localhost:8200 |

### Usuários de teste (seed)
| Email | Senha |
|---|---|
| user@email.com | password |
| user2@email.com | password |

---

## Variáveis de Ambiente (`.env`)

```env
# Frontend (transcendence-front/.env)
VITE_API_BASE_URL=http://localhost          # WAF/Nginx na porta 80
VITE_WS_URL=ws://localhost/ws
VITE_RPC_URL=https://eth-sepolia.g.alchemy.com/v2/<key>
VITE_ZION_TOKEN_ADDRESS=0x<contract_address>

# Backend (via Vault — transcendence-back/src/main/resources/bootstrap.yml)
# jwt.secret              → secret/transcendence
# blockchain.private-key  → secret/transcendence
# spring.datasource.password → secret/transcendence
```

---

## Swagger / OpenAPI

A documentação interativa da API está disponível em:

```
https://localhost:8443/swagger-ui.html
```

Grupos de endpoints:
- **Autenticacao** — registro, login, 2FA
- **Tasks** — marketplace, CRUD, aceitar, cancelar, estatísticas
- **Submissões** — envio de prova, aprovação, rejeição
- **Amigos** — pedidos, lista, busca
- **Perfil** — perfil público, avatar, exportação GDPR
- **Conta de Tokens** — saldo ZION off-chain, depósito, saque, histórico
- **Carteiras** — endereços MetaMask conectados
- **Chat** — conversas e mensagens
- **Avaliacoes** — reviews entre usuários, média, estatísticas
- **Notificações** — sistema de alertas

---

## Módulos 42 — Pontuação

> **Regra (subject v21.0):** Major = 2 pts · Minor = 1 pt · **Mínimo: 14 pontos** para validação.
> Bônus: módulos além dos 14 pts (máx. +5 pts).

### Módulos Obrigatórios (≥ 14 pts) ✅

| Módulo | Categoria | Tipo | Pts | Detalhes |
|---|---|---|:---:|---|
| Frameworks frontend + backend (React + Spring Boot) | Web | Major | **2** | React 19 + Vite / Spring Boot 3.4 |
| Real-time WebSocket (STOMP/SockJS) | Web | Major | **2** | Chat ao vivo, broadcasting |
| User Interaction (chat + perfil + amigos) | Web | Major | **2** | Mensagens, perfil público, sistema de amizades |
| ORM (Spring Data JPA + Hibernate) | Web | Minor | **1** | 18 tabelas, queries customizadas |
| Suporte multilíngue EN/PT/FR | Acessibilidade | Minor | **1** | react-i18next, language switcher |
| Standard User Management | User Management | Major | **2** | Perfil, avatar upload, amigos + status online |
| 2FA (TOTP) | User Management | Minor | **1** | RFC 6238, Google Authenticator |
| WAF/ModSecurity + HashiCorp Vault | Cybersecurity | Major | **2** | Nginx + OWASP CRS 3.3.8, Vault para secrets |
| **TOTAL OBRIGATÓRIO** | | | **13** | |

### Módulos Bônus ✅

| Módulo | Categoria | Tipo | Pts | Detalhes |
|---|---|---|:---:|---|
| ERC-20 Marketplace Blockchain (ZION Token) | Modules of choice | Minor | **+1** | Ver justificativa abaixo |
| Sistema de Notificações (frontend completo) | Web | Minor | **+1** | Sidebar badge, página /notifications, mark as read |
| Busca Avançada no Marketplace | Web | Minor | **+1** | Pesquisa por texto, ordenação por data/recompensa |
| Dashboard com Estatísticas de Tarefas | Web | Minor | **+1** | Stats pessoais, gráficos de progresso, saldo ZION |
| Perfil Público de Usuário | User Management | Minor | **+1** | Página /users/:id com stats, reviews, add friend |
| Exportação de Dados GDPR | Cybersecurity | Minor | **+1** | GET /api/profile/export → download JSON com dados pessoais |

---

### Resumo de Pontos

```
Módulos obrigatórios:   13 pts
Módulos bônus:          +6 pts
  ├── ERC-20 Marketplace (Modules of choice Minor)      +1 pt
  ├── Sistema de Notificações frontend (Web Minor)      +1 pt
  ├── Busca Avançada no Marketplace (Web Minor)         +1 pt
  ├── Dashboard com Estatísticas (Web Minor)            +1 pt
  ├── Perfil Público de Usuário (User Mgmt Minor)       +1 pt
  └── Exportação de Dados GDPR (Cybersecurity Minor)    +1 pt
──────────────────────────────────────────────────────────────
TOTAL:                  19 pts
──────────────────────────────────────────────────────────────
Mínimo para validação:  14 pts  ✅ ATINGIDO
Bônus máximo (+5 pts):  ✅ SUPERADO (+6 pts bônus = 19 total)
```

---

### Justificativa — ERC-20 Marketplace (Modules of choice Minor)

**Por que este módulo merece reconhecimento como Minor customizado:**

O sistema de tokens ZION implementa uma economia blockchain completa integrada ao marketplace:

1. **Smart Contract ERC-20 deployado na Sepolia testnet** — contrato `ZionToken.sol` com funções `mint`, `transfer` e `approve` verificáveis on-chain.
2. **Escrow on-chain para tarefas** — ao criar uma task, os tokens ZION ficam bloqueados em escrow até aprovação/rejeição da submissão, garantindo trustless payment.
3. **Integração MetaMask via wagmi/viem** — o frontend conecta carteira, assina transações e exibe saldo em tempo real.
4. **Backend Web3j** — `BlockchainService.java` interage com o nó Sepolia via RPC para executar transações programaticamente com chave privada gerenciada pelo Vault.
5. **Diferencial técnico** — combina blockchain (Ethereum), DeFi (escrow), Web3 (MetaMask) e segurança (Vault) num sistema coeso e funcional.

Este módulo vai além de um simples tutorial de blockchain: implementa um fluxo econômico completo onde cada etapa do marketplace (criação → aceitação → submissão → aprovação) tem consequências financeiras rastreáveis on-chain.

### Detalhes do WAF/ModSecurity + Vault

**WAF** (`waf/` — container `transcendence-waf`, porta 80):
- Imagem base: `owasp/modsecurity-crs:nginx-alpine`
- ModSecurity v3.0.14 + OWASP CRS 3.3.8 — 928 regras ativas
- Bloqueia: SQL Injection, XSS, RCE, Command Injection, Path Traversal
- Proxy reverso: `/api/**` e `/ws/**` → backend HTTPS 8443 | `/*` → frontend 3000
- Security headers: `X-Frame-Options`, `X-Content-Type-Options`, `X-XSS-Protection`, `Referrer-Policy`, `Permissions-Policy`
- Proteção contra buffer overflow: `client_max_body_size 10m`, limites de timeout

**HashiCorp Vault** (container `transcendence-vault`, porta 8200):
- Segredos gerenciados: `jwt.secret`, `blockchain.private-key`, `spring.datasource.password`
- Spring Cloud Vault carrega os segredos no bootstrap do backend
- Inicializado automaticamente pelo container `vault-init`

**Testes de validacao:**
```bash
# Request normal → 200 OK
curl http://localhost/api/categories

# SQL Injection → 403 Forbidden (bloqueado pelo WAF)
curl -X POST http://localhost/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{"email":"admin'\'' OR 1=1--","password":"x"}'

# XSS → 403 Forbidden (bloqueado pelo WAF)
curl "http://localhost/api/tasks?title=<script>alert(1)</script>"

# Logs do WAF
docker logs transcendence-waf | grep -i "403\|blocked\|modsec"
```
