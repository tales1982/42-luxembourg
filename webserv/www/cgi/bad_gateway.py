#!/usr/bin/env python3
# Output an invalid HTTP-like first line to trigger 502 at the server
# (e.g., missing 'Status:' / malformed headers)
# força 502 (headers inválidos)
import sys
sys.stdout.write("BOGUS HEADER LINE\r\n")
sys.stdout.write("\r\n")
sys.stdout.flush()
