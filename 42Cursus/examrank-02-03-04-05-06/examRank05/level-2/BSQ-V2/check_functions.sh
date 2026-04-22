#!/bin/bash

echo "=== VERIFICAÇÃO DE FUNÇÕES USADAS ==="
echo
echo "Funções PERMITIDAS:"
echo "  malloc, calloc, realloc, free"
echo "  fopen, fclose"
echo "  getline, fscanf, fputs, fprintf, fputc"
echo "  stdout, stdin"
echo

echo "Procurando funções NÃO permitidas em *.c:"
echo

# Funções proibidas comuns
prohibited=(
    "strlen"
    "strcpy"
    "strncpy"
    "strcat"
    "strcmp"
    "strncmp"
    "printf"
    "scanf"
    "puts"
    "gets"
    "fgets"
    "read"
    "write"
    "open"
    "close"
)

found_issues=0

for func in "${prohibited[@]}"; do
    result=$(grep -n "\b$func\(" main.c 2>/dev/null | grep -v "ft_$func")
    if [ ! -z "$result" ]; then
        echo "⚠ Encontrado: $func"
        echo "$result"
        found_issues=1
    fi
done

if [ $found_issues -eq 0 ]; then
    echo "✓ Nenhuma função proibida encontrada!"
else
    echo
    echo "✗ Funções proibidas detectadas!"
fi
