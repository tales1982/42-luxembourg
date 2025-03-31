FROM debian:bullseye 
#Obrigatorio usar debian:bullseye

# Instalação do PHP-FPM, PHP-MySQL e utilitários
RUN apt-get update && apt-get install -y \
    php-fpm \
    php-mysql \
    wget \
    unzip \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Cria os diretórios necessários
RUN mkdir -p /usr/src/wordpress /var/www/html

# Baixa e extrai o WordPress para um diretório temporário e copia para /usr/src/wordpress
RUN wget https://wordpress.org/latest.tar.gz -O /tmp/latest.tar.gz \
    && tar -xzf /tmp/latest.tar.gz -C /tmp \
    && cp -R /tmp/wordpress/* /usr/src/wordpress/ \
    && rm -rf /tmp/latest.tar.gz /tmp/wordpress

# Ajusta as permissões dos arquivos pré-copiados
RUN chown -R www-data:www-data /usr/src/wordpress

# Cria o diretório de destino (que será o volume) e ajusta as permissões
RUN mkdir -p /var/www/html && chown -R www-data:www-data /var/www/html

# Cria o diretório para o socket do PHP-FPM e ajusta as permissões
RUN mkdir -p /run/php && chown -R www-data:www-data /run/php

# Altera a configuração do PHP-FPM para escutar em TCP na porta 9000
RUN sed -i 's/^listen = .*/listen = 9000/' /etc/php/7.4/fpm/pool.d/www.conf

# Copia o script de entrypoint para a imagem e torna-o executável
COPY tools/docker-entrypoint.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/docker-entrypoint.sh

# Expondo a porta que o PHP-FPM usará
EXPOSE 9000

# Define o entrypoint
ENTRYPOINT ["docker-entrypoint.sh"]
