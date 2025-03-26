FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    gettext \
    && rm -rf /var/lib/apt/lists/*

# Cria diretório SSL com permissões corretas
RUN mkdir -p /etc/nginx/ssl && \
    chown -R www-data:www-data /etc/nginx && \
    chmod 755 /etc/nginx/ssl

COPY conf/default.conf.template /etc/nginx/conf.d/
COPY tools/entrypoint.sh /docker-entrypoint.sh
RUN chmod +x /docker-entrypoint.sh

EXPOSE 443

ENTRYPOINT ["/docker-entrypoint.sh"]