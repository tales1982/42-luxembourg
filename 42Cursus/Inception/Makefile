NAME = inception
COMPOSE = docker-compose -f ./srcs/docker-compose.yml
VOLUME_PATH = /home/$(USER)/data

all: up

up:
	@$(COMPOSE) up -d --build

down:
	@$(COMPOSE) down

clean:
	@$(COMPOSE) down -v --remove-orphans
	@docker volume rm -f srcs_wordpress srcs_mariadb 2>/dev/null || true

fclean: clean
	@docker rmi srcs_nginx srcs_wordpress srcs_mariadb 2>/dev/null || true
	@docker system prune -af --volumes

re: fclean all

