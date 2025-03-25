
# Makefile                                    

## Como usar:

- make build
Cria as imagens definidas no docker-compose.yml.

- make up
Sobe os containers em segundo plano.

- make down
Para os containers (sem remover volumes).

- make clean
Para e remove os containers e volumes do docker-compose.

- make fclean
Faz uma limpeza completa (containers, imagens, volumes).

- make re
Equivale a fclean + all.

#
# Como configurar o docker-compose.yml

- O docker-compose.yml é onde você orquestra os containers, definindo:

- build (caminho do Dockerfile),

- container_name,

- volumes (para dados do WordPress e base de dados),

- networks (uma rede customizada para conectar tudo),

- environment (variáveis de ambiente para senhas, usuários, etc.),

- depends_on (para garantir ordem de inicialização).

#
# Conclusão 

## Fluxo de trabalho:

- Organize a árvore de diretórios (conforme o enunciado).

- Escreva cada Dockerfile (NGINX, WordPress, MariaDB) na pasta requirements/<servico>.

- Crie o docker-compose.yml em srcs/, especificando as imagens que serão construídas (build), volumes e rede.

- Crie o arquivo .env para armazenar credenciais e outras variáveis.

- Desenvolva o Makefile na raiz para automatizar build, up, down, etc.

- Rode make up (ou docker-compose up --build) e teste.

- Verifique se NGINX está servindo em TLS 1.2/1.3 na porta 443 e se o WordPress se conecta corretamente ao MariaDB.

- Dessa forma, você segue as exigências do enunciado (estrutura de diretórios, cada serviço em seu container, volumes para persistência, TLS no NGINX, etc.) e cumpre o projeto Inception.

# DOCS
## https://hub.docker.com/_/wordpress
## https://github.com/docker-library/wordpress/blob/master/wp-config-docker.php