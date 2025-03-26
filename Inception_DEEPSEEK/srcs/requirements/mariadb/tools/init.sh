#!/bin/bash
set -eo pipefail

# Garante permissões corretas
chown -R mysql:mysql /var/lib/mysql
chmod 755 /var/lib/mysql

# Inicialização do banco
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing database..."
    mysql_install_db --user=mysql --ldata=/var/lib/mysql
    
    # Servidor temporário sem autenticação
    mysqld_safe --skip-grant-tables --socket=/run/mysqld/mysqld.sock &
    
    sleep 5
    
    # Configuração inicial
    mysql -uroot --socket=/run/mysqld/mysqld.sock <<-EOSQL
        FLUSH PRIVILEGES;
        ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
        CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
        CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
        GRANT ALL ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
        FLUSH PRIVILEGES;
EOSQL

    mysqladmin shutdown -p${MYSQL_ROOT_PASSWORD} --socket=/run/mysqld/mysqld.sock
fi

# Ajuste final de permissões
# Adicione no início do script:
chown -R mysql:mysql /var/lib/mysql
chmod 755 /var/lib/mysql

echo "Starting MariaDB..."
exec mysqld