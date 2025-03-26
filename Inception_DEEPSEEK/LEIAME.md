# Inception - Visão Geral do Projeto

Você precisa configurar uma pequena infraestrutura de serviços em contêineres Docker, composta por:

- **NGINX** (com TLSv1.2 ou TLSv1.3)
- **WordPress + PHP-FPM** (sem NGINX embutido)
- **MariaDB** (sem NGINX embutido)

Esses serviços devem se comunicar entre si usando rede Docker e volumes para persistência de dados. Você vai orquestrar tudo isso com **docker-compose** e **Dockerfiles** escritos por você mesmo (sem usar imagens prontas para os serviços, exceto Alpine ou Debian como base).

---

# Restrições Importantes

- **Porta de Entrada:**  
  Você só pode expor a porta **443 (HTTPS)** para o NGINX. Ou seja, o NGINX será o único ponto de entrada para toda a sua infraestrutura.

- **TLS:**  
  Deve-se usar **TLSv1.2** ou **TLSv1.3 (HTTPS)**.

- **Base de Imagens:**  
  Os containers devem ser baseados na **penúltima versão estável** do Alpine ou Debian.

- **Tag da Imagem:**  
  Nenhum container deve usar o tag `latest`.

- **Senhas:**  
  Nenhum password deve estar “hard-coded” no Dockerfile. Você deve usar **variáveis de ambiente** (e, preferencialmente, **Docker secrets**).

- **Dockerfile por Serviço:**  
  Cada serviço deve ter seu próprio Dockerfile e se chamar exatamente como o serviço (ex.: `nginx`, `wordpress`, `mariadb`).

- **Volumes:**  
  Você deve criar dois volumes:
  - Um para a base de dados do WordPress (MariaDB).
  - Outro para os arquivos do seu site WordPress (wp-content, uploads, etc.).

- **Rede Docker:**  
  Você deve criar uma **rede Docker (docker-network)** que conecte todos os containers.

- **Reinício Automático:**  
  Cada container deve **reiniciar em caso de crash**.

- **Execução dos Serviços:**  
  Você não pode usar soluções “hacky” (como `tail -f`, `sleep infinity`, `while true`, etc.) para manter o container rodando. Os serviços devem rodar em “modo daemon” corretamente (por exemplo, `nginx -g "daemon off;"`, `php-fpm`, `mysqld`, etc.).

- **Usuários no WordPress:**  
  Você deve criar **dois usuários** no WordPress:
  - **Conta Admin:** a única exigência é que o username não contenha a palavra “admin” (por exemplo, `rootUser`, `superUser`, `boss`, etc.).
  - **Conta Normal:** um usuário comum.

- **Local dos Volumes:**  
  Você deve guardar seus volumes em `/home/<login>/data` (por exemplo, `/home/tales/data`).

- **Domínio Local:**  
  Você deve configurar um domínio `login.42.fr` apontando para o IP local (por exemplo, `tales.42.fr` → `127.0.0.1`).

- **Variáveis de Ambiente:**  
  Use variáveis de ambiente, preferencialmente em um arquivo `.env`.

- **Docker Secrets (Recomendado):**  
  Use Docker secrets para armazenar senhas de forma mais segura.

---

# Estrutura Geral: Onde Entram Logins e Senhas?

Dentro desse projeto, há três lugares principais em que você terá **logins e senhas**:

## 1. Banco de Dados (MariaDB)

- Você terá pelo menos um usuário **root** (com senha de root).
- Você criará um banco para o WordPress, com um usuário e senha específicos.

## 2. WordPress

- No arquivo `wp-config.php`, você precisará configurar as credenciais do banco de dados:
  - Nome do DB
  - Usuário
  - Senha
  - Host

- Você criará 2 contas no WordPress:
  - **Conta Admin:**  
    A exigência é que o username não contenha a palavra “admin”.  
    _Exemplo:_ `rootUser`, `superUser`, `boss`, etc.
  - **Conta Normal:**  
    Um usuário comum.

## 3. Domínio e Certificados SSL (TLS)

- Embora não seja exatamente “login e senha”, você pode ter que gerar certificados com OpenSSL.
- Normalmente, não há senha associada a estes certificados; porém, se você criar certificados com chave protegida por senha, essa senha também deverá ser armazenada de forma segura (por exemplo, via Docker secrets ou variáveis de ambiente).

---

# Onde Armazenar Senhas?

O enunciado diz que nenhum password deve estar no Dockerfile e que você deve usar variáveis de ambiente (e, preferencialmente, Docker secrets). Veja algumas abordagens:

