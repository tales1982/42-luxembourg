#!/usr/bin/env python3

import os
import urllib.parse

print("Content-Type: text/html\r\n\r\n")

# Função auxiliar para listar arquivos de um diretório
def listar_arquivos_em(diretorio_web, path_url):
    base = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'www', diretorio_web))
    lista = ""

    if not os.path.isdir(base):
        return "<li><em>Dossier introuvable.</em></li>"

    for fname in os.listdir(base):
        full_path = os.path.join(base, fname)
        if os.path.isfile(full_path):
            href = f"/{path_url}/" + urllib.parse.quote(fname)
            lista += f'<li><a href="{href}" download>{fname}</a></li>\n'

    return lista or "<li><em>Aucun fichier disponible.</em></li>"

# Gera seções separadas
list_othes = listar_arquivos_em('othes', 'othes')
list_fotos = listar_arquivos_em('fotos', 'fotos')
list_pdfs = listar_arquivos_em('pdfs', 'pdfs')

# HTML moderno com glassmorphism
print(f"""
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <title>Téléchargement de fichiers</title>
  <style>
    * {{
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }}
    body {{
      font-family: 'Segoe UI', sans-serif;
      background: linear-gradient(135deg, #74ebd5, #9face6);
      color: #ffffff;
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 2rem;
    }}
    .container {{
      background: rgba(255, 255, 255, 0.08);
      border: 1px solid rgba(255, 255, 255, 0.2);
      border-radius: 16px;
      padding: 2rem;
      max-width: 700px;
      width: 100%;
      backdrop-filter: blur(10px);
      box-shadow: 0 12px 32px rgba(0, 0, 0, 0.25);
      text-align: center;
    }}
    h1 {{
      font-size: 1.8rem;
      margin-bottom: 1rem;
      color: #ffeaa7;
    }}
    h2 {{
      margin-top: 2rem;
      margin-bottom: 0.5rem;
      color: #fab1a0;
    }}
    ul {{
      list-style: none;
      padding: 0;
    }}
    li {{
      margin: 0.7rem 0;
      margin:24px;
    }}
    a {{
      color: #2d3436;
      background: #ffffff;
      padding: 0.5rem 1.2rem;
      border-radius: 12px;
      text-decoration: none;
      font-weight: bold;
      transition: background 0.3s;
    }}
    a:hover {{
      background: #f1f1f1;
    }}
    .back {{
      display: inline-block;
      margin-top: 2rem;
      padding: 0.6rem 1.5rem;
      background: #ff7675;
      color: white;
      border-radius: 50px;
      text-decoration: none;
      font-weight: bold;
    }}
    .back:hover {{
      background: #d63031;
    }}
  </style>
</head>
<body>
  <div class="container">
    <h1>📥 Téléchargements disponibles</h1>

    <h2>📂 Dossier "othes"</h2>
    <ul>{list_othes}</ul>

    <h2>🖼️ Dossier "fotos"</h2>
    <ul>{list_fotos}</ul>

    <h2>📄 Dossier "pdfs"</h2>
    <ul>{list_pdfs}</ul>

    <a class="back" href="/">⬅ Retour à l'accueil</a>
    <a class="back" href="http://localhost:8080/tests/index_tests.html">⬅ Retour à la page tests</a>
  </div>
</body>
</html>
""")
