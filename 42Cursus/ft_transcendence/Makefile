# ============================================
# Transcendence Makefile
# ============================================

.PHONY: help up down build logs clean rebuild frontend backend postgres vault diagnose

# Default target
help:
	@echo "╔══════════════════════════════════════════════════════════════╗"
	@echo "║           🎮 Transcendence - Comandos Disponíveis            ║"
	@echo "╠══════════════════════════════════════════════════════════════╣"
	@echo "║  make up        → Inicia todos os serviços                   ║"
	@echo "║  make down      → Para todos os serviços                     ║"
	@echo "║  make build     → Build de todas as imagens                  ║"
	@echo "║  make rebuild   → Rebuild forçado (sem cache)                ║"
	@echo "║  make logs      → Mostra logs de todos os serviços           ║"
	@echo "║  make clean     → Remove containers, volumes e imagens       ║"
	@echo "║                                                              ║"
	@echo "║  make frontend  → Logs do frontend                           ║"
	@echo "║  make backend   → Logs do backend                            ║"
	@echo "║  make postgres  → Acessa o PostgreSQL via psql               ║"
	@echo "║  make vault     → Abre o Vault UI                            ║"
	@echo "║  make diagnose  → Executa diagnóstico de problemas           ║"
	@echo "╚══════════════════════════════════════════════════════════════╝"

# Start all services
up:
	@echo "🚀 Starting Transcendence..."
	docker compose --env-file .env up -d
	@echo ""
	@echo "✅ Services started!"
	@echo "   App (via WAF): http://localhost"
	@echo "   Frontend Dev:  http://localhost:3000"
	@echo "   Backend HTTPS: https://localhost:8443"
	@echo "   pgAdmin:       http://localhost:5050"
	@echo "   Vault UI:      http://localhost:8200"
	@echo "   PostgreSQL:    localhost:5433"
	@echo ""
	@echo "⚠️  First time? Accept the self-signed backend cert:"
	@echo "   → Visit https://localhost:8443/actuator/health and click 'Advanced > Proceed'"

# Stop all services
down:
	@echo "🛑 Stopping Transcendence..."
	docker compose down

# Build images
build:
	@echo "🔨 Building images..."
	docker compose build

# Rebuild without cache
rebuild:
	@echo "🔨 Rebuilding images (no cache)..."
	docker compose build --no-cache

# Show logs
logs:
	docker compose logs -f

# Clean everything
clean:
	@echo "🧹 Cleaning up..."
	docker compose down -v --rmi local
	@echo "✅ Cleanup complete!"

# Individual service logs
frontend:
	docker compose logs -f frontend

backend:
	docker compose logs -f backend

# Access PostgreSQL
postgres:
	@echo "🐘 Connecting to PostgreSQL..."
	docker compose exec postgres psql -U transcendence -d transcendence

# Open Vault UI
vault:
	@echo "🔐 Opening Vault UI..."
	@echo "   URL: http://localhost:8200"
	@echo "   Token: transcendence-root-token"
	xdg-open http://localhost:8200 2>/dev/null || open http://localhost:8200 2>/dev/null || echo "Open http://localhost:8200 in your browser"

# Run diagnostics
diagnose:
	@./scripts/diagnose.sh
