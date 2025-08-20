# webserv (42) — versão limpa

- C++98, `-Wall -Wextra -Werror`, **sem libs externas**
- **select()** como único loop de I/O (non-blocking)
- Métodos: **GET, HEAD, POST, DELETE**
- Autoindex, Upload simples (corpo raw), CGI por extensão
- Multi-port/virtual host via config (exemplo mostra 1 server)

## Build
```bash
make
```

## Run
```bash
./webserv configs/example.conf
```

## Rotas
- `/` → estático (`index.html`)
- `/files/` → autoindex + GET/POST/DELETE (upload salvo em `www/uploads`)
- `/cgi/echo.py?hello=world` → CGI Python
- `/old` → redireciona para `/new`
