# Module C++ 09 - STL

## 📌 Introdução

- O C++ é uma extensão do C com suporte à programação orientada a objetos (POO).
- Este módulo é parte da introdução à POO.
- O código deve seguir a norma **C++98**.

---

## ⚙️ Consignes Gerais

### 📦 Compilação

- Usar: `c++ -Wall -Wextra -Werror -std=c++98`

### 🧾 Convenções

- Nome dos diretórios: `ex00`, `ex01`, etc.
- Nome de arquivos, classes e funções conforme especificado no exercício.
- Classes em `UpperCamelCase`.
- Arquivos devem conter `.hpp`, `.cpp`.
- Evitar memória vazada (`new` sem `delete`).
- Implementar a forma canônica (Coplien).

### 🚫 Proibições

- Proibido: `*printf()`, `*alloc()`, `free()`
- Proibido usar `friend` e `using namespace`
- C++11 e Boost são proibidos
- STL só permitida nos módulos 08 e 09

---

## 📌 Regras Específicas do Módulo

- É obrigatório usar **containers da STL**
- Um container por exercício, exceto o ex02 (que exige dois)
- Cada exercício deve ter um `Makefile` com as regras: `$(NAME)`, `all`, `clean`, `fclean`, `re`
- Makefile não deve fazer relink

---

## 📘 Exercício 00: Bitcoin Exchange

### 🎯 Objetivo

- Criar o programa `btc` que calcula o valor do bitcoin em uma determinada data.

### 📁 Arquivos a entregar

- `Makefile`, `main.cpp`, `BitcoinExchange.cpp`, `BitcoinExchange.hpp`

### 📌 Regras

- Entrada: arquivo com linhas no formato `YYYY-MM-DD | value`
- Validar: data, valor (float/int, 0-1000)
- Usar ao menos **um container**
- Tratar erros com mensagens adequadas

### 💡 Observações

- Se a data não existir na base, usar a **data anterior mais próxima**
- Exibir resultado no formato:  
  `YYYY-MM-DD => value = result`

---

## 📘 Exercício 01: Reverse Polish Notation (RPN)

### 🎯 Objetivo

- Criar o programa `RPN` que resolve expressões matemáticas em notação polonesa reversa.

### 📁 Arquivos a entregar

- `Makefile`, `main.cpp`, `RPN.cpp`, `RPN.hpp`

### 📌 Regras

- Entrada: string contendo expressão no formato `"8 9 * 9 - ..."`
- Operações válidas: `+ - * /`
- Números < 10
- Mostrar apenas o resultado final
- Usar ao menos **um container**
- Tratar erros (por exemplo: parênteses, strings inválidas)

---

## 📘 Exercício 02: PmergeMe

### 🎯 Objetivo

- Criar o programa `PmergeMe` que ordena uma sequência de inteiros positivos.

### 📁 Arquivos a entregar

- `Makefile`, `main.cpp`, `PmergeMe.cpp`, `PmergeMe.hpp`

### 📌 Regras

- Utilizar o algoritmo **Ford-Johnson** (merge-insert sort)
- Usar **dois containers diferentes**
- Capaz de ordenar **3000 números**
- Mostrar:
  - Sequência original
  - Sequência ordenada
  - Tempo de execução para cada container

### 📌 Exemplo de saída

```plaintext
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process with std::vector : 0.00031 us
Time to process with std::deque  : 0.00014 us
```

---

## 🧾 Rendu e Évaluation

- Entregar os arquivos obrigatórios no repositório Git
- Nada fora do repositório será avaliado
- Conferir os nomes de arquivos e diretórios