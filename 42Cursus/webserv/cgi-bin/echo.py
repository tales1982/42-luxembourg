#!/usr/bin/env python3
import os, sys
body = sys.stdin.read()
print("Status: 200 OK")
print("Content-Type: text/plain")
print("")
print("CGI echo.py")
print("QUERY_STRING=", os.environ.get("QUERY_STRING",""))
print("PATH_INFO=", os.environ.get("PATH_INFO",""))
print("SCRIPT_NAME=", os.environ.get("SCRIPT_NAME",""))
print("REQUEST_METHOD=", os.environ.get("REQUEST_METHOD",""))
print("--- BODY ---")
print(body)
