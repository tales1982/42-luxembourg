FROM debian:bullseye 

# Instala o NGINX e openssl
RUN apt-get update -y && apt-get install -y nginx openssl && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Remove a configuração padrão do NGINX
RUN rm -f /etc/nginx/conf.d/default.conf

# Cria as pastas para SSL caso não existam
RUN mkdir -p /etc/ssl/private /etc/ssl/certs

# Copia a configuração personalizada (ATENÇÃO AO NOME nginx.conf)
COPY conf/nginx.conf /etc/nginx/conf.d/nginx.conf

# Copia os certificados SSL para o container
COPY tools/ssl/cert.pem /etc/ssl/certs/cert.pem
COPY tools/ssl/key.pem /etc/ssl/private/key.pem

EXPOSE 80 443

# Inicia o NGINX em modo foreground
CMD ["nginx", "-g", "daemon off;"]
