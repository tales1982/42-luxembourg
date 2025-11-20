#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}🔍 Running COMPREHENSIVE TESTING for bsq${NC}"
echo "=========================================="
echo ""

# Paths
# Pasta um nível acima, onde estão bsq.c, (opcionalmente bsq.h e main.c)
RANDOM_FOLDER=".."

# Check if user solution exists
if [ ! -d "$RANDOM_FOLDER" ]; then
    echo -e "${RED}❌ User rendu folder not found!${NC}"
    exit 1
fi

# Procura arquivos .c (obrigatório) e .h (opcional)
USER_C_FILES=$(find "$RANDOM_FOLDER" -maxdepth 1 -name "*.c")
USER_H_FILES=$(find "$RANDOM_FOLDER" -maxdepth 1 -name "*.h")

if [ -z "$USER_C_FILES" ]; then
    echo -e "${RED}❌ User solution not found: No .c files${NC}"
    exit 1
fi

# Se existir main.c, vamos usá-lo como main de teste
if [ -f "$RANDOM_FOLDER/main.c" ]; then
    echo -e "${BLUE}ℹ️  Found main.c in parent folder, using it as test main.${NC}"
    USE_MAIN=1
    cp "$RANDOM_FOLDER/main.c" temp_main.c
else
    echo -e "${YELLOW}⚠️  No main.c found in parent folder.${NC}"
    echo -e "${YELLOW}    The tester expects a separate main.c (test harness).${NC}"
    echo -e "${YELLOW}    For now, will try to compile bsq.c alone as your full program.${NC}"
    USE_MAIN=0
fi

# Copia arquivos .c e .h do diretório pai para o diretório do tester
cp "$RANDOM_FOLDER"/*.c . 2>/dev/null
cp "$RANDOM_FOLDER"/*.h . 2>/dev/null

# Compile reference solution
echo -e "${BLUE}📦 Compiling reference solution...${NC}"
if [ "$USE_MAIN" -eq 1 ]; then
    # main.c + bsq.c
    gcc -Wall -Wextra -Werror -std=c99 -o ref_bsq temp_main.c bsq.c
else
    # Sem main.c separado: usa só bsq.c (não é bem "referência", mas mantém estrutura)
    gcc -Wall -Wextra -Werror -std=c99 -o ref_bsq bsq.c
fi

if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Reference compilation failed!${NC}"
    exit 1
fi
echo -e "${GREEN}✅ Reference compilation successful!${NC}"
echo ""

# Compile user solution
echo -e "${BLUE}📦 Compiling user solution...${NC}"
if [ "$USE_MAIN" -eq 1 ]; then
    gcc -Wall -Wextra -Werror -std=c99 -o user_bsq temp_main.c bsq.c
else
    gcc -Wall -Wextra -Werror -std=c99 -o user_bsq bsq.c
fi

if [ $? -ne 0 ]; then
    echo -e "${RED}❌ User compilation failed!${NC}"
    exit 1
fi
echo -e "${GREEN}✅ User compilation successful!${NC}"
echo ""

# Create test maps
cat > test1.map << 'EOF'
9 . o x
...........................
....o......................
............o..............
...........................
....o......................
...............o...........
...........................
......o..............o.....
..o.......o................
EOF

cat > test2.map << 'EOF'
5 . # O
.....
.....
.....
.....
.....
EOF

cat > test3.map << 'EOF'
3 a b c
aaa
aaa
aaa
EOF

# Function to run tests
run_test() {
    local num=$1
    local file=$2
    echo -e "${BLUE}🚀 Running Test $num...${NC}"
    ./ref_bsq "$file" > "ref_output${num}.txt" 2>&1
    ./user_bsq "$file" > "user_output${num}.txt" 2>&1

    if diff -q "ref_output${num}.txt" "user_output${num}.txt" > /dev/null; then
        echo -e "${GREEN}✅ Test $num output matches reference!${NC}"
        return 0
    else
        echo -e "${RED}❌ Test $num output does NOT match reference!${NC}"
        echo -e "${YELLOW}--- Diff ---${NC}"
        diff "ref_output${num}.txt" "user_output${num}.txt"
        return 1
    fi
}

# Run all tests
tests_passed=true
for i in 1 2 3; do
    run_test "$i" "test${i}.map" || tests_passed=false
done

# Standard input test
echo -e "${BLUE}🚀 Running Test 4 (stdin)...${NC}"
./ref_bsq < test1.map > ref_output4.txt 2>&1
./user_bsq < test1.map > user_output4.txt 2>&1
if diff -q ref_output4.txt user_output4.txt > /dev/null; then
    echo -e "${GREEN}✅ Test 4 output matches reference!${NC}"
else
    echo -e "${RED}❌ Test 4 output does NOT match reference!${NC}"
    diff ref_output4.txt user_output4.txt
    tests_passed=false
fi

# Valgrind check
echo -e "${BLUE}🚀 Running Valgrind memory check...${NC}"
valgrind_output=$(valgrind --leak-check=full --show-leak-kinds=all -s ./user_bsq test1.map 2>&1)
valgrind_exit=$?

echo "$valgrind_output"

if echo "$valgrind_output" | grep -q "definitely lost:" && ! echo "$valgrind_output" | grep -q "definitely lost: 0 bytes"; then
    echo -e "${RED}❌ Memory leaks detected!${NC}"
    tests_passed=false
else
    echo -e "${GREEN}✅ No memory leaks detected.${NC}"
fi

# Summary
echo "======================================="
if [ "$tests_passed" = true ]; then
    echo -e "${GREEN}✅ PASSED!${NC}"
else
    echo -e "${RED}❌ SOME TESTS FAILED!${NC}"
fi
echo "======================================="

# Cleanup
rm -f temp_main.c user_bsq ref_bsq

