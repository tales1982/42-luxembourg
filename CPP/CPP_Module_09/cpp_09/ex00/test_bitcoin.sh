#!/bin/bash

# Cores ANSI
RESET="\033[0m"
BOLD="\033[1m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
CYAN="\033[36m"

echo -e "${BLUE}${BOLD}Running BitcoinExchange Tests...${RESET}"

EXECUTABLE="./btc"  # ou ./BitcoinExchange se for o nome usado

# Verifica se o executável existe
if [ ! -f "$EXECUTABLE" ]; then
  echo -e "${RED}${BOLD}Erro: executável '$EXECUTABLE' não encontrado.${RESET}"
  echo "Execute 'make' e tente novamente."
  exit 1
fi

# Executa o programa
output=$($EXECUTABLE input.txt 2>&1)

# Remove ANSI internas (caso já existam do próprio programa)
clean_output=$(echo "$output" | sed -r 's/\x1B\[[0-9;]*[JKmsu]//g')

echo -e "\n${CYAN}${BOLD}--- Saída do Programa ---${RESET}"

# Destacar dinamicamente cada linha
while IFS= read -r line; do
  if [[ "$line" == Error:* || "$line" == *"Error:"* ]]; then
    echo -e "${RED}${line}${RESET}"
  elif [[ "$line" == *"=>"* ]]; then
    echo -e "${GREEN}${line}${RESET}"
  else
    echo "$line"
  fi
done <<< "$clean_output"

echo -e "\n${BLUE}${BOLD}Teste finalizado.${RESET}"
