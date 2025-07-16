#!/usr/bin/env python3
import cgi
import datetime

# Définition des en-têtes
print("Content-Type: text/html; charset=utf-8")
print()

# Obtention de la date/heure actuelle
date_actuelle = datetime.datetime.now().strftime("%d/%m/%Y %H:%M:%S")

# HTML de sortie avec style CSS inline pour un rendu moderne
html = f"""
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>CGI Esthétique</title>
    <style>
        body {{
            margin: 0;
            padding: 0;
            font-family: 'Segoe UI', Tahoma, sans-serif;
            background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }}
        .container {{
            background: #ffffff;
            padding: 2rem;
            border-radius: 12px;
            box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
            text-align: center;
            max-width: 400px;
            width: 90%;
        }}
        h1 {{
            margin-bottom: 0.5rem;
            color: #333333;
        }}
        p {{
            margin-top: 0;
            color: #666666;
        }}
        .btn-refresh {{
            margin-top: 1rem;
            padding: 0.6rem 1.2rem;
            border: none;
            border-radius: 6px;
            background-color: #007acc;
            color: #ffffff;
            font-size: 1rem;
            cursor: pointer;
            transition: background-color 0.3s;
        }}
        .btn-refresh:hover {{
            background-color: #005fa3;
        }}
    </style>
</head>
<body>
    <div class="container">
        <h1>CGI exécuté avec succès 🎉</h1>
        <p>Date et heure actuelles :<br><strong>{date_actuelle}</strong></p>
        <form method="post">
            <button type="submit" class="btn-refresh">Actualiser</button>
        </form>
    </div>
</body>
</html>
"""

print(html)