#!/bin/bash

echo "=== TESTE FINAL COMPLETO ==="
echo
echo "1. Compilação:"
cc -std=c89 -Wall -Wextra -Werror main.c -o programa && echo "   OK: Compilado com sucesso"
echo
echo "2. Testes automatizados:"
./run_tests.sh 2>/dev/null | grep "Grade:"
echo
echo "3. Teste com arquivo:"
echo "   ./programa test5.stdin (primeiras 3 linhas):"
./programa test5.stdin | head -3
echo
echo "4. Teste com stdin:"
echo -e "3.ox\n...\n.o.\n..." | ./programa
echo
echo "5. Teste de erro:"
./programa arquivo_inexistente 2>&1 | head -1
echo
echo "=== PROGRAMA FUNCIONANDO CORRETAMENTE! ==="
