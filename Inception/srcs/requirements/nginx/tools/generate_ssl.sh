#!/bin/bash
# Diretório onde os certificados serão armazenados (executado na pasta onde está o script)
TOOLS_DIR="."  
CERT_FILE="${TOOLS_DIR}/cert.pem"
KEY_FILE="${TOOLS_DIR}/key.pem"
DOMAIN="tlima-de.42.fr"

mkdir -p "${TOOLS_DIR}"

if [ -f "${CERT_FILE}" ] && [ -f "${KEY_FILE}" ]; then
  echo "Certificado e chave já existem em ${TOOLS_DIR}."
else
  echo "Gerando certificado autoassinado para ${DOMAIN}..."
  openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout "${KEY_FILE}" \
    -out "${CERT_FILE}" \
    -subj "/CN=${DOMAIN}"
  if [ $? -eq 0 ]; then
    echo "Certificado e chave gerados com sucesso em ${TOOLS_DIR}."
  else
    echo "Erro ao gerar certificado."
    exit 1
  fi
fi
