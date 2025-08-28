1) -- Primeiro teste rode em um terminal
   ./webserv ./configs/example.conf
   e em outro terminal rode
   ./webserv/configs/example.conf
   ------------------------------
2) segundo test rode em um terminal
   ./webserv ./configs/ubuntu_tester.conf
   e em outro rode :
   ./ubuntu_tester http://127.0.0.1:8080

   Primeiro teste rode em um terminal
   ./webserv ./configs/example.conf
   e em outro terminal rode
   ./webserv/configs/example.conf

TENHO QUE REPARA AINDA

# Veredito rápido

**Ainda não dá pra entregar.** Há dois pontos que costumam dar **nota 0 imediata** na correção da 42:

1. **Checar `errno` depois de `read`/`write`/`recv`/`send`.**

   No `src/CGIManager.cpp` você trata `EAGAIN/EWOULDBLOCK` após `write()` e `read()` (linhas ~135 e ~170). Na grade está explícito: *“Se `errno` é checado depois de read/recv/write/send, a nota é 0 e a avaliação termina agora.”*
2. **Ler/escrever FDs fora do `select()` (ou equivalente).**

   Seu loop principal usa **um único `select`** correto (lê e escreve no mesmo ciclo — ponto positivo), mas o **manuseio dos pipes do CGI** (`inPipe[1]` e `outPipe[0]`) é feito em laços próprios com `usleep()` e sem `select()` (no `CGIManager.cpp`). A grade diz: *“Escrever ou ler **QUALQUER** file descriptor sem passar pelo `select()` (ou equivalente) é estritamente proibido.”* Avaliadores mais estritos aplicam isso também aos pipes do CGI — e reprovam.

> ✅ No main loop eu confirmei que você usa  **um só `select()`** , monitora **leitura e escrita ao mesmo tempo** (rfds + wfds) e faz **apenas um `recv`/`send` por cliente por iteração** — isso cumpre os itens centrais da grade.

---

# O que está OK (ou muito perto)

* **Build / padrão 42:** `Makefile` com `-Wall -Wextra -Werror -std=c++98`; binário `webserv`; default config quando não passa argumento (`configs/example.conf`). (Subject exige isso. )
* **Multiplexação:** um único `select` no loop, setando `rfds` e `wfds` ao mesmo tempo; **fecha cliente** em `recv` 0/−1 e em `send` < 0. (Itens centrais da grade.)
* **Config features implementadas:**

  `listen`, `server_name`,  **múltiplos servers/portas** , `root`, `index`, `autoindex on/off`, `methods`, `error_page`, `client_max_body_size` (com sufixos K/M), `return` (redirect), `upload on` + `upload_store`, `cgi_ext` + `cgi_executor`. (Tudo presente no parser.)
* **HTTP básico:** `GET`, `HEAD` (remove body e mantém `Content-Length`), `POST` (upload cru e `x-www-form-urlencoded`), `DELETE`, `405` com header `Allow`, `413` quando `Content-Length` excede limite, `404`, `403` (dir sem index e sem autoindex), `301/302` via `return`.
* **Páginas de erro customizadas** e **fallback** para página HTML default quando não houver corpo (já tem gerador).
* **CGI:** mapeamento por extensão, `execve` com env, `chdir` para a pasta do script (ok segundo o subject).
* **Multi-host:** configs de `sitea.local:8081` e `siteb.local:8082` + páginas com os títulos certos (A/B).
* **Valgrind:** no log incluído,  **definitely/indirectly lost = 0** . A aparição de *still reachable* deve vir de libc/tz; costuma ser tolerado, mas depende do avaliador. (A grade pede ausência de leaks; normalmente focam em  *definitely lost* .)

---

# Problemas que vão te custar pontos (além dos “zeradores”)

* **Timeout/502/504 do CGI não consolidados:**

  O `example.conf` declara `cgi_timeout 3;` e você incluiu páginas `502/504`, mas **o parser não reconhece `cgi_timeout`** e **não vi código atribuindo 502/504** no fluxo do CGI. Resultado: script lento/erro tende a virar **500** e não **504/502** como você planejou — e o `httpStatusReason` usado no CGI (o de `Http.cpp`)  **nem tem 502/504** , o que pode gerar *reason* errado se você setar esses códigos. (O subject/grade pedem testar problemas de CGI e exibir erro sem crash.)

  **Ação:** unificar um **único** `httpStatusReason(...)` (o de `DefaultErrorPage.hpp` já cobre 502/504) e implementar a leitura de `cgi_timeout` no parser + mapeamentos:  *timeout → 504* ,  *CGI que falha ao iniciar → 502* ,  *falha interna → 500* .
