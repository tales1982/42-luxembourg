FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    php-fpm php-mysql curl tar \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/www/html
WORKDIR /var/www/html

# Baixa o WordPress
RUN curl -O https://wordpress.org/latest.tar.gz \
  && tar -xvf latest.tar.gz --strip-components=1 \
  && rm latest.tar.gz

EXPOSE 9000

CMD ["php-fpm7.4", "-F"]
