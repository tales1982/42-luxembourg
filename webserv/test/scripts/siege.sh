#!/usr/bin/env bash
set -euo pipefail

# Usage: ./siege.sh http://127.0.0.1:8080 30 100
#        ./siege.sh <BASE_URL> <DURATION_SECONDS> <CONCURRENCY>
BASE_URL="${1:-http://127.0.0.1:8080}"
DURATION="${2:-30}"
CONCURRENCY="${3:-50}"

if ! command -v siege >/dev/null 2>&1; then
  echo "ERROR: siege not found. Install with: sudo apt-get install -y siege" >&2
  exit 1
fi

echo "[i] Running warm-up..."
siege -b -c 10 -t 10S "$BASE_URL/" || true

echo "[i] Stress test starting: ${DURATION}s at c=${CONCURRENCY}"
URLS_FILE="$(dirname "$0")/siege_urls.txt"
if [[ -f "$URLS_FILE" ]]; then
  siege -b -c "$CONCURRENCY" -t "${DURATION}S" -f "$URLS_FILE"     > siege_report.txt 2>&1 || true
else
  siege -b -c "$CONCURRENCY" -t "${DURATION}S" "$BASE_URL/"     > siege_report.txt 2>&1 || true
fi

echo "[i] Done. Summary:"
grep -E "Availability|Transaction rate|Throughput|Failed transactions" siege_report.txt || true

# Simple pass/fail gate: require availability >= 99.5%
AVAIL=$(grep -E "Availability" siege_report.txt | awk '{print $(NF-0)}' | tr -d '%')
if [[ -n "$AVAIL" ]]; then
  awk -v a="$AVAIL" 'BEGIN { if (a+0 < 99.5) { exit 1 } }' || {
    echo "[!] Availability ${AVAIL}% < 99.5% threshold"; exit 2; }
  echo "[✓] Availability ${AVAIL}% >= 99.5%"
fi

echo "[i] Full report saved at $(pwd)/siege_report.txt"
