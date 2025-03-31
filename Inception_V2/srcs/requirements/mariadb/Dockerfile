FROM debian:bullseye 
#Obrigatorio usar debian:bullseye

# Instalação do MariaDB
RUN apt-get update -y && apt-get install -y mariadb-server
RUN mkdir -p /run/mysqld /var/log/mysql && \
    chown -R mysql:mysql /run/mysqld /var/log/mysql
RUN apt-get clean && rm -rf /var/lib/apt/lists/*


# Cópia da configuração personalizada do MariaDB
COPY tools/custom.cnf /etc/mysql/mariadb.conf.d/

# Cópia do script de inicialização do banco de dados
COPY tools/init-db.sh /

# Definição de permissões para o script
RUN chmod +x /init-db.sh

# Comando padrão para iniciar o container
CMD ["/init-db.sh"]