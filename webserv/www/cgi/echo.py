#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os, sys, html
from urllib.parse import parse_qs
from datetime import datetime

def read_post_data():
    try:
        length = int(os.environ.get("CONTENT_LENGTH", "0") or 0)
    except ValueError:
        length = 0
    return sys.stdin.read(length) if length > 0 else ""

method = (os.environ.get("REQUEST_METHOD") or "GET").upper()
qs = os.environ.get("QUERY_STRING", "")
get_params = parse_qs(qs, keep_blank_values=True)

post_raw = read_post_data() if method == "POST" else ""
post_ct = (os.environ.get("CONTENT_TYPE") or "").split(";")[0].strip().lower()
post_params = parse_qs(post_raw, keep_blank_values=True) if post_ct in ("application/x-www-form-urlencoded", "") else {}

# name can come from POST or GET
name = ""
for src in (post_params, get_params):
    if "name" in src and src["name"]:
        name = src["name"][0]
        break
name = name.strip()

client_ip = os.environ.get("REMOTE_ADDR", "unknown")
now_str   = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
safe_name = html.escape(name)

html_body = f"""<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>CGI • Echo & Welcome</title>
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <style>
    * {{ margin:0; padding:0; box-sizing:border-box; font-family: "Segoe UI", Roboto, sans-serif; }}
    html, body {{ height:100%; }}
    body {{
      color:#fff; min-height:100vh; display:flex; justify-content:center; align-items:center; padding:40px;
      /* image is applied via JS (with cache-buster) */
      background-color:#111;
      background-position:center center; background-repeat:no-repeat;
      background-attachment:fixed; background-size:cover;
    }}
    .card {{
      background: rgba(0,0,0,0.45);
      padding: 36px; border-radius: 16px; width: 100%; max-width: 720px; text-align: center;
      box-shadow: 0 8px 24px rgba(0,0,0,0.5); backdrop-filter: blur(4px);
    }}
    h1 {{ font-size: 2.2rem; margin-bottom: 8px; color:#ffda79; text-shadow: 0 0 10px rgba(255,218,121,.7); }}
    p.lead {{ margin-bottom: 18px; opacity:.9; }}
    form {{ margin: 18px auto 10px; text-align:left; max-width: 520px; }}
    label {{ display:block; margin: 8px 0 6px; color:#ffd86b; font-weight:600; }}
    input[type="text"] {{
      width:100%; padding:12px 14px; border-radius:10px; border:none; outline:none; font-size:1rem;
      background: rgba(255,255,255,0.15); color:#fff;
    }}
    .row {{ display:flex; gap:12px; margin-top:12px; }}
    button {{
      padding:12px 20px; border:none; border-radius:10px; cursor:pointer; font-weight:700;
      background: linear-gradient(135deg, #ffda79, #ff9a3c); color:#000;
      transition: transform .15s, box-shadow .15s;
    }}
    button:hover {{ transform: translateY(-2px); box-shadow: 0 4px 12px rgba(255,218,121,.6); }}
    .muted {{ opacity:.8; font-size:.95rem; }}
    .box {{ background: rgba(0,0,0,0.35); padding:12px 14px; border-radius:10px; margin-top:14px; }}
    .ok  {{ color:#90ee90; }}
    .mono {{ font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace; }}

    /* Debug bar same as home */
    #dbgbar{{ position:fixed; top:8px; left:8px; z-index:9999; background:#000a; color:#fff;
             padding:6px 10px; border-radius:6px; font:14px system-ui; display:flex; gap:8px; align-items:center; }}
    #dbgthumb{{ height:44px; border-radius:6px; border:2px solid #fff; }}
    #dbginfo small{{ display:block; opacity:.85; }}
    #dbginfo a{{ color:#00e0ff; text-decoration:none; }}
    #dbginfo a:hover{{ text-decoration:underline; }}
  </style>
</head>
<body>

  <div id="dbgbar">
    <strong>DEBUG IMG</strong>
    <img id="dbgthumb" alt="(thumb)" />
    <div id="dbginfo">
      <div id="dbgstatus">loading…</div>
      <small><a id="dbglink" href="#" target="_blank" rel="noopener">open image</a></small>
    </div>
  </div>

  <div class="card">
    <h1>⚡ Dynamic CGI</h1>
    <p class="lead">Type your name to receive a welcome message with date, time and IP.</p>

    <form method="GET" action="/cgi/echo.py">
      <label for="name">Your name</label>
      <div class="row">
        <input type="text" id="name" name="name" placeholder="E.g.: Tales" value="{safe_name}">
        <button type="submit">Send</button>
      </div>
    </form>

    {("<div class='box ok'><strong>Welcome, " + safe_name + "!</strong><br>Now: " + html.escape(now_str) + " &middot; Your IP: <span class='mono'>" + html.escape(client_ip) + "</span></div>") if safe_name else ""}

    <div class="box muted">
      <div><strong>Method:</strong> {html.escape(method)}</div>
      <div><strong>QUERY_STRING:</strong> <span class="mono">{html.escape(qs)}</span></div>
    </div>
    <!-- Botão Home -->
<a href="/" class="home-btn"><button type="button">⬅ Back to Home</button></a>

  </div>
  

  <script>
    // Same logic as home: cache-buster + thumb + status
    const base = "/images/serve7.jpg";
    const url  = base + "?cb=" + Date.now();

    document.getElementById("dbglink").href = base;

    const thumb = document.getElementById("dbgthumb");
    thumb.src = url;

    const statusEl = document.getElementById("dbgstatus");
    fetch(url, {{ cache: "no-store" }}).then((res) => {{
      statusEl.textContent = "fetch: " + res.status + " " + res.statusText;
      if (res.ok) {{
        document.body.style.backgroundImage = `url("${{url}}")`;
        document.body.style.backgroundPosition = "center center";
        document.body.style.backgroundRepeat = "no-repeat";
        document.body.style.backgroundAttachment = "fixed";
        document.body.style.backgroundSize = "cover";
      }}
    }}).catch((e) => {{
      statusEl.textContent = "fetch ERROR: " + e;
    }});
  </script>
</body>
</html>
"""

print("Status: 200 OK")
print("Content-Type: text/html; charset=utf-8")
print()
sys.stdout.write(html_body)
