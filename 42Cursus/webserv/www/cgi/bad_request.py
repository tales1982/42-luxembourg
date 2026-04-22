#!/usr/bin/env python3
# Emits an explicit 400 status via CGI header
# força 400
print("Status: 400 Bad Request")
print("Content-Type: text/plain")
print()
print("Bad Request (CGI forced 400)")
