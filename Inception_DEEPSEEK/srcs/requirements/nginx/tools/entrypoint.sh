#!/bin/bash

# Gera certificado SSL
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/server.key \
    -out /etc/nginx/ssl/server.crt \
    -subj "/C=BR/ST=SP/L=SaoPaulo/O=42School/OU=Inception/CN=${DOMAIN_NAME}"

# Ajusta permissões
chmod 600 /etc/nginx/ssl/server.key
chmod 644 /etc/nginx/ssl/server.crt
chown www-data:www-data /etc/nginx/ssl/*

# Processa template
envsubst '$DOMAIN_NAME' < /etc/nginx/conf.d/default.conf.template > /etc/nginx/conf.d/default.conf

# Inicia Nginx
exec nginx -g "daemon off;"