## Variáveis de Ambiente no `docker-compose.yml`

```yaml
version: '3.8'
services:
  mariadb:
    build: ./requirements/mariadb
    environment:
      - MYSQL_ROOT_PASSWORD=${MYSQL_ROOT_PASSWORD}
      - MYSQL_DATABASE=${MYSQL_DATABASE}
      - MYSQL_USER=${MYSQL_USER}
      - MYSQL_PASSWORD=${MYSQL_PASSWORD}
    # ...


```
E, então, no arquivo .env (que não deve ir para o repositório público), você define:

```bash
Copy
MYSQL_ROOT_PASSWORD=some_secure_root_pass
MYSQL_DATABASE=wordpress_db
MYSQL_USER=wp_user
MYSQL_PASSWORD=some_secure_pass
```

# Docker Secrets (Forma Mais Segura)

- **Criação de Arquivos com Senhas:**  
  Crie arquivos de texto com as senhas, por exemplo:  
  - `db_password.txt`
  - `db_root_password.txt`

- **Montagem dos Secrets no docker-compose:**  
  Monte esses arquivos como secrets no arquivo `docker-compose.yml`.  
  Dessa forma, as senhas não ficam visíveis no próprio arquivo de configuração nem em variáveis de ambiente.

- **Leitura dos Valores no Container:**  
  No entrypoint ou script de inicialização do container, leia esses valores para usá-los na configuração dos serviços.

Essa abordagem impede que as senhas fiquem expostas diretamente no `docker-compose.yml` ou em variáveis de ambiente.

---

# WordPress Users

Existem duas abordagens para criar as contas do WordPress (admin e usuário comum):

## 1. Instalação Manual via Navegador

- Ao acessar o site pela primeira vez, o WordPress pedirá para criar um usuário admin.
- Você pode definir o username e a senha manualmente.
- **Atenção:** O username escolhido para o admin **não deve** conter “admin” (por exemplo, use `superuser` ao invés de `admin`).

## 2. Criação via Script (WP-CLI ou wp-config.php Customizado)

- Utilize o **WP-CLI** para criar usuários automaticamente dentro do container, utilizando variáveis de ambiente para definir os usernames e senhas.
- Ou execute um script PHP que insira os usuários diretamente no banco de dados.

O enunciado exige que existam **2 usuários**:
- Um admin (cujo username não contém “admin”)
- Um usuário comum

A forma de automação é de sua escolha.

---

# Explicando Passo a Passo (Focado em Senhas e Logins)

## MariaDB

### Instalação
- No seu Dockerfile do MariaDB (baseado em Alpine ou Debian), instale o MariaDB.

### Variáveis de Ambiente
- Ao iniciar o container, utilize variáveis de ambiente (ou secrets) para definir:
  - `MYSQL_ROOT_PASSWORD`
  - `MYSQL_DATABASE`
  - `MYSQL_USER`
  - `MYSQL_PASSWORD`

### Script de Inicialização
- Você pode ter um script (por exemplo, `init.sql`) que cria o banco de dados e o usuário do WordPress utilizando essas variáveis:

```sql
  CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
  CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
  GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
  FLUSH PRIVILEGES;

```

## Execução do Script de Inicialização no MariaDB

Assim, quando o container MariaDB iniciar pela primeira vez, ele executa o script de inicialização (por exemplo, `init.sql`) e cria o banco de dados (DB) e o usuário utilizando as variáveis de ambiente definidas. Isso garante que o WordPress tenha acesso ao DB com as credenciais corretas.

---

## WordPress

### Configuração do `wp-config.php`

No arquivo `wp-config.php`, configure as credenciais do banco de dados lendo as variáveis de ambiente:

```php
define( 'DB_NAME', getenv('MYSQL_DATABASE') );
define( 'DB_USER', getenv('MYSQL_USER') );
define( 'DB_PASSWORD', getenv('MYSQL_PASSWORD') );
define( 'DB_HOST', 'mariadb:3306' );
```
# Criação do Usuário Admin
## Instalação Manual
- Acesse https://seu-dominio.42.fr no navegador.

- Siga o assistente de instalação do WordPress e crie um usuário admin.

- Atenção: O username para o admin não deve conter a palavra “admin” (por exemplo, use superuser).

## Criação Automática
- Utilize um script com WP-CLI (por exemplo, utilizando comandos como wp core install e wp user create) para criar os usuários automaticamente.

- Utilize variáveis de ambiente para definir os usernames e senhas.

## NGINX
- Certificados TLS
- Gere ou copie os certificados TLS necessários para o NGINX.

