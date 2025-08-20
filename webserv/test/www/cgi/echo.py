#!/usr/bin/env python3
import os,sys
print("Status: 200 OK")
print("Content-Type: text/plain")
print()
print("Hello from CGI!")
print("QUERY_STRING=", os.environ.get("QUERY_STRING",""))
data = sys.stdin.read()
if data:
    print("BODY=", data)
