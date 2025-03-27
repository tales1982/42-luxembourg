#!/bin/bash
set -e

# Se o arquivo index.php não existir em /var/www/html, popula o diretório com os arquivos do WordPress
if [ ! -f /var/www/html/index.php ]; then
  echo "Populando /var/www/html com arquivos do WordPress..."
  cp -R /usr/src/wordpress/* /var/www/html/
  chown -R www-data:www-data /var/www/html
fi

exec php-fpm7.3 -F
