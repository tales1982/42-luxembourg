# Projeto Docker - Exercício

Este documento descreve os passos e a estrutura para realizar o exercício utilizando Docker, conforme as especificações.

---

## 1. Estrutura de Diretórios e Arquivos

- **Diretório Raiz:**  
  Crie um diretório principal onde ficará o seu projeto. Nele, coloque o seu `Makefile`.

- **Pasta `srcs`:**  
  Dentro deste diretório, crie uma pasta chamada `srcs` que conterá:
  - O arquivo `docker-compose.yml`
  - Um arquivo `.env` com suas variáveis de ambiente (como `DOMAIN_NAME`, configurações MySQL, etc.)
  - Uma pasta (por exemplo, `requirements`) que contenha os subdiretórios para cada serviço: `nginx`, `wordpress` e `mariadb`.  
    Em cada um desses, coloque o `Dockerfile` e os arquivos de configuração específicos (como os arquivos de configuração do Nginx, PHP ou MariaDB).

- **Pasta `secrets`:**  
  Crie também uma pasta `secrets` na raiz para armazenar os arquivos com informações sensíveis (como senhas, chaves, etc.).  
  Esses arquivos deverão ser referenciados via Docker secrets e adicionados ao `.gitignore` para não serem enviados para repositórios públicos.

## Estrutura de Diretórios

```bash
├── Makefile
├── secrets
│   ├── credentials.txt
│   ├── db_password.txt
│   └── db_root_password.txt
└── srcs
    ├── docker-compose.yml
    ├── .env
    └── requirements
        ├── nginx
        │   ├── Dockerfile
        │   └── default.conf
        ├── wordpress
        │   ├── Dockerfile
        │   └── configurações adicionais (ex: php.ini)
        └── mariadb
            ├── Dockerfile
            └── my.cnf
```

---

## 2. Dockerfiles para Cada Serviço

Cada serviço deve ter seu próprio `Dockerfile`, construído a partir da penúltima versão estável do Alpine ou Debian (conforme sua escolha):

- **Nginx:**
  - **Base:** Penúltima versão estável de Alpine ou Debian.
  - **Instalação:** Instale o Nginx e configure-o para aceitar **apenas** TLSv1.2 ou TLSv1.3.
  - **Configuração:** Crie um arquivo de configuração (por exemplo, `default.conf`) que direcione as requisições na porta 443 e redirecione para o container do WordPress.

- **WordPress + php-fpm:**
  - **Base:** Penúltima versão estável de Alpine ou Debian.
  - **Instalação:** Instale o PHP-FPM e o WordPress.
  - **Configuração:** Configure o PHP para se comunicar com o container do banco de dados (MariaDB) e não utilize o Nginx neste container.

- **MariaDB:**
  - **Base:** Penúltima versão estável de Alpine ou Debian.
  - **Instalação:** Instale e configure o MariaDB.
  - **Configuração:** Utilize variáveis de ambiente (via `.env` e, possivelmente, Docker secrets) para configurar senhas e o usuário do banco.
  - **Volumes:** Monte um volume para armazenar os dados do banco.

> **Observação:**  
> Evite "hacky patches" como `tail -f`, `sleep infinity` ou loops infinitos nos comandos de inicialização. Procure iniciar os serviços como daemons (usando os comandos nativos dos serviços).

---

## 3. Arquivo `docker-compose.yml`

No arquivo `docker-compose.yml` você deverá:

- **Definir três serviços:** `nginx`, `wordpress` e `mariadb`.
- **Configurar cada serviço para:**
  - Usar a imagem que você criou (build local com seu Dockerfile).
  - Reiniciar automaticamente (`restart: always`).
  - Definir o mapeamento de volumes:
    - Um volume para os arquivos do WordPress.
    - Um volume para o banco de dados (armazenado, por exemplo, em `/home/seu_login/data` no host).
  - Criar uma rede customizada para que os containers se comuniquem entre si (sem usar `--link` ou `network: host`).

### Exemplo Simplificado

```yaml
version: '3.8'

services:
  nginx:
    build: ./requirements/nginx
    container_name: nginx
    ports:
      - "443:443"
    volumes:
      - ./requirements/nginx/default.conf:/etc/nginx/conf.d/default.conf:ro
    networks:
      - my_network
    restart: always

  wordpress:
    build: ./requirements/wordpress
    container_name: wordpress
    volumes:
      - wordpress_data:/var/www/html
    environment:
      - WORDPRESS_DB_HOST=mariadb
      - WORDPRESS_DB_USER=${MYSQL_USER}
      - WORDPRESS_DB_PASSWORD=${MYSQL_PASSWORD}
      - WORDPRESS_DB_NAME=${MYSQL_DATABASE}
    networks:
      - my_network
    restart: always

  mariadb:
    build: ./requirements/mariadb
    container_name: mariadb
    volumes:
      - db_data:/var/lib/mysql
    environment:
      - MYSQL_ROOT_PASSWORD=${MYSQL_ROOT_PASSWORD}
      - MYSQL_DATABASE=${MYSQL_DATABASE}
      - MYSQL_USER=${MYSQL_USER}
      - MYSQL_PASSWORD=${MYSQL_PASSWORD}
    networks:
      - my_network
    restart: always

volumes:
  wordpress_data:
  db_data:

networks:
  my_network:

```