- A única exigência é expor a porta 443 e habilitar TLSv1.2 ou TLSv1.3.

## Exemplo de Configuração (nginx.conf)
```shell
server {
  listen 443 ssl;
  ssl_certificate /etc/nginx/ssl/server.crt;
  ssl_certificate_key /etc/nginx/ssl/server.key;
  ssl_protocols TLSv1.2 TLSv1.3;
  # Outras configurações necessárias...
}
```
- Se o certificado tiver uma chave protegida por senha, essa senha também deverá ser armazenada de 
forma segura (por exemplo, via variável de ambiente ou Docker secret).
#

## Volumes
- Volume para o Banco de Dados:   
Monte um volume para o banco de dados no container MariaDB (geralmente em /var/lib/mysql).

- Volume para o WordPress:   
Monte um volume para os arquivos do WordPress (por exemplo, em /var/www/html ou no diretório onde o WordPress está instalado).

- Localização na Máquina Host:   
Os volumes devem estar em /home/<login>/data (por exemplo, /home/tales/data).

#
## Rede Docker
Definição da Rede
No docker-compose.yml, defina uma rede para conectar os containers:
```shell
networks:
  inception_network:
    driver: bridge
```
##  Associação dos Serviços à Rede
Em cada serviço, adicione:
```shell
services:
  mariadb:
    networks:
      - inception_network
  wordpress:
    networks:
      - inception_network
  nginx:
    networks:
      - inception_network
```
Assim, os containers se comunicam utilizando os nomes dos serviços (por exemplo, mariadb como hostname para o banco de dados).

#
## Reiniciar em Caso de Crash
No docker-compose.yml, utilize a diretiva:

```yaml
restart: always
```
Isso garante que os containers reiniciem automaticamente em caso de falha.
#
## Domínio Local
- Configuração no Host
Configure o arquivo /etc/hosts da máquina virtual ou host local para associar o IP local ao domínio   
login.42.fr.

Exemplo:
```shell
127.0.0.1 tales.42.fr
```
Assim, ao digitar https://tales.42.fr no navegador, a requisição será direcionada ao container NGINX na porta 443.
#
## Sem "Hacky Patches"
- Não utilize:
Comandos como CMD ["tail", "-f", "/dev/null"] ou estruturas de loop infinito para manter o container ativo.

- Utilize o processo real do serviço como PID 1:

- Exemplo para o NGINX:
```bash
CMD ["nginx", "-g", "daemon off;"]
```
- Exemplo para o MariaDB:   
Utilize o script de entrada adequado ou
```bash
CMD ["mysqld"]
```
#
## Em Resumo
O que o Projeto Pede:   
- Criação de Contêineres:
Criar contêineres para NGINX, WordPress e MariaDB utilizando Dockerfiles baseados em Alpine/Debian.

- Orquestração:
Utilizar docker-compose para orquestrar os serviços.

- Rede e Volumes:
Utilizar rede Docker e volumes para persistência dos dados.

- Porta Única:
Expor somente a porta 443 para o NGINX com TLS.

- Usuários do WordPress:
Criar 2 usuários:   

    - Um admin (cujo username não contém “admin”).

    - Um usuário comum.

- Domínio Local:
Configurar um domínio local (login.42.fr) apontando para sua VM/localhost.

- Segurança das Senhas:
Armazenar senhas em variáveis de ambiente ou Docker secrets (nunca hard-coded nos Dockerfiles).

## Como Lidar com Logins/Senhas:
- No MariaDB:
Defina MYSQL_ROOT_PASSWORD, MYSQL_USER, MYSQL_PASSWORD e MYSQL_DATABASE no docker-compose.yml (ou via .env/Docker secrets).

- No WordPress:
Configure o wp-config.php para ler essas variáveis de ambiente.
Para a criação do usuário admin, garanta que o username não contenha “admin”.

## Como Executar:
- Makefile:
Crie um Makefile para facilitar os comandos:

    - docker-compose build

    - docker-compose up -d

- Acesso:
Após subir os containers, acesse o domínio configurado (por exemplo, https://tales.42.fr)   
no navegador e conclua a instalação/configuração do WordPress.

Seguindo esses passos e atenções, você cumprirá todos os requisitos do projeto Inception,   
implementando boas práticas de segurança, persistência de dados e comunicação entre os serviços.
#

# Próximos Passos
Rebuild das imagens:

```bash
make build
```
### Subir os containers:
Em seguida:

```bash
make up
Verificar logs:
```
### Confira os logs para confirmar que os erros foram resolvidos:

```bash
docker logs wordpress
```
```basch
docker logs mariadb
```
