# **************************************************************************** #
#                                  Makefile                                    #
# **************************************************************************** #

NAME = inception

# Caminho para o docker-compose
COMPOSE_FILE = srcs/docker-compose.yml
ENV_FILE = srcs/.env

# Alvo principal: constrói e sobe os containers
all: up

# Constrói as imagens Docker (chamando o docker-compose)
build:
	docker-compose --env-file ${ENV_FILE} -f $(COMPOSE_FILE) build

# Sobe (inicia) os containers em segundo plano
up:
	docker-compose ${ENV_FILE} -f $(COMPOSE_FILE) up -d

# Desce (para) os containers
down:
	docker-compose ${ENV_FILE} -f $(COMPOSE_FILE) down

# Limpa containers, redes e volumes
clean:
	docker-compose -f $(COMPOSE_FILE) down --volumes

# Remove imagens e volumes não utilizados
fclean: clean
	docker system prune -af
	docker volume prune -f

# Reconstrói tudo do zero
re: fclean all

.PHONY: all build up down clean fclean re
