#!/bin/sh
set -e

echo "Waiting for Vault to be ready..."
MAX_ATTEMPTS=30
ATTEMPT=0
until vault status >/dev/null 2>&1; do
    ATTEMPT=$((ATTEMPT + 1))
    if [ "$ATTEMPT" -ge "$MAX_ATTEMPTS" ]; then
        echo "ERROR: Vault failed to start after $MAX_ATTEMPTS seconds"
        exit 1
    fi
    sleep 1
done
echo "Vault is ready"

echo "Enabling KV secrets engine v2..."
vault secrets enable -path=secret kv-v2 2>/dev/null || echo "Secrets engine already enabled"

# ============================================================
# All secrets stored at secret/transcendence
# Keys use Spring property names so Spring Cloud Vault injects
# them automatically (no env vars needed in the backend).
# ============================================================
echo "Storing all application secrets in Vault..."
vault kv put secret/transcendence \
    "spring.datasource.username=transcendence" \
    "spring.datasource.password=transcendence123" \
    "jwt.secret=bXlTZWNyZXRLZXlGb3JKV1RUb2tlbkdlbmVyYXRpb25UaGF0SXNBdExlYXN0MjU2Qml0c0xvbmcxMjM0NTY3ODk=" \
    "blockchain.rpc-url=https://eth-sepolia.g.alchemy.com/v2/amXFYaunCo1a-njVqtBYQqB3whzUVX4_" \
    "blockchain.contract-address=0x273FA47B2401c583D615b44Cd435707FA7383Eed" \
    "blockchain.minter-private-key=${BLOCKCHAIN_MINTER_KEY:-}"

echo "Vault secrets initialized successfully!"
echo "Stored keys at secret/transcendence:"
vault kv get secret/transcendence | grep -E "^(spring\.|jwt\.|blockchain\.)" || true

exit 0
