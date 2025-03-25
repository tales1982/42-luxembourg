FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y mariadb-server && rm -rf /var/lib/apt/lists/*

# Ajusta diretório do socket e permissões
RUN mkdir -p /run/mysqld && chown -R mysql:mysql /run/mysqld

# Copia o arquivo de configuração do MariaDB (para bindar em 0.0.0.0, etc.)
COPY conf/ini.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

# Copia o script de inicialização
COPY tools/init.sh /docker-entrypoint-init.sh
RUN chmod +x /docker-entrypoint-init.sh

EXPOSE 3306
ENTRYPOINT ["/docker-entrypoint-init.sh"]
