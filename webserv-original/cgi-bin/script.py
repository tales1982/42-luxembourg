#!/usr/bin/env python3
import cgi
import datetime

# En-têtes HTTP
print("Content-Type: text/html\r\n\r\n")

# Obtenção da data/hora atual
date_actuelle = datetime.datetime.now().strftime("%d/%m/%Y %H:%M:%S")

# HTML com o mesmo estilo da página de teste
html = f"""
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <title>CGI Esthétique</title>
  <style>
    :root {{
      --bg-start: #1e3c72;
      --bg-end:   #2a5298;
      --box-bg: rgba(255, 255, 255, 0.15);
      --box-border: rgba(255, 255, 255, 0.3);
      --text-main: #ffffff;
      --text-secondary: #e0e0e0;
      --btn-start: #ff416c;
      --btn-end:   #ff4b2b;
      --btn-text:  #ffffff;
    }}

    *, *::before, *::after {{
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }}

    html, body {{
      height: 100%;
    }}

    body {{
      font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
      background: linear-gradient(120deg, var(--bg-start), var(--bg-end));
      background-attachment: fixed;
      display: flex;
      justify-content: center;
      align-items: center;
      color: var(--text-main);
    }}

    .container {{
      position: relative;
      max-width: 400px;
      width: 90%;
      padding: 2rem;
      border-radius: 16px;
      background: var(--box-bg);
      border: 1px solid var(--box-border);
      backdrop-filter: blur(10px);
      box-shadow: 0 8px 32px rgba(0,0,0,0.2);
      text-align: center;
    }}

    p {{
      font-size: 1.25rem;
      line-height: 1.5;
      color: var(--text-secondary);
      margin-bottom: 1.5rem;
    }}

    .btn-refresh {{
      display: inline-block;
      padding: 0.75rem 1.5rem;
      background: linear-gradient(45deg, var(--btn-start), var(--btn-end));
      color: var(--btn-text);
      text-decoration: none;
      font-size: 1rem;
      font-weight: 600;
      border-radius: 50px;
      border: none;
      box-shadow: 0 8px 16px rgba(0,0,0,0.3);
      transition: transform 0.2s ease, box-shadow 0.2s ease;
      cursor: pointer;
      margin: 10px;
    }}

    .btn-refresh:hover {{
      transform: translateY(-4px);
      box-shadow: 0 12px 24px rgba(0,0,0,0.4);
    }}
  </style>
</head>
<body>
  <div class="container">
    <p>🎉 CGI exécuté avec succès</p>
    <p>Date et heure actuelles :<br><strong>{date_actuelle}</strong></p>
    <form method="post">
      <button type="submit" class="btn-refresh">Actualiser</button>
      <a class="btn-refresh" href="http://localhost:8080/tests/index_tests.html">⬅ Retour à la page tests</a>
    </form>
  </div>
</body>
</html>
"""

print(html)
