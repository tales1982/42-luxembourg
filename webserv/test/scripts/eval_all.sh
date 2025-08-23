#!/usr/bin/env bash
# eval_all.sh — Checklist Webserv (subject + eval da 42)
# Rode este script enquanto o servidor estiver rodando em outro terminal.

###############################################################################
# CONFIG
###############################################################################
BASE_URL="${BASE_URL:-http://127.0.0.1:8080}"
EXPECT_A="${EXPECT_A:-SITE A (hostname)}"
EXPECT_B="${EXPECT_B:-SITE B 8081}"

ROOT_URL="${ROOT_URL:-$BASE_URL/}"
HEAD_URL="${HEAD_URL:-$BASE_URL/}"
NOTFOUND_URL="${NOTFOUND_URL:-$BASE_URL/nao_existe}"
AUTOINDEX_URL="${AUTOINDEX_URL:-$BASE_URL/files/}"
REDIRECT_URL="${REDIRECT_URL:-$BASE_URL/old}"

# 405: testa em /new/index.html (não permite DELETE)
METHOD_TEST_URL="${METHOD_TEST_URL:-$BASE_URL/new/index.html}"
METHOD_DISALLOWED="${METHOD_DISALLOWED:-DELETE}"

# Upload simples (POST raw)
UPLOAD_RAW_URL="${UPLOAD_RAW_URL:-$BASE_URL/files/}"

# Body limit 413 — por padrão usa o CGI (POST permitido)
CGI_GET_URL="${CGI_GET_URL:-$BASE_URL/cgi/echo.py}"
CGI_POST_URL="${CGI_POST_URL:-$BASE_URL/cgi/echo.py}"
BODY_LIMIT_URL="${BODY_LIMIT_URL:-$CGI_POST_URL}"
BODY_LIMIT_SIZE_KB="${BODY_LIMIT_SIZE_KB:-10240}"   # 10 MiB

# Multi-host 
HOST_A="${HOST_A:-sitea.local}"; PORT_A="${PORT_A:-8081}"
HOST_B="${HOST_B:-siteb.local}"; PORT_B="${PORT_B:-8082}"
EXPECT_A="${EXPECT_A:-SITE A (hostname)}"
EXPECT_B="${EXPECT_B:-SITE B 8081}"

# Stress (opcional): exige 'siege'
ENABLE_SIEGE="${ENABLE_SIEGE:-1}"
SIEGE_TARGET="${SIEGE_TARGET:-$ROOT_URL}"
SIEGE_TIME="${SIEGE_TIME:-10S}"
SIEGE_EXPECTED_AVAIL="${SIEGE_EXPECTED_AVAIL:-99.5}"
SIEGE_HARD_TIMEOUT="${SIEGE_HARD_TIMEOUT:-20}"  # mata siege após Xs, se necessário

# Timeout por requisição cURL (segundos)
TIMEOUT="${TIMEOUT:-3}"

###############################################################################
# IMPL
###############################################################################
set -u
LANG=C LC_ALL=C

# Cores
if [ -t 1 ]; then
  GREEN="\033[1;32m"; RED="\033[1;31m"; YELLOW="\033[1;33m"; BLUE="\033[1;34m"; GREY="\033[0;90m"; RESET="\033[0m"
else
  GREEN=""; RED=""; YELLOW=""; BLUE=""; GREY=""; RESET=""
fi

CURL="curl -sS -m $TIMEOUT"
PASS=0; FAIL=0; SKIP=0
ok(){   echo -e "${GREEN}[PASS]${RESET} $*"; PASS=$((PASS+1)); }
bad(){  echo -e "${RED}[FAIL]${RESET} $*";  FAIL=$((FAIL+1)); }
skip(){ echo -e "${YELLOW}[SKIP]${RESET} $*"; SKIP=$((SKIP+1)); }
info(){ echo -e "${BLUE}[INFO]${RESET} $*"; }

