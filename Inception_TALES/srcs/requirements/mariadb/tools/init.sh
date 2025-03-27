#!/bin/bash
set -e

echo "Iniciando mysqld_safe sem rede..."
mysqld_safe --skip-networking &

echo "Aguardando o MariaDB iniciar..."
until mysqladmin ping --silent; do
  sleep 2
done

echo "Criando banco e usuário..."
mysql -u root -p${MYSQL_ROOT_PASSWORD} <<-EOSQL
  CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
  CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
  GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
  FLUSH PRIVILEGES;
EOSQL



# (Opcional) Ajusta a senha de root
mysql -u root -p${MYSQL_ROOT_PASSWORD} <<-EOSQL
  ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
EOSQL


echo "Subindo o servidor em primeiro plano..."
exec mysqld
