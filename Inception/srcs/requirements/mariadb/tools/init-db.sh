#!/bin/bash
set -e

# Leia os secrets
if [ -f /run/secrets/db_root_password ]; then
    export MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
fi

if [ -f /run/secrets/db_password ]; then
    export MYSQL_PASSWORD=$(cat /run/secrets/db_password)
fi

echo "Starting MariaDB..."

# Iniciar o MariaDB em modo safe
mysqld_safe --user=mysql &

# Aguardar o MariaDB iniciar
echo "Waiting for MariaDB to start..."
sleep 5

# Verificar se o MariaDB está rodando
if ! mysqladmin ping -u root --silent; then
    echo "Error: MariaDB did not start correctly."
    exit 1
fi

# Criar banco de dados e usuário
echo "Creating database and user..."
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" <<EOF
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}' WITH GRANT OPTION;
FLUSH PRIVILEGES;
EOF

# Parar o MariaDB iniciado anteriormente
echo "Stopping MariaDB..."
kill $(cat /run/mysqld/mysqld.pid)

# Iniciar o MariaDB em modo foreground
echo "Starting MariaDB in foreground mode..."
exec mysqld --user=mysql
