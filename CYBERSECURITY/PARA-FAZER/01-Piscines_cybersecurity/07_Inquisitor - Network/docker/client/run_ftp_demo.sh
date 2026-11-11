#!/usr/bin/env bash
# Demo FTP client: waits for the FTP server and inquisitor (the
# attacker in the middle) to be ready, then logs in and does a
# download (RETR) and an upload (STOR) so inquisitor has real FTP
# control-channel traffic to sniff.
set -u

FTP_HOST="${FTP_HOST:-ftp-server}"
FTP_USER="${FTP_USER:-ftpuser}"
FTP_PASS="${FTP_PASS:-ftppass}"

echo "[client] waiting for the environment to settle..."
sleep 8

echo "[client] RETR secret_report.pdf"
curl -s -u "$FTP_USER:$FTP_PASS" "ftp://$FTP_HOST/secret_report.pdf" -o /tmp/secret_report.pdf
echo "[client] downloaded $(wc -c </tmp/secret_report.pdf) bytes"

echo "hello from the client, uploaded via FTP" > /tmp/upload_me.txt
echo "[client] STOR upload_me.txt"
curl -s -u "$FTP_USER:$FTP_PASS" -T /tmp/upload_me.txt "ftp://$FTP_HOST/upload_me.txt"

echo "[client] demo FTP session complete."
sleep 2
