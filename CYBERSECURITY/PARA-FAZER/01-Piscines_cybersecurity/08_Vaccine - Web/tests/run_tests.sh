#!/usr/bin/env bash
# End-to-end test: starts the local, deliberately-vulnerable test app
# (tests/vulnerable_app.py, authorized since we own it), runs vaccine
# against it over both GET and POST, and checks the JSON results file
# for the expected findings and extracted data.
set -u
cd "$(dirname "$0")/.."

PORT=8123
BASE="http://127.0.0.1:$PORT/products?id=1"
STORE=/tmp/vaccine_selftest_results.json
FAIL=0

pass() { echo "OK   $1"; }
fail() { echo "FAIL $1"; FAIL=1; }

python3 -u tests/vulnerable_app.py "$PORT" >/tmp/vaccine_selftest_app.log 2>&1 &
APP_PID=$!
trap 'kill "$APP_PID" 2>/dev/null' EXIT
sleep 1

rm -f "$STORE"

echo "--- GET ---"
python3 -u ./vaccine -o "$STORE" "$BASE"
GET_EXIT=$?
[ "$GET_EXIT" -eq 0 ] && pass "vaccine exits 0 (vulnerable) on GET" \
    || fail "expected exit 0 on GET, got $GET_EXIT"

echo "--- POST ---"
python3 -u ./vaccine -X POST -o "$STORE" "$BASE"
POST_EXIT=$?
[ "$POST_EXIT" -eq 0 ] && pass "vaccine exits 0 (vulnerable) on POST" \
    || fail "expected exit 0 on POST, got $POST_EXIT"

python3 - "$STORE" <<'EOF'
import json, sys
data = json.load(open(sys.argv[1]))
scans = data["scans"]

def check(cond, label):
    print(("OK   " if cond else "FAIL ") + label)
    return cond

ok = True
ok &= check(len(scans) == 2, "two scans recorded (GET + POST)")

for scan in scans:
    types = {f["type"] for f in scan["findings"]}
    ok &= check({"error", "boolean", "time"} <= types,
                f"{scan['method']}: error+boolean+time findings all present")
    engines = {f["engine"] for f in scan["findings"] if f["engine"]}
    ok &= check("SQLite" in engines, f"{scan['method']}: engine fingerprinted as SQLite")
    ext = scan["extraction"]
    ok &= check(ext is not None, f"{scan['method']}: UNION extraction ran")
    if ext:
        users = ext["databases"].get("main", {}).get("users", {}).get("rows", [])
        usernames = {r.get("username") for r in users}
        ok &= check("admin" in usernames and "alice" in usernames,
                    f"{scan['method']}: users table fully dumped (admin, alice)")
        products = ext["databases"].get("main", {}).get("products", {}).get("rows", [])
        ok &= check(len(products) == 3, f"{scan['method']}: products table fully dumped (3 rows)")

sys.exit(0 if ok else 1)
EOF
[ $? -eq 0 ] || FAIL=1

if [ "$FAIL" -eq 0 ]; then
    echo
    echo "All vaccine end-to-end tests passed."
else
    echo
    echo "Some vaccine end-to-end tests FAILED."
fi
exit "$FAIL"