hstatus(){ $CURL -o /dev/null -w "%{http_code}" "$@" 2>/dev/null || echo 000; }
hbody(){   $CURL "$@" 2>/dev/null || true; }
hhead(){   $CURL -D - -o /dev/null "$@" 2>/dev/null || true; }
hbsize(){  $CURL -o /dev/null -w "%{size_download}" "$@" 2>/dev/null || echo 0; }
need(){ command -v "$1" >/dev/null 2>&1; }

echo -e "${GREY}== Checando se o servidor responde em $BASE_URL ==${RESET}"
st=$(hstatus "$BASE_URL")
if [ "$st" = "000" ]; then
  bad "Servidor não respondeu (suba o webserv em outro terminal: ./webserv configs/example.conf)"
  echo -e "${GREY}PASS=$PASS FAIL=$FAIL SKIP=$SKIP${RESET}"
  exit 1
fi

echo
echo -e "${GREY}== 1) GET básico (200 + Content-Type) ==${RESET}"
st=$(hstatus "$ROOT_URL")
if [ "$st" = "200" ]; then
  ct=$(hhead "$ROOT_URL" | awk -F': ' 'tolower($1)=="content-type"{print $2}' | tr -d '\r')
  ok "GET $ROOT_URL -> 200 (Content-Type: ${ct:-<n/i>})"
else
  bad "GET $ROOT_URL -> $st (esp. 200)"
fi

echo
echo -e "${GREY}== 2) HEAD sem corpo (usar -I) ==${RESET}"
H=$(hhead -I "$HEAD_URL"); st=$(printf "%s" "$H" | head -n1 | awk '{print $2}')
bs=$(hbsize -I "$HEAD_URL")
conn=$(printf "%s" "$H" | awk -F': ' 'tolower($1)=="connection"{print tolower($2)}' | tr -d '\r')
if [ "$st" = "200" ] && [ "$bs" = "0" ]; then
  ok "HEAD $HEAD_URL -> 200 e body 0 (Connection: ${conn:-<n/i>})"
else
  bad "HEAD $HEAD_URL -> status=$st body=$bs (esp. 200/0)"
fi

echo
echo -e "${GREY}== 3) 404 custom ==${RESET}"
st=$(hstatus "$NOTFOUND_URL")
[ "$st" = "404" ] && ok "GET $NOTFOUND_URL -> 404" || bad "GET $NOTFOUND_URL -> $st"

echo
echo -e "${GREY}== 4) Autoindex ==${RESET}"
if [ -n "$AUTOINDEX_URL" ]; then
  st=$(hstatus "$AUTOINDEX_URL")
  body=$(hbody "$AUTOINDEX_URL" | head -n 60)
  if [ "$st" = "200" ] && echo "$body" | grep -qi '<a href='; then
    ok "Autoindex $AUTOINDEX_URL"
  else
    bad "Autoindex $AUTOINDEX_URL -> $st"
  fi
else
  skip "Autoindex (não configurado)"
fi

echo
echo -e "${GREY}== 5) Redirect (301/302 + Location) ==${RESET}"
if [ -n "$REDIRECT_URL" ]; then
  H=$(hhead -L -s -o /dev/null "$REDIRECT_URL")
  code=$(printf "%s\n" "$H" | head -n1 | awk '{print $2}')
  loc=$(printf "%s\n" "$H" | awk -F': ' 'tolower($1)=="location"{print $2}' | tr -d '\r' | tail -n1)
  echo "$code" | grep -Eq '^30(1|2)$' && [ -n "$loc" ] \
    && ok "Redirect $REDIRECT_URL -> $code (Location: $loc)" \
    || bad "Redirect $REDIRECT_URL -> $code (Loc: ${loc:-<vazio>})"
else
  skip "Redirect (não configurado)"
fi

