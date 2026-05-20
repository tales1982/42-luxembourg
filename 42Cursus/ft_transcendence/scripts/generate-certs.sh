#!/bin/bash
# Generate self-signed TLS certificate for local HTTPS development
set -e

CERTS_DIR="$(dirname "$0")/../certs"
mkdir -p "$CERTS_DIR"

echo "Generating self-signed certificate for localhost..."

openssl req -x509 -newkey rsa:4096 \
  -keyout "$CERTS_DIR/key.pem" \
  -out "$CERTS_DIR/cert.pem" \
  -days 365 \
  -nodes \
  -subj "/CN=localhost" \
  -addext "subjectAltName=DNS:localhost,IP:127.0.0.1"

openssl pkcs12 -export \
  -out "$CERTS_DIR/keystore.p12" \
  -inkey "$CERTS_DIR/key.pem" \
  -in "$CERTS_DIR/cert.pem" \
  -password pass:transcendence123

echo "Certificates generated in certs/"
echo ""
echo "Next steps:"
echo "  1. docker compose up --build backend -d"
echo "  2. Visit https://localhost:8443 in the browser and accept the certificate warning (one-time)"
echo "  3. Frontend at http://localhost:3000 will connect to https://localhost:8443"
