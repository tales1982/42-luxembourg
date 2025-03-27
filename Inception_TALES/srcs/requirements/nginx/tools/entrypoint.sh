#!/bin/bash
# entrypoint.sh - Script de inicialização para o Nginx

# Substitui o placeholder __DOMAIN_NAME__ no template pelo valor da variável de ambiente DOMAIN_NAME
envsubst '${DOMAIN_NAME}' < /etc/nginx/conf.d/default.conf.template > /etc/nginx/conf.d/default.conf


# Inicia o Nginx em primeiro plano
exec nginx -g "daemon off;"
