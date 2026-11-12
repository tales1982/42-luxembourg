NAME = red-tetris

all: up

up:
	docker compose up --build -d app
	@echo "Red Tetris: http://localhost:3000/sala1/seu_nome"

down:
	docker compose --profile dev --profile test down

logs:
	docker compose logs -f app

dev:
	docker compose --profile dev up --build dev

test:
	docker compose --profile test run --rm --build test

clean: down
	docker compose --profile dev --profile test down --rmi local -v

re: clean all

.PHONY: all up down logs dev test clean re
