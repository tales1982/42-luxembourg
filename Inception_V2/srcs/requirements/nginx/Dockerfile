FROM debian:buster

# Instala o NGINX e openssl
RUN apt-get update -y && apt-get install -y nginx openssl && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Remove a configuração padrão do NGINX
RUN rm -f /etc/nginx/conf.d/default.conf

# Copia a configuração customizada
COPY conf/default.conf /etc/nginx/conf.d/
# Copiar os certificados SSL para o container
COPY tools/ssl/cert.pem /etc/ssl/certs/cert.pem
COPY tools/ssl/key.pem /etc/ssl/private/key.pem


EXPOSE 443

# Inicia o NGINX em modo foreground
CMD ["nginx", "-g", "daemon off;"]
