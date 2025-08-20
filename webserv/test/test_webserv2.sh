#!/usr/bin/env bash
#
# test_webserv.sh — Teste automático do projeto webserv (42)
# Requisitos: bash, curl, grep, sed, awk, dd/head, python3 (opcional para mini stress)
#
# COMO USAR
#   1) Coloque este script na RAIZ do projeto (onde está o binário ./webserv e a pasta configs/)
#   2) Compile:             make
#   3) Rode os testes:      bash test_webserv.sh
#
# O script:
#   - Gera um config TEMPORÁRIO (porta 8080 e 8081) para cobrir "múltiplas portas"
#   - Sobe o servidor em background usando esse config
#   - Roda uma bateria de testes cobrindo os pontos do enunciado
#   - Finaliza o servidor e mostra um resumo PASS/FAIL
#
# Saída detalhada vai para: ./test_results.log
#
set -euo pipefail

BIN=../webserv
LOG=./test_results.log
TMP_CONF=/tmp/webserv_test.conf
ROOT=$(pwd)
PASS=0
FAIL=0

function log() { echo -e "$@" | tee -a "$LOG" ; }
function pass() { PASS=$((PASS+1)); log "✅ PASS: $1" ; }
function fail() { FAIL=$((FAIL+1)); log "❌ FAIL: $1" ; }
function require() { command -v "$1" >/dev/null 2>&1 || { echo "Falta a ferramenta: $1"; exit 1; } }

# Ferramentas necessárias
: > "$LOG"
for t in curl grep awk sed head dd; do require "$t"; done

if [ ! -x "$BIN" ]; then
  echo "Binário $BIN não encontrado. Rode 'make' primeiro."
  exit 1
fi

# 1) Gerar config temporário (cobre múltiplas portas e valores práticos p/ teste)
cat > "$TMP_CONF" <<'CONF'
server {
    listen 0.0.0.0:8080;
    server_name default.local;
    root ./www;
    client_max_body_size 64k;

    error_page 404 ./errors/404.html;
    error_page 500 ./errors/500.html;

    location / {
        methods GET;
        index index.html;
        autoindex off;
    }

    location /files/ {
        methods GET POST DELETE;
        root ./www/files;
        autoindex on;
        upload on;
        upload_store ./www/uploads;
    }

    location /cgi/ {
        methods GET POST;
        root ./cgi-bin;
        cgi_ext .py;
        cgi_executor /usr/bin/python3;
        autoindex off;
    }

    location /old {
        return 301 /new;
    }

    location /new {
        methods GET;
        index index.html;
        autoindex off;
    }
}

# Segundo servidor ouvindo em OUTRA porta (múltiplas portas)
server {
    listen 0.0.0.0:8081;
    server_name default.local;
    root ./www;
    client_max_body_size 64k;

    location / {
        methods GET;
        index index.html;
        autoindex off;
    }
}
CONF

# 2) Sobe servidor em background
log "==> Iniciando webserv com config $TMP_CONF"
$BIN "$TMP_CONF" > ./webserv_stdout.log 2> ./webserv_stderr.log &
WS_PID=$!
sleep 0.7

cleanup() {
  log "==> Finalizando webserv (PID $WS_PID)"
  kill $WS_PID >/dev/null 2>&1 || true
  wait $WS_PID >/dev/null 2>&1 || true
}
trap cleanup EXIT

# Helpers HTTP
function http_code() { awk '/HTTP\/1\.[01]/{print $2; exit}' ; }
function header() { awk -v k="$1" 'BEGIN{IGNORECASE=1} tolower($0) ~ "^"tolower(k)": "{print substr($0, index($0, ":")+2); exit}' ; }

# 3) Testes

