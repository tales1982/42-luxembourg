MAKEFLAGS += --no-print-directory

# Variables
DOCKER_COMPOSE = docker-compose
SRC_DIR = srcs
COMPOSE_FILE = $(SRC_DIR)/docker-compose.yml
DC = $(DOCKER_COMPOSE) -f $(COMPOSE_FILE)
DATA_DIR = $(HOME)/data

# Cibles
.PHONY: all build up down clean logs ps volumes inspect prune help eval net-ls info mysql


# Par défaut, exécuter les cibles build et up
all: build up

# Construire les images Docker et ajuster les permissions des répertoires
build:
	@ mkdir -p $(DATA_DIR)/mariadb $(DATA_DIR)/wordpress > /dev/null 2>&1
	@$(DC) build

# Démarrer les conteneurs Docker
up:
	@$(DC) up -d

# Arrêter et supprimer les conteneurs Docker et le réseau
down:
	$(DC) down

# Nettoyer les volumes Docker et les données
clean:
	$(DC) down -v --remove-orphans
	rm -rf $(DATA_DIR)/mariadb $(DATA_DIR)/wordpress


# Afficher les journaux des conteneurs Docker
logs:
	$(DC) logs -f

# Afficher l'état des conteneurs Docker du projet
ps:
	$(DC) ps

# Lister les volumes Docker
volumes:
	docker volume ls

# Inspecter un volume Docker spécifique
inspect:
	@if [ -z "$(NAME)" ]; then \
		echo "Veuillez spécifier le nom du volume avec 'make inspect-volume NAME=volume_name'"; \
	else \
		docker volume inspect $(NAME); \
	fi

net-ls:
	docker network ls

# Ouvrir une session MySQL dans le conteneur MariaDB
mysql:
	docker exec -it mariadb mysql -u root -p

info:
	@echo "== Docker Network List =="
	@docker network ls
	@echo "\n== Docker Containers Status =="
	@if $(DC) ps | grep -q .; then \
		$(DC) ps; \
	else \
		echo "Aucun conteneur actif."; \
	fi
	@echo "\n== Docker Volumes List =="
	@if docker volume ls | grep -q .; then \
		docker volume ls; \
	else \
		echo "Aucun volume trouvé."; \
	fi
	@echo "\n== Inspecting Volume: mariadb =="
	@if docker volume inspect mariadb >/dev/null 2>&1; then \
		docker volume inspect mariadb; \
	else \
		echo "Le volume 'mariadb' n'existe pas."; \
	fi
	@echo "\n== Inspecting Volume: wordpress =="
	@if docker volume inspect wordpress >/dev/null 2>&1; then \
		docker volume inspect wordpress; \
	else \
		echo "Le volume 'wordpress' n'existe pas."; \
	fi
	@echo "\n== Docker Compose Logs =="
	@if $(DC) ps | grep -q .; then \
		$(DC) logs --tail=10; \
	else \
		echo "Aucun conteneur actif pour afficher les logs."; \
	fi
	@echo "\n== Docker Images List =="
	@if docker images | grep -q .; then \
		docker images; \
	else \
		echo "Aucune image Docker trouvée."; \
	fi; \

# Nettoyer tous les conteneurs, images, volumes et réseaux Docker (action destructrice)
prune:
	@echo "ATTENTION : Cette action va supprimer TOUS les conteneurs, images, volumes et réseaux Docker sur votre système !"
	@read -p "Êtes-vous sûr de vouloir continuer ? [y/N] " confirm && \
	if [ "$$confirm" = "y" ]; then \
		if [ -n "$$(docker ps -qa)" ]; then docker stop $$(docker ps -qa); fi; \
		if [ -n "$$(docker ps -qa)" ]; then docker rm $$(docker ps -qa); fi; \
		if [ -n "$$(docker images -qa)" ]; then docker rmi -f $$(docker images -qa); fi; \
		if [ -n "$$(docker volume ls -q)" ]; then docker volume rm $$(docker volume ls -q); fi; \
		if [ -n "$$(docker network ls -q)" ]; then docker network rm $$(docker network ls -q) 2>/dev/null || true; fi; \
		if [ -d "$(DATA_DIR)" ]; then sudo rm -rf $(DATA_DIR); fi; \
		docker system prune -a --volumes; \
	else \
		echo "Action annulée."; \
	fi

