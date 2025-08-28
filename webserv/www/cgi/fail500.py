#!/usr/bin/env python3
# Crash to simulate internal server error
# força 500 (exceção)
import sys
sys.stderr.write("CGI crashed intentionally\n")
raise RuntimeError("Intentional failure")