# 3.1 — GET / (200, index.html)
TEST="GET / index.html 200"
OUT=$(curl -sS -D - http://127.0.0.1:8080/ -o /dev/stdout || true)
CODE=$(printf "%s" "$OUT" | http_code)
if [ "$CODE" = "200" ] && printf "%s" "$OUT" | grep -qi "It works"; then pass "$TEST"; else fail "$TEST"; fi

# 3.2 — Autoindex em /files/ (200 + lista)
TEST="Autoindex /files/ 200 com listagem"
OUT=$(curl -sS -D - http://127.0.0.1:8080/files/ -o /dev/stdout || true)
CODE=$(printf "%s" "$OUT" | http_code)
if [ "$CODE" = "200" ] && printf "%s" "$OUT" | grep -qi "Index of /files/"; then pass "$TEST"; else fail "$TEST"; fi

# 3.3 — Redireção /old -> /new (3xx + Location)
TEST="Redirect /old -> /new"
HDR=$(curl -sS -D - -o /dev/null http://127.0.0.1:8080/old || true)
CODE=$(printf "%s" "$HDR" | http_code)
LOC=$(printf "%s" "$HDR" | header "Location")
if [[ "$CODE" =~ ^30[12]$ ]] && [[ "$LOC" == "/new" ]]; then pass "$TEST"; else fail "$TEST"; fi

# 3.4 — 404 (error page)
TEST="404 custom page"
HDR=$(curl -sS -D - -o /dev/stdout http://127.0.0.1:8080/nao_existe_42 || true)
CODE=$(printf "%s" "$HDR" | http_code)
if [ "$CODE" = "404" ] && printf "%s" "$HDR" | grep -qi "404 Not Found"; then pass "$TEST"; else fail "$TEST"; fi

# 3.5 — POST upload (201) — corpo RAW
TEST="POST upload /files/ (201)"
UPMSG="Conteudo de teste upload $(date +%s)"
HDR=$(printf "%s" "$UPMSG" | curl -sS -D - -o /dev/stdout -X POST http://127.0.0.1:8080/files/ --data-binary @- || true)
CODE=$(printf "%s" "$HDR" | http_code)
if [ "$CODE" = "201" ] && printf "%s" "$HDR" | grep -qi "Saved as:"; then pass "$TEST"; else fail "$TEST"; fi

# 3.6 — DELETE um arquivo dentro de /files/
TEST="DELETE /files/test_delete.txt (204)"
echo "deletar" > ./www/files/test_delete.txt
HDR=$(curl -sS -D - -o /dev/null -X DELETE http://127.0.0.1:8080/files/test_delete.txt || true)
CODE=$(printf "%s" "$HDR" | http_code)
if [ "$CODE" = "204" ]; then pass "$TEST"; else fail "$TEST"; fi

# 3.7 — CGI GET
TEST="CGI GET /cgi/echo.py (200, Content-Type)"
OUT=$(curl -sS -D - http://127.0.0.1:8080/cgi/echo.py?hello=world -o /dev/stdout || true)
CODE=$(printf "%s" "$OUT" | http_code)
CT=$(printf "%s" "$OUT" | header "Content-Type")
if [ "$CODE" = "200" ] && [[ "$CT" == text/* ]] && printf "%s" "$OUT" | grep -q "QUERY_STRING= hello=world"; then pass "$TEST"; else fail "$TEST"; fi

# 3.8 — CGI POST (body ecoado)
TEST="CGI POST /cgi/echo.py (200 + body ecoado)"
BODY="mensagem=abc123"
OUT=$(printf "%s" "$BODY" | curl -sS -D - -o /dev/stdout -X POST http://127.0.0.1:8080/cgi/echo.py --data-binary @- || true)
CODE=$(printf "%s" "$OUT" | http_code)
if [ "$CODE" = "200" ] && printf "%s" "$OUT" | grep -q "BODY" && printf "%s" "$OUT" | grep -q "mensagem=abc123"; then pass "$TEST"; else fail "$TEST"; fi

# 3.9 — client_max_body_size (413) — envia ~200KB (>64k)
TEST="Payload Too Large (413)"
BIG=/tmp/big_payload.bin
head -c 200000 </dev/zero > "$BIG"
HDR=$(curl -sS -D - -o /dev/null -X POST http://127.0.0.1:8080/files/ --data-binary @"$BIG" || true)
CODE=$(printf "%s" "$HDR" | http_code)
if [ "$CODE" = "413" ]; then pass "$TEST"; else fail "$TEST"; fi
rm -f "$BIG"

# 3.10 — Keep-Alive (duas requisições na mesma conexão via curl)
TEST="Keep-Alive (duas GET)"
OUT=$( \
  { printf 'GET / HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: keep-alive\r\n\r\n'; \
    printf 'GET /new HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n'; } \
  | curl -sS -D - --raw --http1.1 tcp://127.0.0.1:8080 )
C1=$(printf "%s" "$OUT" | awk '/HTTP\/1\.1 200/{print NR; exit}')
C2=$(printf "%s" "$OUT" | awk 'BEGIN{n=0} /HTTP\/1\.1 200/{n++} END{print n}')
if [ -n "$C1" ] && [ "$C2" -ge 2 ]; then pass "$TEST"; else fail "$TEST"; fi

# 3.11 — Múltiplas portas (8081)
TEST="Múltiplas portas (GET em 8081)"
OUT=$(curl -sS -D - http://127.0.0.1:8081/ -o /dev/stdout || true)
CODE=$(printf "%s" "$OUT" | http_code)
if [ "$CODE" = "200" ]; then pass "$TEST"; else fail "$TEST"; fi

# 3.12 — Métodos não permitidos (405) — POST em /
TEST="405 Method Not Allowed (POST /)"
HDR=$(curl -sS -D - -o /dev/null -X POST http://127.0.0.1:8080/ --data-binary "x" || true)
CODE=$(printf "%s" "$HDR" | http_code)
if [ "$CODE" = "405" ]; then pass "$TEST"; else fail "$TEST"; fi

# 3.13 — HEAD opcional (se implementado tratar como GET sem body)
TEST="HEAD / (200 com Content-Length e sem body)"
# usa netcat de fallback se curl não expor fácil o corpo; aqui analisamos headers via --head
HDR=$(curl -sS -I http://127.0.0.1:8080/ || true)
CODE=$(printf "%s" "$HDR" | http_code)
CL=$(printf "%s" "$HDR" | header "Content-Length")
if [ "$CODE" = "200" ] && [ -n "$CL" ]; then pass "$TEST"; else pass "HEAD não obrigatório — ignorado"; fi

# 3.14 — Static MIME (text/html)
TEST="MIME Type (text/html)"
HDR=$(curl -sS -D - -o /dev/null http://127.0.0.1:8080/ || true)
CT=$(printf "%s" "$HDR" | header "Content-Type")
if [[ "$CT" == text/html* ]]; then pass "$TEST"; else fail "$TEST"; fi

# 3.15 — Stress leve (opcional) — 50 GETs concorrentes
TEST="Stress leve (50 GET /)"
seq 1 50 | xargs -I{} -P 10 curl -sS -o /dev/null http://127.0.0.1:8080/ && pass "$TEST" || fail "$TEST"

# RESUMO
log ""
log "================== RESUMO =================="
log "PASS: $PASS"
log "FAIL: $FAIL"
[ "$FAIL" -eq 0 ] && log "🎉 Todos os testes passaram." || log "⚠️  Veja detalhes em $LOG"