# Afficher l'aide
help:
	@echo "Utilisation du Makefile :"
	@echo "  make                  : Construire et démarrer les conteneurs Docker"
	@echo "  make build            : Construire les images Docker"
	@echo "  make up               : Démarrer les conteneurs Docker"
	@echo "  make down             : Arrêter et supprimer les conteneurs Docker et le réseau"
	@echo "  make clean            : Nettoyer les volumes Docker et supprimer les données"
	@echo "  make logs             : Afficher les journaux des conteneurs Docker"
	@echo "  make ps               : Afficher l'état des conteneurs Docker du projet"
	@echo "  make volumes          : Lister les volumes Docker"
	@echo "  make inspect          : Inspecter un volume Docker spécifique (ex: make inspect-volume NAME=volume_name)"
	@echo "  make prune            : Nettoyer TOUT Docker (conteneurs, images, volumes, réseaux)"
	@echo "  make help             : Afficher cette aide"
	@echo "  make eval             : Afficher les testes"
	@echo "  make net-ls           : Lister les réseaux Docker"
	@echo "  make info             : Afficher les informations Docker"
	@echo "  make mysql            : Ouvrir une session MySQL dans le conteneur MariaDB"

# Testeur
eval:
	@echo "\033[1;34m/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */"; \
	echo "/*                                PRÉLIMINAIRES                              */"; \
	echo "/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */"; \
	all_tests_passed=true; \
	if [ -f "$(SRC_DIR)/.env" ]; then \
		if grep -Eq '^(DOMAIN_NAME|SQL_DATABASE|SQL_USER|SQL_PASSWORD|SQL_ROOT_PASSWORD|_USER|ADMIN_PASSWORD|ADMIN_EMAIL|SECOND_USER|SECOND_PASSWORD|SECOND_USER_PASSWORD|SECOND_USER_EMAIL)=[^[:space:]]+' $(SRC_DIR)/.env; then \
			echo "\033[31m[Erreur] \033[90m.env contient des informations d'identification critiques.\033[0m"; \
			all_tests_passed=false; \
		else \
			echo "\033[1;34m[OK] \033[90mAucune information d'identification critique n'est présente dans .env.\033[0m"; \
		fi; \
	else \
		echo "\033[1;32m[OK] \033[90mAucun fichier .env trouvé dans srcs.\033[0m"; \
	fi; \
	echo ""; \
	read -p "Nous continuons ? [y/N] " confirm; \
	if [ "$$confirm" = "y" ]; then \
		echo "Continuing with the tests..."; \
	else \
		echo "Action annulée."; \
		exit 1; \
	fi; \
	echo ""; \
	if [ -f "$(SRC_DIR)/.env" ]; then \
		if grep -Eq '^(DOMAIN_NAME|SQL_DATABASE|SQL_USER|SQL_PASSWORD|SQL_ROOT_PASSWORD|_USER|ADMIN_PASSWORD|ADMIN_EMAIL|SECOND_USER|SECOND_PASSWORD|SECOND_USER_PASSWORD|SECOND_USER_EMAIL)=[^[:space:]]+' $(SRC_DIR)/.env; then \
			echo "\033[1;32m[OK] \033[90m.env contient les informations d'identification critiques requises.\033[0m"; \
			all_tests_passed=true; \
		else \
			echo "\033[31m[Erreur] \033[90m.env ne contient pas les informations d'identification critiques requises.\033[0m"; \
			all_tests_passed=false; \
		fi; \
	else \
		echo "\033[31m[Erreur] \033[90m.env est manquant dans srcs.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo "\033[1;34m\n/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */"; \
	echo "/*                           INSTRUCTIONS GÉNÉRALES                          */"; \
	echo "/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */\033[1;32m"; \
	if [ -d "$(SRC_DIR)" ] && [ -n "$$(ls -A $(SRC_DIR))" ]; then \
		if [ -z "$$(find . -maxdepth 1 ! -path . ! -path "./$(SRC_DIR)" ! -path "./.git" ! -name 'Makefile' ! -name '.gitignore' ! -name 'README')" ]; then \
			echo "\033[1;32m[OK] \033[90mTous les fichiers sont dans srcs à la racine.\033[1;32m"; \
		else \
			echo "\033[31m[Erreur] \033[90mDes fichiers sont en dehors de srcs.\033[1;32m"; \
			all_tests_passed=false; \
		fi; \
	else \
		echo "\033[31m[Erreur] \033[90mDossier srcs manquant ou vide.\033[1;32m"; \
		all_tests_passed=false; \
	fi; \
	if [ -f "Makefile" ]; then \
		echo "\033[1;32m[OK] \033[90mMakefile est présent à la racine du référentiel.\033[1;32m"; \
	else \
		echo "\033[31m[Erreur] \033[90mMakefile est manquant à la racine du référentiel.\033[0m"; \
		all_tests_passed=false; \
	echo -e "\033[0m"; \
	fi;\
	# echo "\033[0mdocker stop $(docker ps -qa); docker rm $(docker ps -qa); docker rmi -f $(docker images -qa); docker volume rm $(docker volume ls -q); docker network rm \$(docker network ls -q) 2>/dev/null"; \
	echo -n "\033[1;34m"; \
	# if [ -n "$$(docker ps -qa)" ]; then docker stop $$(docker ps -qa); fi; \
	# if [ -n "$$(docker ps -qa)" ]; then docker rm $$(docker ps -qa); fi; \
	# if [ -n "$$(docker images -qa)" ]; then docker rmi -f $$(docker images -qa); fi; \
	# if [ -n "$$(docker volume ls -q)" ]; then docker volume rm $$(docker volume ls -q); fi; \
	# if [ -n "$$(docker network ls -q)" ]; then docker network rm $$(docker network ls -q) 2>/dev/null; fi; \
	if [ -f "$(SRC_DIR)/docker-compose.yml" ]; then \
		if ! grep -qE "network: host|links:" $(SRC_DIR)/docker-compose.yml; then \
			echo "\033[1;32m[OK] \033[90mdocker-compose.yml ne contient pas 'network: host' ou 'links:'.\033[1;32m"; \
		else \
			echo "\033[31m[Erreur] \033[90mdocker-compose.yml contient 'network: host' ou 'links:'.\033[1;32m"; \
			all_tests_passed=false; \
		fi; \
		if grep -q "network" $(SRC_DIR)/docker-compose.yml; then \
			echo "\033[1;32m[OK] \033[90mdocker-compose.yml contient 'network(s)'.\033[1;32m"; \
		else \
			echo "\033[31m[Erreur] \033[90mdocker-compose.yml ne contient pas 'network(s)'.\033[1;32m"; \
			all_tests_passed=false; \
		fi; \
	else \
		echo "\033[31m[Erreur] \033[90mdocker-compose.yml est manquant.\033[1;32m"; \
		all_tests_passed=false; \
	fi; \
	if ! grep -q -- "\<--link\>" Makefile $(SRC_DIR)/requirements/*/tools/*.sh $(SRC_DIR)/requirements/*/Dockerfile; then \
		echo "\033[1;32m[OK] \033[90mLe Makefile, les Dockerfiles et tous les scripts ne contiennent pas '--link'.\033[1;32m"; \
	else \
		echo "\033[31m[Erreur] \033[90mLe Makefile, les Dockerfiles ou certains scripts contiennent '--link'.\033[1;32m"; \
		all_tests_passed=false; \
	fi; \
	if ! grep -E "sleep infinity|tail -f /dev/null|tail -f /dev/random" $(SRC_DIR)/requirements/*/Dockerfile $(SRC_DIR)/requirements/*/tools/*.sh; then \
		echo "\033[1;32m[OK] \033[90mAucune boucle infinie ou commande interdite trouvée.\033[0m"; \
	else \
		echo "\033[31m[Erreur] \033[90mUne boucle infinie ou une commande interdite a été trouvée dans les Dockerfiles ou scripts.\033[1;32m"; \
		all_tests_passed=false; \
	fi;\
	echo ""; \
	make build; \
	make up; \
	echo "\033[1;34m\n/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */"; \
	echo "/*                             PARTIE OBLIGATOIRE                            */"; \
	echo "/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */\033[1;32m"; \
	echo ""; \
	echo "\033[1;35m                        ----   INSTALLATION SIMPLE   ----                    \033[1;32m"; \
	if [ -f "$(SRC_DIR)/requirements/nginx/conf/nginx.conf" ]; then \
		echo "\033[1;36mss -tuln | grep -E ':(80|443)'\033[0m"; \
		ss_tuln_output=$$(ss -tuln | grep -E ':(80|443)'); \
		echo "$$(echo "$$ss_tuln_output" | sed 's/^/     /')"; \
		if echo "$$ss_tuln_output" | grep -q "443" && ! echo "$$ss_tuln_output" | grep -q "80"; then \
			echo "\033[1;32m[OK] \033[90mNGINX n'est accessible que par le port 443.\033[0m"; \
		else \
			echo "\033[31m[Erreur] \033[90mNGINX est accessible par des ports autres que 443.\033[0m"; \
			all_tests_passed=false; \
		fi; \
		echo ""; \
		echo "\033[1;36mecho | openssl s_client -connect localhost:443 -servername $(USER).42.fr 2>/dev/null | openssl x509 -noout -dates -subject -issuer\033[0m"; \
		ssl_output=$$(echo | openssl s_client -connect localhost:443 -servername $(USER).42.fr 2>/dev/null | openssl x509 -noout -dates -subject -issuer); \
		echo "$$(echo "$$ssl_output" | sed 's/^/     /')"; \
		if echo "$$ssl_output" | grep -q "subject" && echo "$$ssl_output" | grep -q "issuer"; then \
			echo "\033[1;32m[OK] \033[90mUn certificat SSL/TLS est utilisé.\033[0m"; \
		else \
			echo "\033[31m[Erreur] \033[90mAucun certificat SSL/TLS n'est configuré.\033[0m"; \
			all_tests_passed=false; \
		fi; \
	else \
		echo "\033[31m[Erreur] \033[90mLe fichier de configuration NGINX est manquant.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	read -p "Desirez-vous ouvrir la page $(USER).42.fr ? [y/N] " confirm; \
	if [ "$$confirm" = "y" ]; then \
		echo "Continuing with the tests...\n"; \
	else \
		echo "Action annulée."; \
		exit 1; \
	fi; \
	xdg-open "https://$(USER).42.fr/"; \
	curl -s -k https://$(USER).42.fr | grep -q "WordPress Installation"; \
	if [ $$? -eq 0 ]; then \
		echo "\033[31m[Erreur] \033[90mLe site WordPress affiche la page d'installation.\033[1;32m"; \
		all_tests_passed=false; \
	else \
		echo "\033[1;32m[OK] \033[90mLe site WordPress est correctement installé.\033[1;32m"; \
	fi; \
	echo ""; \
	echo "\033[1;36mcurl -I http://$(USER).42.fr\033[0m"; \
	curl_result=$$(curl -s -S -I http://$(USER).42.fr 2>&1); \
	echo "\033[0m     $$curl_result"; \
	if curl -I http://$(USER).42.fr 2>&1 | grep -q "Failed to connect to $(USER).42.fr port 80: Connection refused"; then \
		echo "\033[1;32m[OK] \033[90mLe site n'est pas accessible via HTTP.\033[1;32m"; \
	else \
		echo "\033[31m[Erreur] \033[90mLe site est accessible via HTTP ou ne redirige pas vers HTTPS.\033[1;32m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	echo "\033[1;35m                     ----   NOTIONS DE BASE SUR DOCKER   ----                    \033[1;32m"; \
	all_files_present=true; \
	for service in wordpress mariadb nginx; do \
		if [ ! -f "$(SRC_DIR)/requirements/$$service/Dockerfile" ] || [ ! -s "$(SRC_DIR)/requirements/$$service/Dockerfile" ]; then \
			echo "\033[31m[Erreur] \033[90mLe Dockerfile pour $$service est manquant ou vide.\033[0m"; \
			all_files_present=false; \
		fi; \
	done; \
	if [ "$$all_files_present" = true ]; then \
		echo "\033[1;32m[OK] \033[90mTous les Dockerfiles par service existent et ne sont pas vides.\033[0m"; \
	else \
		all_tests_passed=false; \
	fi; \
	all_custom_images=true; \
	if grep -q "image:" $(SRC_DIR)/docker-compose.yml; then \
		echo "\033[31m[Erreur] \033[90mdocker-compose.yml utilise des images prêtes à l'emploi (image:). Veuillez utiliser 'build:' avec un chemin vers un Dockerfile.\033[0m"; \
		all_custom_images=false; \
	else \
		echo "\033[1;32m[OK] \033[90mdocker-compose.yml utilise 'build:' et non des images prêtes à l'emploi.\033[0m"; \
	fi; \
	if docker images | grep -E '^(nginx|mysql|php|wordpress|mariadb)\s'; then \
		echo "\033[31m[Erreur] \033[90mDes images Docker populaires (nginx, mysql, etc.) existent dans le système. Assurez-vous d'utiliser vos propres Dockerfiles.\033[0m"; \
		all_custom_images=false; \
	else \
		echo "\033[1;32m[OK] \033[90mAucune image Docker non personnalisée utilisée pour la construction.\033[0m"; \
	fi; \
	if [ "$$all_custom_images" = false ]; then \
		all_tests_passed=false; \
	fi; \
	all_images_valid=true; \
	for dockerfile in $(SRC_DIR)/requirements/*/Dockerfile; do \
		if ! grep -q "FROM debian:bullseye" $$dockerfile; then \
			echo "\033[31m[Erreur] \033[90mLe Dockerfile $$dockerfile n'utilise pas debian:bullseye.\033[0m"; \
			all_images_valid=false; \
		fi; \
	done; \
	if [ "$$all_images_valid" = true ]; then \
		echo "\033[1;32m[OK] \033[90mTous les Dockerfiles utilisent debian:bullseye comme base.\033[0m"; \
	else \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	echo "\033[1;35m                           ----   RÉSEAU DOCKER   ----\033[1;32m"; \
	echo "\033[1;36mdocker network ls | grep inception\033[0m"; \
	if docker network ls | grep -q "inception"; then \
		echo "\033[0m     $$(docker network ls | head -n 1)"; \
		echo "\033[0m     $$(docker network ls | grep inception)"; \
		echo "\033[1;32m[OK] \033[90mLe réseau docker-network 'inception' est présent.\033[0m"; \
	else \
		echo "\033[31m[Erreur] \033[90mAucun réseau Docker nommé 'inception' trouvé.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	echo "\033[1;35m                         ----   NGINX avec SSL/TLS   ----\033[1;32m"; \
	if [ -f "$(SRC_DIR)/requirements/nginx/Dockerfile" ] && [ -s "$(SRC_DIR)/requirements/nginx/Dockerfile" ]; then \
		echo "\033[1;32m[OK] \033[90mLe Dockerfile pour nginx existe et n'est pas vide.\033[0m"; \
	else \
		echo "\033[31m[Erreur] \033[90mLe Dockerfile pour nginx est manquant ou vide.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	echo "\033[1;36mdocker-compose -f $(SRC_DIR)/docker-compose.yml ps\033[0m"; \
	if docker-compose -f $(SRC_DIR)/docker-compose.yml ps | grep -q "nginx.*Up"; then \
		echo "     $$(docker-compose -f $(SRC_DIR)/docker-compose.yml ps | head -n 1)"; \
		echo "     $$(docker-compose -f $(SRC_DIR)/docker-compose.yml ps | grep nginx)"; \
		echo "\033[1;32m[OK] \033[90mLe conteneur 'nginx' est créé et en cours d'exécution.\033[0m"; \
	else \
		echo "\033[31m[Erreur] \033[90mLe conteneur 'nginx' n'est pas en cours d'exécution ou n'a pas été créé.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	echo "\033[1;36mcurl -I http://$(USER).42.fr\033[0m"; \
	curl_result=$$(curl -s -S -I http://$(USER).42.fr 2>&1); \
	echo "     $$curl_result"; \
	if echo "$$curl_result" | grep -q "Failed to connect"; then \
		echo "\033[1;32m[OK] \033[90mL'accès via HTTP (port 80) est correctement bloqué.\033[0m"; \
	else \
		echo "\033[31m[Erreur] \033[90mL'accès via HTTP (port 80) est possible, il devrait être bloqué.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	echo "\033[1;36mecho | openssl s_client -connect $(USER).42.fr:443 2>/dev/null | grep -m 1 -oE 'TLSv1\.[0-9]'\033[0m"; \
	tls_output=$$(echo | openssl s_client -connect $(USER).42.fr:443 2>/dev/null | grep -m 1 -oE 'TLSv1\.[0-9]'); \
	echo "$$tls_output"; \
	if [ "$$tls_output" = "TLSv1.2" ]; then \
		echo "\033[1;32m[OK] \033[90mCertificat TLS v1.2 détecté.\033[0m"; \
	elif [ "$$tls_output" = "TLSv1.3" ]; then \
		echo "\033[1;32m[OK] \033[90mCertificat TLS v1.3 détecté.\033[0m"; \
	else \
		echo "\033[31m[Erreur] \033[90mAucun certificat TLS v1.2/v1.3 trouvé.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	echo "\033[1;35m                ----   WORDPRESS AVEC PHP-FPM ET SON VOLUME   ----\033[1;32m"; \
	if [ -f "$(SRC_DIR)/requirements/wordpress/Dockerfile" ] && [ -s "$(SRC_DIR)/requirements/wordpress/Dockerfile" ]; then \
		echo "\033[1;32m[OK] \033[90mLe Dockerfile pour wordpress existe et n'est pas vide.\033[0m"; \
	else \
		echo "\033[31m[Erreur] \033[90mLe Dockerfile pour wordpress est manquant ou vide.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	if ! grep -q "nginx" $(SRC_DIR)/requirements/wordpress/Dockerfile; then \
		echo "\033[1;32m[OK] \033[90mIl n'y a pas de NGINX dans le Dockerfile de WordPress.\033[1;32m"; \
	else \
		echo "\033[31m[Erreur] \033[90mNGINX est présent dans le Dockerfile de WordPress.\033[1;32m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	echo "\033[1;36mdocker-compose -f $(SRC_DIR)/docker-compose.yml ps\033[0m"; \
	if docker-compose -f $(SRC_DIR)/docker-compose.yml ps | grep -q "wordpress.*Up"; then \
		echo "\033[0m     $$(docker-compose -f $(SRC_DIR)/docker-compose.yml ps | head -n 1)"; \
		echo "\033[0m     $$(docker-compose -f $(SRC_DIR)/docker-compose.yml ps | grep wordpress)"; \
		echo "\033[1;32m[OK] \033[90mLe conteneur 'wordpress' est créé et en cours d'exécution.\033[0m"; \
	else \
		echo "\033[31m[Erreur] \033[90mLe conteneur 'wordpress' n'est pas en cours d'exécution ou n'a pas été créé.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	echo "\033[1;36mdocker volume ls && docker volume inspect wordpress\033[0m"; \
	volume_name="srcs_wordpress"; \
	volume_path="/home/$(USER)/data/wordpress"; \
	volume_exists=$$(docker volume ls | grep -w $$volume_name); \
	volume_inspect=$$(docker volume inspect $$volume_name | grep '"device":' | sed 's/^[ \t]*//'); \
	if [ -n "$$volume_exists" ]; then \
		if echo "$$volume_inspect" | grep -q "$$volume_path"; then \
			echo "     $$volume_exists"; \
			echo "     $$volume_inspect"; \
			echo "\033[1;32m[OK] \033[90mLe volume $$volume_name existe et utilise le chemin $$volume_path.\033[0m"; \
		else \
			echo "\033[31m[Erreur] \033[90mLe volume $$volume_name n'utilise pas le chemin $$volume_path.\033[0m"; \
			all_tests_passed=false; \
		fi; \
	else \
		echo "\033[31m[Erreur] Le volume $$volume_name n'existe pas.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	read -p "Desirez-vous ouvrir la page $(USER).42.fr/wp-admin ? [y/N] " confirm; \
	if [ "$$confirm" = "y" ]; then \
		echo "Continuing with the tests..."; \
	else \
		echo "Action annulée."; \
		exit 1; \
	fi; \
	xdg-open "https://$(USER).42.fr/wp-admin"; \
	echo ""; \
	echo "\033[1;35m                      ----   MARIADB ET SON VOLUME   ----\033[1;32m"; \
	if [ -f "$(SRC_DIR)/requirements/mariadb/Dockerfile" ] && [ -s "$(SRC_DIR)/requirements/mariadb/Dockerfile" ]; then \
		echo "\033[1;32m[OK] \033[90mLe Dockerfile pour mariadb existe et n'est pas vide.\033[0m"; \
	else \
		echo "\033[31m[Erreur] \033[90mLe Dockerfile pour mariadb est manquant ou vide.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	if ! grep -q "nginx" $(SRC_DIR)/requirements/mariadb/Dockerfile; then \
		echo "\033[1;32m[OK] \033[90mIl n'y a pas de NGINX dans le Dockerfile de mariadb.\033[1;32m"; \
	else \
		echo "\033[31m[Erreur] \033[90mNGINX est présent dans le Dockerfile de mariadb.\033[1;32m"; \
		all_tests_passed=false; \
	fi; \
	if docker-compose -f $(SRC_DIR)/docker-compose.yml ps | grep -q "mariadb.*Up"; then \
		echo "\033[0m     $$(docker-compose -f $(SRC_DIR)/docker-compose.yml ps | head -n 1)"; \
		echo "\033[0m     $$(docker-compose -f $(SRC_DIR)/docker-compose.yml ps | grep mariadb)"; \
		echo "\033[1;32m[OK] \033[90mLe conteneur 'mariadb' est créé et en cours d'exécution.\033[0m"; \
	else \
		echo "\033[31m[Erreur] \033[90mLe conteneur 'mariadb' n'est pas en cours d'exécution ou n'a pas été créé.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	echo "\033[1;36mdocker volume ls && docker volume inspect mariadb\033[0m"; \
	volume_name="srcs_mariadb"; \
	volume_path="/home/$(USER)/data/mariadb"; \
	volume_exists=$$(docker volume ls | grep -w $$volume_name); \
	volume_inspect=$$(docker volume inspect $$volume_name | grep '"device":' | sed 's/^[ \t]*//'); \
	if [ -n "$$volume_exists" ]; then \
		if echo "$$volume_inspect" | grep -q "$$volume_path"; then \
			echo "     $$volume_exists"; \
			echo "     $$volume_inspect"; \
			echo "\033[1;32m[OK] \033[90mLe volume $$volume_name existe et utilise le chemin $$volume_path.\033[0m"; \
		else \
			echo "\033[31m[Erreur] \033[90mLe volume $$volume_name n'utilise pas le chemin $$volume_path.\033[0m"; \
			all_tests_passed=false; \
		fi; \
	else \
		echo "\033[31m[Erreur] Le volume $$volume_name n'existe pas.\033[0m"; \
		all_tests_passed=false; \
	fi; \
	echo ""; \
	read -p "Desirez-vous vous connecter à la base de données ? [y/N] " confirm; \
	if [ "$$confirm" = "y" ]; then \
		echo "Continuing with the tests...\n"; \
	else \
		echo "Action annulée."; \
		exit 1; \
	fi; \
	echo "\033[1;36mdocker exec -it mariadb mysql -u root -p\033[0m"; \
	docker exec -it mariadb mysql -u root -p;

