#!/usr/bin/env bash
set -euo pipefail

# Uso:
#   ./test/scripts/valgrind.sh [./webserv] [./configs/example.conf]
BIN="${1:-./webserv}"
CONF="${2:-./configs/example.conf}"

if ! command -v valgrind >/dev/null 2>&1; then
  echo "ERROR: valgrind not found. Install with: sudo apt-get install -y valgrind" >&2
  exit 1
fi

if [ ! -x "$BIN" ]; then
  echo "ERROR: binary not found or not executable: $BIN" >&2
  exit 1
fi
if [ ! -f "$CONF" ]; then
  echo "ERROR: config file not found: $CONF" >&2
  exit 1
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SUPP="$SCRIPT_DIR/valgrind.supp"
LOG="${LOG:-valgrind.log}"

echo "[i] Starting valgrind (Ctrl+C para parar)"
echo "[i] Em outro terminal, você pode rodar eval_all.sh"

# Monta os argumentos do valgrind de forma segura
ARGS=(
  "--tool=memcheck"
  "--leak-check=full"
  "--show-leak-kinds=all"
  "--track-origins=yes"
  "--log-file=$LOG"
)
# Só adiciona suppressions se o arquivo existir
[ -f "$SUPP" ] && ARGS+=("--suppressions=$SUPP")

exec valgrind "${ARGS[@]}" "$BIN" "$CONF"
