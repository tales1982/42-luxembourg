#!/bin/bash

echo "=== VERIFICAÇÃO CONFORMIDADE 42 ==="
echo
echo "Assignment: bsq"
echo "Files: main.c"
echo "Compilation: cc -std=c89 -Wall -Wextra -Werror"
echo

echo "1. Verificando arquivos..."
if [ -f main.c ]; then
    echo "   ✓ Arquivo main.c presente"
else
    echo "   ✗ Falta o arquivo main.c"
    exit 1
fi

echo
echo "2. Compilando..."
if cc -std=c89 -Wall -Wextra -Werror main.c -o programa 2>&1 | grep -q "error:"; then
    echo "   ✗ Erro de compilação"
    exit 1
else
    echo "   ✓ Compilação sem erros, warnings ou flags"
fi

echo
echo "3. Testando funcionalidades básicas..."

# Test com stdin
result=$(echo -e "3.ox\n...\n.o.\n..." | ./programa)
if echo "$result" | grep -q "x"; then
    echo "   ✓ Leitura de stdin funciona"
else
    echo "   ✗ Problema com stdin"
    exit 1
fi

# Test com arquivo
if ./programa test1.stdin >/dev/null 2>&1; then
    echo "   ✓ Leitura de arquivo funciona"
else
    echo "   ✗ Problema com arquivo"
    exit 1
fi

# Test de erro - mapa inválido
result=$(./programa < test_error1.stdin 2>&1)
if echo "$result" | grep -q "Error: invalid map"; then
    echo "   ✓ Detecção de mapa inválido funciona"
else
    echo "   ✗ Erro não detectado corretamente"
    exit 1
fi

# Test de erro - arquivo inexistente
result=$(./programa arquivo_nao_existe 2>&1)
if echo "$result" | grep -q "Error:"; then
    echo "   ✓ Detecção de arquivo inexistente funciona"
else
    echo "   ✗ Erro de arquivo não detectado"
    exit 1
fi

echo
echo "4. Testando test6 (caso que falhou inicialmente)..."
result=$(./programa < test6.stdin)
expected="2   2  22 
2 22 2 222
2 2   222 
33  22    
33  2  22 
222 2    2
 2    222 
22 22    2
22    2  2
   2 2 22 "

if [ "$result" = "$expected" ]; then
    echo "   ✓ Test6 passou!"
else
    echo "   ✗ Test6 falhou"
    echo "Esperado:"
    echo "$expected"
    echo "Obtido:"
    echo "$result"
    exit 1
fi

echo
echo "=== TODOS OS TESTES PASSARAM! ==="
echo "Grade: 100%"
echo