*** Observação: Adapte os caminhos e variáveis conforme o seu projeto e a estrutura do seu diretório. ***

## 4. Variáveis de Ambiente e Docker Secrets

### Arquivo `.env`:
Crie um arquivo `.env` dentro da pasta `srcs` para definir variáveis como `DOMAIN_NAME`, `MYSQL_USER`, `MYSQL_PASSWORD`, `MYSQL_ROOT_PASSWORD`, etc.

### Docker Secrets:
Para maior segurança, configure Docker secrets para armazenar informações sensíveis (por exemplo, senhas) e referenciá-las no `docker-compose.yml`.  
Essa abordagem evita que informações confidenciais sejam “hardcoded” nos Dockerfiles.

---

## 5. Makefile

No `Makefile` (na raiz do seu projeto) você deverá criar comandos para facilitar o build e a subida dos containers.

### Exemplo Básico

```makefile
all: build up

build:
	docker-compose -f srcs/docker-compose.yml build

up:
	docker-compose -f srcs/docker-compose.yml up -d

down:
	docker-compose -f srcs/docker-compose.yml down

clean: down
	docker volume rm $(shell docker volume ls -q)
```
*** Esse Makefile permite que você construa as imagens e inicie os containers com um único comando (make all). ***

## 6. Configuração do NGINX e TLS

### TLS:
No container do NGINX, configure o servidor para utilizar apenas TLSv1.2 ou TLSv1.3.  
Isso pode ser feito editando o arquivo de configuração (por exemplo, `default.conf`) para incluir as seguintes diretivas:

```nginx
ssl_protocols TLSv1.2 TLSv1.3;
ssl_prefer_server_ciphers on;
```
### Certificados
Você pode usar certificados autoassinados para testes ou configurar certificados reais, dependendo do ambiente de desenvolvimento.

### Ponto de Entrada
Lembre-se que o NGINX deverá ser o único ponto de entrada para a infraestrutura, ou seja, ele receberá as conexões na porta 443 e, através de proxy reverso, repassará as requisições para o container do WordPress.

---

## 7. Boas Práticas

### Dockerfiles
- Evite comandos que mantenham o container ativo com loops ou "hacky patches".
- Use o comando adequado para iniciar o daemon do serviço (por exemplo, `nginx -g "daemon off;"` para o NGINX).

### Build Local
- Construa todas as imagens localmente utilizando seus próprios Dockerfiles, sem recorrer a imagens pré-prontas (exceto pela base, que pode ser Alpine ou Debian).

### Usernames
- Certifique-se de que o nome do usuário Admin do WordPress não contenha “admin” ou variações, conforme especificado.

### Volumes e Persistência
- Configure os volumes corretamente para que os dados (banco e arquivos do WordPress) sejam persistentes e estejam localizados no diretório `/home/seu_login/data` na máquina host.

### Documentação
- Caso alguma configuração ou comando não esteja claro, consulte a documentação oficial do Docker, docker-compose e dos serviços utilizados (NGINX, PHP, MariaDB).

---

## Conclusão

Resumindo, para fazer este exercício você deverá:

- Criar a estrutura de diretórios conforme o exemplo e incluir todos os arquivos necessários.
- Escrever os Dockerfiles individualmente para cada serviço (NGINX, WordPress + php-fpm, MariaDB) com base em uma imagem base adequada.
- Configurar o `docker-compose.yml` para definir os serviços, volumes, rede e variáveis de ambiente.
- Utilizar um arquivo `.env` (e, se possível, Docker secrets) para gerenciar variáveis e credenciais.
- Criar um Makefile que automatize o build e o deploy dos containers.
- Garantir que o NGINX seja configurado para aceitar apenas conexões TLSv1.2/TLSv1.3 na porta 443 e que ele seja o único ponto de entrada da infraestrutura.

Com esses passos e consultando a documentação sempre que necessário, você conseguirá realizar o exercício com sucesso.  
Se tiver dúvidas em alguma parte específica, sinta-se à vontade para perguntar!
