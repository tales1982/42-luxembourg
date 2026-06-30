# Arachnida — Manual de Uso

Dois programas: **spider** (baixa imagens de sites) e **scorpion** (lê metadados de imagens).

---

## Instalação de dependências

```bash
pip install requests beautifulsoup4 pillow
```

---

## spider.py — Baixar imagens de um site

### Uso básico

```bash
python3 spider.py <URL>
```

### Opções

| Flag | Descrição | Padrão |
|------|-----------|--------|
| `-r` | Modo recursivo (segue links do mesmo domínio) | desativado |
| `-l <N>` | Profundidade máxima de recursão | 5 |
| `-p <pasta>` | Pasta onde salvar as imagens | `./data/` |

### Exemplos

```bash
# Baixar imagens apenas da página inicial
python3 spider.py https://exemplo.com

# Baixar recursivamente até profundidade 3
python3 spider.py -r -l 3 https://exemplo.com

# Salvar em pasta personalizada
python3 spider.py -r -l 2 -p ./minhas_imagens/ https://exemplo.com
```

### Formatos baixados
`.jpg` `.jpeg` `.png` `.gif` `.bmp`

---

## scorpion.py — Ler metadados de imagens

### Uso básico

```bash
python3 scorpion.py <arquivo1> [arquivo2 ...]
```

### Exemplos

```bash
# Ver metadados de uma imagem
python3 scorpion.py foto.jpg

# Ver metadados de várias imagens
python3 scorpion.py foto.jpg imagem.png banner.gif

# Ver metadados de tudo que foi baixado pelo spider
python3 scorpion.py data/*.jpg
```

### O que é exibido
- Tamanho do arquivo
- Data de criação e modificação
- Formato, modo e dimensões
- Dados EXIF (câmera, GPS, etc. se disponível)
- Metadados extras do formato (PNG, GIF, etc.)