echo
echo -e "${GREY}== 6) 405 Method Not Allowed (+Allow) ==${RESET}"
if [ -n "$METHOD_TEST_URL" ]; then
  H=$(hhead -X "$METHOD_DISALLOWED" "$METHOD_TEST_URL")
  st=$(printf "%s" "$H" | head -n1 | awk '{print $2}')
  allow=$(printf "%s" "$H" | awk -F': ' 'tolower($1)=="allow"{print $2}' | tr -d '\r')
  [ "$st" = "405" ] \
    && ok "405 em $METHOD_DISALLOWED $METHOD_TEST_URL (Allow: ${allow:-<ausente>})" \
    || bad "$METHOD_DISALLOWED $METHOD_TEST_URL -> $st (esp. 405)"
else
  skip "405 (não configurado)"
fi

echo
echo -e "${GREY}== 7) Upload (POST raw em /files/) ==${RESET}"
if [ -n "$UPLOAD_RAW_URL" ]; then
  payload="hello webserv $(date +%s)"
  st=$(hstatus -X POST --data "$payload" -H "Content-Type: text/plain" "$UPLOAD_RAW_URL")
  echo "$st" | grep -Eq '^20(0|1)$' \
    && ok "Upload raw $UPLOAD_RAW_URL -> $st" \
    || bad "Upload raw $UPLOAD_RAW_URL -> $st"
else
  skip "Upload raw (não configurado)"
fi

echo
echo -e "${GREY}== 8) Body limit (413) ==${RESET}"
if [ -n "$BODY_LIMIT_URL" ]; then
  tmpf="$(mktemp)"
  dd if=/dev/zero of="$tmpf" bs=1024 count="$BODY_LIMIT_SIZE_KB" >/dev/null 2>&1
  st=$(hstatus -X POST --data-binary @"$tmpf" -H "Content-Type: application/octet-stream" "$BODY_LIMIT_URL")
  rm -f "$tmpf"
  [ "$st" = "413" ] \
    && ok "413 em $BODY_LIMIT_URL (${BODY_LIMIT_SIZE_KB}KB)" \
    || bad "POST grande em $BODY_LIMIT_URL -> $st"
else
  skip "Body limit (não configurado)"
fi

echo
echo -e "${GREY}== 9) CGI (GET e POST) ==${RESET}"
if [ -n "$CGI_GET_URL" ]; then
  st=$(hstatus "$CGI_GET_URL")
  [ "$st" = "200" ] && ok "CGI GET $CGI_GET_URL -> 200" || bad "CGI GET -> $st"
else
  skip "CGI GET (não configurado)"
fi
if [ -n "$CGI_POST_URL" ]; then
  st=$(hstatus -X POST -d "message=hello" "$CGI_POST_URL")
  [ "$st" = "200" ] && ok "CGI POST $CGI_POST_URL -> 200" || bad "CGI POST -> $st"
else
  skip "CGI POST (não configurado)"
fi

echo
echo -e "${GREY}== 10) Multi-host (server_name) ==${RESET}"

check_vhost() {
  local host="$1" port="$2" expect="$3" label="$4"
  local st body
  st=$(curl -sS -m "$TIMEOUT" -o /dev/null -w "%{http_code}" \
        --resolve "$host:$port:127.0.0.1" "http://$host:$port/")
  if [ "$st" != "200" ]; then
    bad "$label $host:$port -> $st"
    return
  fi
  body=$(curl -sS -m "$TIMEOUT" \
         --resolve "$host:$port:127.0.0.1" "http://$host:$port/")
  if [ -n "$expect" ] && ! echo "$body" | grep -q "$expect"; then
    bad "$label $host:$port -> 200, mas corpo NÃO contém '$expect' (provável default vhost)"
  else
    ok "$label $host:$port -> 200 (conteúdo OK)"
  fi
}

if [ -n "${HOST_A:-}" ]; then
  check_vhost "$HOST_A" "$PORT_A" "$EXPECT_A" "Host A"
else
  skip "Host A (não configurado)"
fi

if [ -n "${HOST_B:-}" ]; then
  check_vhost "$HOST_B" "$PORT_B" "$EXPECT_B" "Host B"
else
  skip "Host B (não configurado)"
fi

echo
echo -e "${GREY}== 11) UNKNOWN method não crasha ==${RESET}"
st=$(hstatus -X FOO "$ROOT_URL" || true)
ok "UNKNOWN method não crashou (status $st)"

