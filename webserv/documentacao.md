
## ✔️ O que já está implementado corretamente

1. **Parsing de configuração**
   * Leitura de `server { … }`, diretivas gerais e blocos `location` (path + directives) **fr.subject**
2. **Loop de I/O não-bloqueante**
   * Usa `select()` para multiplexar conexões num único loop de eventos **fr.subject**
3. **Servir arquivos estáticos**
   * Lê e retorna conteúdo de `root + path` com `Content-Type` inferido pelo sufixo **fr.subject**
4. **Directory listing (autoindex)**
   * Gera HTML a partir de um template quando `autoindex on` **fr.subject**
5. **Uploads via POST**
   * Extrai corpo multipart, deduz extensão, grava em subpastas e mostra página de sucesso **fr.subject**
6. **CGI básico**
   * `fork()`, `execve()`, passa `REQUEST_METHOD`, `PATH_INFO`, captura saída em pipe e responde **fr.subject**
7. **Redirecionamentos**
   * Trata diretiva `return 301|302|307|308 URL` e envia status + `Location` **fr.subject**
8. **Config de página de erro**
   * Lê `error_page 404 …` e `500 …` no parser **fr.subject**

---

## ⚠️ Funcionalidades ainda **faltantes** ou incompletas

1. **Método DELETE**
   * Você ainda não trata `DELETE`: deve remover o recurso solicitado (arquivo ou diretório vazio) e responder `200 OK` ou `204 No Content`/`404 Not Found`.
2. **Validação de métodos permitidos**
   * Em cada `location` precisa verificar se `method` está em `methods GET POST DELETE` e, caso contrário, responder `405 Method Not Allowed`.
3. **Tamanho máximo de corpo (client_max_body_size)**
   * A diretiva `client_max_body_size 1M` não está sendo aplicada; hoje o buffer é fixo em 100 MB.
4. **Suporte a múltiplos blocos server / múltiplas portas**
   * O parser só carrega um `ServerConfig` e você abre apenas um socket. Para virtual hosts você deve:
     * Permitir vários blocos `server { … }`
     * Criar um `ServerConfig` por bloco e dar `socket()/bind()` em cada porta distinta (mesma ou diferente)
5. **Respeitar server_name / Host header**
   * No parsing você lê `server_name`, mas no runtime não faz distinção via cabeçalho `Host:` — hoje todo request cai no mesmo virtual host.
6. **Parsing completo de headers HTTP**
   * Você só analisa a primeira linha (`METHOD PATH`), sem armazenar `Content-Length`, `Content-Type`, `Connection`, etc.
   * Para uploads, CGI e keep-alive você precisa extrair esses headers antes de processar o corpo.
7. **Variáveis de ambiente completas para CGI**
   * Falta passar `CONTENT_LENGTH`, `CONTENT_TYPE`, `QUERY_STRING`, `HTTP_HOST`, `SERVER_NAME`, entre outras, conforme a spec CGI/1.1.
8. **Tratamento de escrita não-bloqueante**
   * Em sockets não-bloqueantes, `write()` pode retornar `EAGAIN`; você deve checar e usar loop ou buffer intermediário.
9. **Índices customizados por location**
   * Se um `location` define `index foo.html`, você deve procurar `root/path/foo.html` em vez de sempre `index.html`.
10. **DELETE recursivo e remoção de diretórios**
    * Se `DELETE` apontar para diretório, ou devolver `409 Conflict` ou remover somente se vazio.
11. **Outras páginas de erro**
    * O spec permite `error_page 403`, `400` etc.; hoje você só trata 404 e 500.
12. **Suporte a keep-alive / Connection: close**
    * Detectar `Connection: keep-alive` e manter conexão ou fechar conforme o header.
13. **Makefile completo**
    * Verifique se seu `Makefile` tem alvos mínimos (`all`, `clean`, `fclean`, `re`, e gera `webserv` sem relinkar desnecessariamente).

---

### Próximos passos sugeridos

1. **Parser de HTTP** : crie uma estrutura para headers (`std::map`) e funcione como input para upload, CGI e DELETE.
2. **DELETE + validação de métodos** : implemente antes do `process_client_request()`.
3. **Client_max_body_size** : converta “1M” em bytes, compare com `Content-Length` e limite o buffer.
4. **Virtual hosts** : leia vários blocos `server {}` no parser e em `main()` faça um loop que chama `initialize_server()` para cada um. Depois, no `select()`, faça `FD_ISSET()` em todos os `server_fd`.
5. **Ambiente CGI completo** : adicione variáveis padrão como `CONTENT_LENGTH`, `CONTENT_TYPE`, `QUERY_STRING` e reasigne `envp`.
6. **Tratamento de escrita robusto** : transforme `send_response()` num método que garante envio completo, mesmo se `write()` for parcial ou EAGAIN.
7. **Teste end-to-end** : escreva casos para GET estático, autoindex, POST upload, CGI, DELETE e redirecionamentos; garanta status, headers e corpo.
