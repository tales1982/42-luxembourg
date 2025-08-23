#!/usr/bin/env bash
set -e

# ===== Config para o teu example.conf =====
export BASE_URL="http://127.0.0.1:8080"
export ROOT_URL="$BASE_URL/"
export HEAD_URL="$BASE_URL/"

# /files/ (aparece na tua home) → autoindex + uploads por POST (raw)
export AUTOINDEX_URL="$BASE_URL/files/"

# redirect /old -> /new
export REDIRECT_URL="$BASE_URL/old"

# 405: tentar DELETE em um arquivo estático
export METHOD_TEST_URL="$BASE_URL/files/index.html"
export METHOD_DISALLOWED="DELETE"

# Upload multipart: teu site usa POST "raw" em /files/, então vamos pular multipart:
unset UPLOAD_URL
unset UPLOAD_DOWNLOAD_URL

# Body limit 413: só ative se tiver client_max_body_size definido e uma rota POST
# export BODY_LIMIT_URL="$BASE_URL/cgi/echo.py"
# export BODY_LIMIT_SIZE_KB="2048"

# CGI GET/POST
export CGI_GET_URL="$BASE_URL/cgi/echo.py"
export CGI_POST_URL="$BASE_URL/cgi/echo.py"

# Hosts virtuais: não configurados no teu example.conf → pular
unset HOST_A HOST_B

# Siege (stress): ative se tiver instalado
export ENABLE_SIEGE=1
export SIEGE_TARGET="$BASE_URL/"
export SIEGE_TIME="10S"
export SIEGE_EXPECTED_AVAIL="99.5"

# Valgrind desativado por padrão
export ENABLE_VALGRIND=0

# ===== Executa o checklist =====
./webserv_check.sh ./webserv configs/example.conf
