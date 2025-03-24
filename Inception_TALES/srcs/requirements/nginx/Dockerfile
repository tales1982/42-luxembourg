FROM debian:bullseye

RUN apt-get update && apt-get install -y nginx openssl \
  && rm -rf /var/lib/apt/lists/*

# Cria diretório de certificados
RUN mkdir /etc/nginx/ssl

# Gera um certificado autoassinado (exemplo; use TLSv1.2/1.3)
# (ou você pode copiar um certificado real via COPY)
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
  -keyout /etc/nginx/ssl/server.key \
  -out /etc/nginx/ssl/server.crt \
  -subj "/C=BR/ST=Estado/L=Cidade/O=Empresa/OU=TI/CN=dominio"

# Copia config customizada
COPY conf/default.conf /etc/nginx/conf.d/default.conf

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]