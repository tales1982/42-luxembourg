#!/bin/bash

SERVER_URL="http://localhost:8080"
UPLOAD_FILE="test_upload.txt"
CGI_SCRIPT="cgi-bin/test.py"
TEST_DIR="fotos"
UPLOAD_ENDPOINT="/upload"
REDIRECT_PATH="/redirect301"
PROTECTED_FILE="protected_file.txt"

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m" # No Color

# Criação de arquivos e permissões
touch $UPLOAD_FILE
echo "Teste de upload automático" > $UPLOAD_FILE
chmod 000 www/$PROTECTED_FILE

print_result() {
  local code=$1
  local expected=$2
  local message=$3

  if [[ "$code" == "$expected" ]]; then
    echo -e "✅ ${GREEN}$message ($code)${NC}"
  else
    echo -e "❌ ${RED}$message ($code, esperado: $expected)${NC}"
  fi
}

echo "🧪 Iniciando testes automáticos do Webserv..."

# 1. Página inicial
code=$(curl -s -o /dev/null -w "%{http_code}" "$SERVER_URL/")
print_result "$code" "200" "Página inicial"

# 2. Autoindex
code=$(curl -s -o /dev/null -w "%{http_code}" "$SERVER_URL/$TEST_DIR/")
print_result "$code" "200" "Autoindex (listagem de diretório)"

# 3. Upload
code=$(curl -s -o /dev/null -w "%{http_code}" -F "file=@$UPLOAD_FILE" "$SERVER_URL$UPLOAD_ENDPOINT")
print_result "$code" "200" "Upload de arquivo"

# 4. Executar CGI
code=$(curl -s -o /dev/null -w "%{http_code}" "$SERVER_URL/$CGI_SCRIPT")
print_result "$code" "200" "CGI Python"

# 5. Redirecionamento
code=$(curl -s -o /dev/null -w "%{http_code}" "$SERVER_URL$REDIRECT_PATH")
print_result "$code" "301" "Redirecionamento 301"

# 6. Erro 405
code=$(curl -s -o /dev/null -w "%{http_code}" -X DELETE "$SERVER_URL/")
print_result "$code" "405" "Método não permitido (DELETE /)"

# 7. Erro 403
code=$(curl -s -o /dev/null -w "%{http_code}" "$SERVER_URL/$PROTECTED_FILE")
print_result "$code" "403" "Permissão negada (403)"

# 8. Erro 404
code=$(curl -s -o /dev/null -w "%{http_code}" "$SERVER_URL/arquivo-inexistente.html")
print_result "$code" "404" "Arquivo não encontrado (404)"

# 9. DELETE válido
UPLOAD_NAME=$(ls www/fotos/ | grep -E '^file_' | head -n 1)
if [ -n "$UPLOAD_NAME" ]; then
  code=$(curl -s -o /dev/null -w "%{http_code}" -X DELETE "$SERVER_URL/fotos/$UPLOAD_NAME")
  print_result "$code" "204" "Deleção de arquivo válido"
else
  echo "⚠️ Nenhum arquivo encontrado para deletar. Pulei o teste DELETE."
fi


# Limpeza
rm -f $UPLOAD_FILE
chmod 644 www/$PROTECTED_FILE
rm -f www/$PROTECTED_FILE

echo -e "\n🧪 ${GREEN}Todos os testes executados.${NC}"
