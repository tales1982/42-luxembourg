#!/bin/bash
set -e

echo "Iniciando o MariaDB..."

# Iniciar o MariaDB em modo safe
mysqld_safe --user=mysql &

# Aguardar o MariaDB iniciar
echo "Aguardando o MariaDB iniciar..."
sleep 5

# Verificar se o MariaDB está rodando
if ! mysqladmin ping -u root --silent; then
    echo "Erro: MariaDB não iniciou corretamente."
    exit 1
fi

# Criar banco de dados e usuário
echo "Criando banco de dados e usuário..."
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" <<EOF
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}' WITH GRANT OPTION;
FLUSH PRIVILEGES;
EOF

# Parar o MariaDB iniciado anteriormente
echo "Parando o MariaDB..."
kill $(cat /run/mysqld/mysqld.pid)

# Iniciar o MariaDB em modo foreground
echo "Iniciando o MariaDB em modo foreground..."
exec mysqld --user=mysql