FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    php-fpm php-mysql php-curl php-gd php-xml php-mbstring wget unzip iputils-ping net-tools iproute2 curl \
    && rm -rf /var/lib/apt/lists/*

# Altera o 'listen = /run/php/php7.4-fpm.sock' para 'listen = 0.0.0.0:9000'
RUN sed -i 's|^listen = .*|listen = 0.0.0.0:9000|' /etc/php/7.4/fpm/pool.d/www.conf

# Diretório para o socket (ainda pode ser útil)
RUN mkdir -p /run/php

WORKDIR /var/www/html

# Baixa e extrai o WordPress
RUN wget https://wordpress.org/latest.tar.gz && \
    tar -xzf latest.tar.gz --strip-components=1 && \
    rm latest.tar.gz

# Copia o arquivo wp-config.php que você criou para dentro do container
COPY tools/wp-config.php /var/www/html/wp-config.php

EXPOSE 9000

CMD ["php-fpm7.4", "-F"]
