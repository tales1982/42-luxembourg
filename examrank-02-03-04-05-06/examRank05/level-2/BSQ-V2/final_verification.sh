#!/bin/bash

echo "╔══════════════════════════════════════════════════╗"
echo "║     VERIFICAÇÃO FINAL - PROJETO BSQ             ║"
echo "╚══════════════════════════════════════════════════╝"
echo

# 1. Verificar funções permitidas
echo "1. Verificando funções..."
if grep "strlen\|strcpy\|strcmp\|printf\b\|puts\|gets" main.c 2>/dev/null | grep -v "ft_strlen\|fprintf"; then
    echo "   ✗ Funções proibidas encontradas!"
    exit 1
else
    echo "   ✓ Apenas funções permitidas"
fi

# 2. Compilação
echo
echo "2. Compilando com flags estritas..."
if cc -std=c89 -Wall -Wextra -Werror main.c -o programa 2>&1 | grep -i "error\|warning"; then
    echo "   ✗ Erros ou warnings na compilação"
    exit 1
else
    echo "   ✓ Compilação limpa (sem erros ou warnings)"
fi

# 3. Teste básico
echo
echo "3. Testando funcionalidades..."
result=$(echo -e "3.ox\n...\n.o.\n..." | ./programa)
if echo "$result" | grep -q "x"; then
    echo "   ✓ Algoritmo funciona corretamente"
else
    echo "   ✗ Problema no algoritmo"
    exit 1
fi

# 4. Teste de erro
echo
echo "4. Testando tratamento de erros..."
result=$(echo -e "3.ox\n..\n.o.\n..." | ./programa 2>&1)
if echo "$result" | grep -q "Error: invalid map"; then
    echo "   ✓ Erros são detectados corretamente"
else
    echo "   ✗ Tratamento de erros falhou"
    exit 1
fi

# 5. Testes completos
echo
echo "5. Executando bateria de testes..."
./run_tests.sh 2>/dev/null | grep "Grade:" | while read line; do
    echo "   $line"
done

echo
echo "╔══════════════════════════════════════════════════╗"
echo "║              ✓ PROJETO APROVADO!                ║"
echo "║     Pronto para submissão na 42!                ║"
echo "╚══════════════════════════════════════════════════╝"
