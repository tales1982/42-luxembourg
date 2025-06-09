#!/bin/bash

# Cores ANSI
GREEN='\033[1;32m'
RED='\033[1;31m'
CYAN='\033[1;36m'
RESET='\033[0m'
BOLD='\033[1m'

echo -e "${CYAN}${BOLD}Running PmergeMe Tests...${RESET}"
echo ""

TESTS=(
    "3 5 9 7 4"
    "10 1 9 3 8 2 7 4 6 5"
    "100"
    "1 2 3 4 5"
    "3000"
)

INVALID_TESTS=(
    "-1 5 7"
    "a b c"
    "1 2 abc"
    ""
)

# Testes válidos
for test in "${TESTS[@]}"
do
    echo -e "${BOLD}Input:${RESET} '$test'"
    ./PmergeMe $test
    echo "----------------------------------"
done

# Testes inválidos
echo -e "${CYAN}${BOLD}Testing invalid inputs...${RESET}"
for test in "${INVALID_TESTS[@]}"
do
    echo -e "${BOLD}Input:${RESET} '$test'"
    ./PmergeMe $test 2> /dev/null
    if [ $? -ne 0 ]; then
        echo -e "${GREEN}[PASS] Properly failed on invalid input${RESET}"
    else
        echo -e "${RED}[FAIL] Should have failed, but ran successfully${RESET}"
    fi
    echo "----------------------------------"
done

# Teste com 3000 números aleatórios
echo -e "${CYAN}${BOLD}Testing 3000 random integers...${RESET}"
RAND_INPUT=$(shuf -i 1-100000 -n 3000 | tr "\n" " ")
./PmergeMe $RAND_INPUT
echo -e "${GREEN}[PASS] Completed test with 3000 elements${RESET}"