* **Dois `httpStatusReason(...)` diferentes no projeto.**

  Um em `Http.cpp` (sem 502/504) e outro **inline** em `include/DefaultErrorPage.hpp` (com 502/504). Mantenha **apenas um** para evitar divergências.
* **Keep-Alive desativado na prática.**

  Em `queueResponse()` você força `Connection: close`. Não reprova, mas **piora o siege/throughput** (a grade mede disponibilidade no siege). Se quiser brilhar no “Availability > 99.5%”, considere suportar keep-alive real.
* **Path-join defensivo simples:**

  `safePathJoin` só bloqueia `..` literal; se alguém mandar `%2e%2e/`, pode escapar se não normalizar/decodificar antes. Não é requisito do subject, mas é um endurecimento fácil.

---

# Itens da grade já cobertos x a testar na banca

Checklist essencial que o avaliador costuma disparar (comportamentos que vi no teu código/config):

* **Múltiplos servers/portas** e **server_name** por Host (ok).
* **Default error page** + **error_page por código** (ok).
* **`client_max_body_size`** com 413 (ok).
* **Rotas** com `methods`, `index`, `autoindex`, `upload`, `return`/redirect (ok).
* **GET/POST/DELETE/HEAD** (ok) e **UNKNOWN method** sem crash (405) (ok).
* **CGI GET/POST** e **erros de CGI** sem crash (ok estruturalmente, mas falta timeout/502/504).
* **Compatível com navegador, serve site estático, 404** , listar diretório quando permitido (ok).
* **Stress (siege)** sem leak/hang (arquitetura está boa; keep-alive ajudaria).

---

# O que eu mudaria agora (prioridade)

1. **Remover `errno` do fluxo de I/O**
   * No `CGIManager.cpp`, pare de testar `errno` após `read()/write()`. Se o FD foi sinalizado como pronto pelo `select`, faça **uma** operação curta; em erro (`n < 0`) trate como falha e finalize o CGI. (Isso bate 100% com a grade.)
2. **Trazer os pipes do CGI para o `select()` principal**
   * Modele o CGI como um “sub-estado” do cliente: adicione os FDs do CGI (`inPipe[1]` para `wfds`, `outPipe[0]` para `rfds`) nos mesmos sets do loop principal; escreva/lea  **apenas uma vez por iteração** ; mate por deadline (timeout) sem busy-wait. Assim você cumpre “um único select” + “um read/write por cliente por `select`” e nunca precisa checar `errno` por `EAGAIN`.
3. **Unificar `httpStatusReason(...)`**
   * Elimine o de `Http.cpp` e use o de `DefaultErrorPage.hpp` em todo o projeto (ou mova a versão completa para `Http.cpp` e remova o inline do header). Isso resolve 502/504.
4. **Implementar `cgi_timeout` no parser**
   * Armazene em `ServerConfig` e repasse para o `CGIManager`. Mapeie:  **timeout → 504** ,  **exec falhou → 502** ,  **exit != 0 ou saída inválida → 500** . (O subject pede que o CGI rode “no diretório certo” — você já faz `chdir` — e que o servidor **não trave** e  **mostre erro** .)
5. **(Opcional, mas ajuda no siege)**
   * Suporte **keep-alive** real (não force `Connection: close` sempre).

---

# Observações finais

* Há arquivos fonte no zip com trechos “…” (ex.: `Http.cpp`, `Router.cpp`, `Utils.cpp`, `CGI.cpp`). **Assim não recompila do zero.** Garante que no teu **repositório** (o que será avaliado) esses arquivos estejam completos — a grade exige **compilar sem relink** direto do clone.
* O teu **script de testes** (`test/scripts`) cobre bem o básico e ajuda na defesa.

Se quiser, eu já te entrego os patches para:

* integrar os pipes do CGI ao `select` principal (estado/FDs por conexão),
* remover checks de `errno`,
* unificar `httpStatusReason`,
* e adicionar `cgi_timeout` no parser + mapeamentos 500/502/504.

Diz “manda os patches” e eu te solto a versão refatorada agora.

Fontes

[ ]
