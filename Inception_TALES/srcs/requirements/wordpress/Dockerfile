FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    php-fpm php-mysql php-curl php-gd php-xml php-mbstring wget unzip \
    && rm -rf /var/lib/apt/lists/*

# Altera o 'listen = /run/php/php7.4-fpm.sock' para 'listen = 0.0.0.0:9000'
RUN sed -i 's|^listen = .*|listen = 0.0.0.0:9000|' /etc/php/7.4/fpm/pool.d/www.conf

# Diretório para o socket (ainda pode ser útil)
RUN mkdir -p /run/php

WORKDIR /var/www/html

RUN wget https://wordpress.org/latest.tar.gz && \
    tar -xzf latest.tar.gz --strip-components=1 && \
    rm latest.tar.gz

EXPOSE 9000

CMD ["php-fpm7.4", "-F"]

