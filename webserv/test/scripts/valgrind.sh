#!/usr/bin/env bash
set -euo pipefail

# Usage: ./valgrind.sh ./webserv <config.conf>
BIN="${1:-./webserv}"
CONF="${2:-./conf/example.conf}"

if ! command -v valgrind >/dev/null 2>&1; then
  echo "ERROR: valgrind not found. Install with: sudo apt-get install -y valgrind" >&2
  exit 1
fi

SUPP="$(dirname "$0")/valgrind.supp"
LOG="valgrind.log"

echo "[i] Starting valgrind (it will keep running until you stop the server or send requests)"
echo "[i] You can run ./scripts/siege.sh in another terminal while valgrind is running."
exec valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \  --track-origins=yes --log-file="$LOG" --suppressions="$SUPP" \  "$BIN" "$CONF"
