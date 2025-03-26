FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    php-fpm php-mysql php-curl php-gd php-xml php-mbstring wget unzip \
    && rm -rf /var/lib/apt/lists/*

RUN sed -i 's|^listen = .*|listen = 0.0.0.0:9000|' /etc/php/7.4/fpm/pool.d/www.conf
RUN mkdir -p /run/php

# Use o caminho absoluto no contexto de build
COPY /home/tlima-de/Documents/Inception_TALES/srcs/requirements/wordpress/tools/wp-config.php /var/www/html/wp-config.php

WORKDIR /var/www/html

RUN wget https://wordpress.org/latest.tar.gz && \
    tar -xzf latest.tar.gz --strip-components=1 && \
    rm latest.tar.gz

RUN chown -R www-data:www-data /var/www/html && \
    chmod 644 /var/www/html/wp-config.php

EXPOSE 9000

CMD ["php-fpm7.4", "-F"]