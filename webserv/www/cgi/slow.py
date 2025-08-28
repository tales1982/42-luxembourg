#!/usr/bin/env python3
import time
# força 504 (timeout)
time.sleep(10)
print("Status: 200 OK")
print("Content-Type: text/plain\n")
print("Woke up after 10s (should have timed out)")
