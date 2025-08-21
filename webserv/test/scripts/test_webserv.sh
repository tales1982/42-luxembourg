#!/usr/bin/env bash
# Teste completo para webserv (42)
# Uso: bash test_webserv.sh [--base http://localhost:8080] [--root ./www] [--prepare yes|no]
# Ex.: bash test_webserv.sh --base http://localhost:8080 --root ./www --prepare yes

set -u

BASE_URL="http://localhost:8080"
WWW_ROOT="./www"
PREPARE="yes"

# Parse args
while [[ $# -gt 0 ]]; do
  case "$1" in
    --base) BASE_URL="$2"; shift 2;;
    --root) WWW_ROOT="$2"; shift 2;;
    --prepare) PREPARE="$2"; shift 2;;
    *) echo "arg desconhecido: $1"; exit 1;;
  esac
done

# Cores ANSI
RESET="\033[0m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
CYAN="\033[36m"
BOLD="\033[1m"

pass=0
fail=0
warn=0

hr() { echo -e "${CYAN}------------------------------------------------------------${RESET}"; }
ok() { echo -e "${GREEN}[PASS]${RESET} $*"; pass=$((pass+1)); }
ko() { echo -e "${RED}[FAIL]${RESET} $*"; fail=$((fail+1)); }
ww() { echo -e "${YELLOW}[WARN]${RESET} $*"; warn=$((warn+1)); }

curl_i() {
  # $1 url ; prints headers+body to stdout
  curl -s -i "$1"
}

curl_status() {
  # $1 method ; $2 url ; [$3 data or @file]
  local method="$1" url="$2" data="${3:-}"
  if [[ -z "$data" ]]; then
    curl -s -o /dev/null -w "%{http_code}" -X "$method" "$url"
  else
    curl -s -o /dev/null -w "%{http_code}" -X "$method" "$url" --data-binary "$data"
  fi
}

# Preparar ambiente opcionalmente (pastas e CGI)
if [[ "$PREPARE" == "yes" ]]; then
  hr
  echo -e "${BOLD}Preparando ambiente em ${WWW_ROOT}${RESET}"
  mkdir -p "$WWW_ROOT/files" "$WWW_ROOT/uploads" "$WWW_ROOT/cgi"
  chmod -R 755 "$WWW_ROOT" || true

  # Cria index.html se não existir
  if [[ ! -f "$WWW_ROOT/index.html" ]]; then
    cat > "$WWW_ROOT/index.html" <<'HTML'
<!doctype html><html><head><meta charset="utf-8"><title>webserv 42</title></head>
<body><h1>It works 🎉</h1><ul>
<li><a href="/files/">/files/</a> (autoindex + upload via POST)</li>
<li><a href="/cgi/echo.py?hello=world">/cgi/echo.py</a> (CGI)</li>
<li><a href="/old">/old</a> → /new</li>
</ul></body></html>
HTML
  fi

  # Cria CGI echo.py
  if [[ ! -f "$WWW_ROOT/cgi/echo.py" ]]; then
    cat > "$WWW_ROOT/cgi/echo.py" <<'PY'
#!/usr/bin/env python3
import os,sys
print("Status: 200 OK")
print("Content-Type: text/plain")
print()
print("Hello from CGI!")
print("QUERY_STRING=", os.environ.get("QUERY_STRING",""))
data = sys.stdin.read()
if data:
    print("BODY=", data)
PY
    chmod +x "$WWW_ROOT/cgi/echo.py"
  fi
fi

# Helpers
tmpdir="$(mktemp -d)"
cleanup() { rm -rf "$tmpdir"; }
trap cleanup EXIT

# ------------------ TESTES ------------------

hr; echo -e "${BOLD}1) GET / (estático)${RESET}"
status=$(curl_status GET "$BASE_URL/")
if [[ "$status" == "200" ]]; then ok "GET / -> 200"; else ko "GET / -> $status (esperado 200)"; fi

hr; echo -e "${BOLD}2) HEAD / (Content-Length consistente)${RESET}"
# pega o body do GET e mede bytes
body_file="$tmpdir/get_root_body.html"
curl -s "$BASE_URL/" -o "$body_file"
get_len=$(wc -c < "$body_file" | tr -d ' ')
# pega apenas headers do HEAD
head_headers="$tmpdir/head_headers.txt"
curl -s -I "$BASE_URL/" > "$head_headers"
head_status=$(grep -m1 -Eo 'HTTP/1\.[01] [0-9]+' "$head_headers" | awk '{print $2}')
head_len=$(grep -i '^Content-Length:' "$head_headers" | awk '{print $2}' | tr -d '\r')
if [[ "$head_status" == "200" && "$head_len" == "$get_len" ]]; then
  ok "HEAD / -> Content-Length=$head_len (igual ao GET)"
