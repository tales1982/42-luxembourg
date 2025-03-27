FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    gettext \
    && rm -rf /var/lib/apt/lists/*

# Copia a configuração customizada do NGINX
COPY conf/default.conf.templatecd  /etc/nginx/conf.d/default.conf.template

# Copia o script de entrypoint
COPY tools/entrypoint.sh /docker-entrypoint.sh
RUN chmod +x /docker-entrypoint.sh

# Cria o diretório para certificados e gera um certificado autoassinado
RUN mkdir -p /etc/nginx/ssl && \
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/server.key \
    -out /etc/nginx/ssl/server.crt \
    -subj "/C=BR/ST=Estado/L=Cidade/O=Empresa/OU=TI/CN=tlima-de.42.fr"

EXPOSE 443

ENTRYPOINT ["/docker-entrypoint.sh"]