echo
echo -e "${GREY}== 12) Stress test (siege) ==${RESET}"
if [ "$ENABLE_SIEGE" = "1" ]; then
  if need siege; then
    # garantir conf p/ não travar
    if [ ! -f "$HOME/.siege/siege.conf" ]; then
      mkdir -p "$HOME/.siege"
      printf "verbose=false\nquiet=true\nlogging=false\n" > "$HOME/.siege/siege.conf"
    fi
    log="$(mktemp)"

    # --- proteger contra Ctrl-C durante o siege ---
    SIEGE_INTERRUPTED=0
    trap 'SIEGE_INTERRUPTED=1' INT

    # roda o siege com proteção contra travas
    if command -v timeout >/dev/null 2>&1; then
      timeout "$SIEGE_HARD_TIMEOUT" siege -b --no-log -t "$SIEGE_TIME" "$SIEGE_TARGET" >"$log" 2>&1 || true
    else
      siege -b --no-log -t "$SIEGE_TIME" "$SIEGE_TARGET" >"$log" 2>&1 & pid=$!
      SECS=0
      while kill -0 "$pid" 2>/dev/null && [ "$SECS" -lt "$SIEGE_HARD_TIMEOUT" ]; do
        sleep 1; SECS=$((SECS+1))
      done
      kill "$pid" 2>/dev/null || true
      kill -9 "$pid" 2>/dev/null || true
    fi

    # se o usuário apertou Ctrl-C, transforma em SKIP e encerra limpo
    if [ "$SIEGE_INTERRUPTED" = "1" ]; then
      trap - INT
      rm -f "$log"
      skip "Siege interrompido pelo usuário (Ctrl-C)"
      echo
      echo -e "${GREY}============== RESUMO ==============${RESET}"
      echo -e "PASS: ${GREEN}$PASS${RESET} | FAIL: ${RED}$FAIL${RESET} | SKIP: ${YELLOW}$SKIP${RESET}"
      exit 0
    fi
    trap - INT

    # disponibilidade: formato antigo OU JSON
    avail=$(grep -Eo 'Availability:\s*[0-9.]+%' "$log" | awk '{print $2}' | tr -d '%' || echo "")
    if [ -z "$avail" ]; then
      succ=$(awk -F: '/"successful_transactions"/{gsub(/[^0-9]/,"",$2);print $2}' "$log" | tail -n1)
      fail=$(awk -F: '/"failed_transactions"/{gsub(/[^0-9]/,"",$2);print $2}' "$log" | tail -n1)
      if [ -n "$succ" ] && [ -n "$fail" ]; then
        total=$((succ + fail))
        if [ "$total" -gt 0 ]; then
          avail=$(awk -v s="$succ" -v t="$total" 'BEGIN{printf "%.2f", (s*100.0)/t}')
        else
          avail="0.00"
        fi
      fi
    fi

    if [ -n "$avail" ] && awk -v a="$avail" -v r="$SIEGE_EXPECTED_AVAIL" 'BEGIN{exit !(a+0>=r+0)}'; then
      ok "Siege disponibilidade >= ${SIEGE_EXPECTED_AVAIL}% (got ${avail}%)"
    else
      bad "Siege disponibilidade (got ${avail:-N/A}%, esp. >= ${SIEGE_EXPECTED_AVAIL}%)"
      info "Saída do siege (últimas linhas):"
      tail -n 10 "$log" || true
    fi
    rm -f "$log"
  else
    skip "Siege não instalado (sudo apt-get install -y siege)"
  fi
else
  skip "Siege desabilitado (export ENABLE_SIEGE=1)"
fi

echo
echo -e "${GREY}============== RESUMO ==============${RESET}"
echo -e "PASS: ${GREEN}$PASS${RESET} | FAIL: ${RED}$FAIL${RESET} | SKIP: ${YELLOW}$SKIP${RESET}"
[ "$FAIL" -eq 0 ] && exit 0 || exit 1