else
  ko "HEAD / -> status=$head_status Content-Length=$head_len (esperado $get_len)"
fi

hr; echo -e "${BOLD}3) Redirect /old → /new${RESET}"
redir_headers="$tmpdir/redir_headers.txt"
curl -s -I "$BASE_URL/old" > "$redir_headers"
rs=$(grep -m1 -Eo 'HTTP/1\.[01] [0-9]+' "$redir_headers" | awk '{print $2}')
loc=$(grep -i '^Location:' "$redir_headers" | awk '{print $2}' | tr -d '\r')
if [[ "$rs" =~ ^30[12378]$ && "$loc" == "/new" ]]; then ok "redirect ok ($rs Location: /new)"; else ko "redirect falhou: status=$rs Location=$loc"; fi

hr; echo -e "${BOLD}4) Autoindex /files/ (200) ou 403 se desativado${RESET}"
fs_headers="$tmpdir/files_headers.txt"
curl -s -I "$BASE_URL/files/" > "$fs_headers"
fs=$(grep -m1 -Eo 'HTTP/1\.[01] [0-9]+' "$fs_headers" | awk '{print $2}')
if [[ "$fs" == "200" ]]; then ok "/files/ -> 200 (autoindex on)"; elif [[ "$fs" == "403" ]]; then ww "/files/ -> 403 (autoindex off)"; else ko "/files/ -> $fs (esperado 200 ou 403)"; fi

hr; echo -e "${BOLD}5) CGI GET /cgi/echo.py?hello=world${RESET}"
cgi_out="$tmpdir/cgi_out.txt"
curl -s -i "$BASE_URL/cgi/echo.py?hello=world" > "$cgi_out"
cgi_status=$(head -n1 "$cgi_out" | awk '{print $2}')
if [[ "$cgi_status" == "200" ]] && grep -q "Hello from CGI!" "$cgi_out"; then
  ok "CGI -> 200 + conteúdo"
else
  ko "CGI -> status=$cgi_status (e/ou conteúdo ausente). Veja $cgi_out"
fi

hr; echo -e "${BOLD}6) Upload: POST /files/ (cria arquivo)${RESET}"
upload_resp="$tmpdir/upload_resp.txt"
ul_status=$(curl -s -o "$upload_resp" -w "%{http_code}" -X POST "$BASE_URL/files/" --data-binary "teste de upload via script")
if [[ "$ul_status" == "201" ]] && grep -qi '^Saved as:' "$upload_resp"; then
  ok "upload -> 201"; saved=$(awk '/^Saved as:/{print $3}' "$upload_resp")
  echo "  Caminho salvo: $saved"
  # tenta DELETE do arquivo salvo (usa apenas o nome base como URL em /uploads/)
  basefile=$(basename "$saved")
  del_status=$(curl_status DELETE "$BASE_URL/uploads/$basefile")
  if [[ "$del_status" == "204" ]]; then ok "DELETE /uploads/$basefile -> 204"; else ko "DELETE /uploads/$basefile -> $del_status (esperado 204)"; fi
else
  ko "upload -> $ul_status (resp em $upload_resp). Verifique location /files/ e permissão/pasta de upload."
fi

hr; echo -e "${BOLD}7) 405 Method Not Allowed (rota somente GET)${RESET}"
# Tenta POST em /somente-get/ (se não existir, pode dar 404; contamos como WARN)
mna_status=$(curl_status POST "$BASE_URL/somente-get/")
if [[ "$mna_status" == "405" ]]; then ok "POST /somente-get/ -> 405"; else ww "POST /somente-get/ -> $mna_status (location pode não existir na sua config, ok)"; fi

hr; echo -e "${BOLD}8) 413 Payload Too Large (envia 2MB)${RESET}"
big="$tmpdir/big.bin"
# 2 MB
python - <<'PY' > "$big"
import sys
sys.stdout.write("A"* (2*1024*1024))
PY
pl_status=$(curl -s -o /dev/null -w "%{http_code}" -X POST "$BASE_URL/files/" --data-binary @"$big")
if [[ "$pl_status" == "413" ]]; then
  ok "POST grande -> 413"
else
  ww "POST grande -> $pl_status (seu parser pode não fechar cedo; não reprova se o avaliador usar payload menor/config diferente)"
fi

hr; echo -e "${BOLD}9) 404 página padrão (sem error_page)${RESET}"
nf_status=$(curl_status GET "$BASE_URL/inexistente_$(date +%s).html")
if [[ "$nf_status" == "404" ]]; then ok "404 -> 404"; else ko "404 -> $nf_status (esperado 404)"; fi

hr
echo -e "${BOLD}Resumo:${RESET} ${GREEN}${pass} PASS${RESET}, ${RED}${fail} FAIL${RESET}, ${YELLOW}${warn} WARN${RESET}"
exit $(( fail>0 ? 1 : 0 ))
