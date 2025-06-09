# C++ - Module 07: C++ Templates

## 📌 Introduction

C++ é uma linguagem de propósito geral criada como uma extensão de C, com suporte a programação orientada a objetos. Este módulo introduz os templates em C++.

Objetivos:
- Introduzir templates de funções e classes.
- Utilizar C++98.

---

## 📋 General Rules

### 🛠 Compilação
- Compile com: `c++ -Wall -Wextra -Werror`
- Compatível com `-std=c++98`

### 🧱 Formatação e Nomeação
- Diretórios: `ex00`, `ex01`, ...
- Classes: UpperCamelCase
- Arquivos de classes: `ClassName.hpp`, `ClassName.cpp`

### ❌ Proibições
- Sem `printf`, `malloc`, `free`
- Sem `using namespace` e `friend`
- STL só é permitida nos módulos 08 e 09
- Nada de `<algorithm>` ainda

---

## 🧪 Exercise 00: Start with a few functions

### 🎯 Objetivo
Implementar templates de função:
- `swap`: Troca dois valores
- `min`: Retorna o menor dos dois valores
- `max`: Retorna o maior dos dois valores

### 📁 Turn-in
- Diretório: `ex00/`
- Arquivos: `Makefile`, `main.cpp`, `whatever.hpp`

### 📝 Exemplo de uso:
```cpp
int a = 2, b = 3;
::swap(a, b);
std::cout << ::min(a, b);
std::cout << ::max(a, b);

std::string c = "chaine1", d = "chaine2";
::swap(c, d);
std::cout << ::min(c, d);
std::cout << ::max(c, d);
```

---

## 🧪 Exercise 01: Iter

### 🎯 Objetivo
Implementar o template de função `iter` com 3 parâmetros:
1. Endereço do array
2. Tamanho do array
3. Função a ser aplicada em cada elemento

### 📁 Turn-in
- Diretório: `ex01/`
- Arquivos: `Makefile`, `main.cpp`, `iter.hpp`

---

## 🧪 Exercise 02: Array

### 🎯 Objetivo
Implementar uma classe template `Array<T>` que:
- Construtor sem parâmetros: array vazio
- Construtor com `unsigned int n`: array com `n` elementos default
- Suporte a cópia e atribuição (deep copy)
- Acesso via `[]` com verificação de limites (joga `std::exception`)
- Método `size()` que retorna número de elementos

### 📁 Turn-in
- Diretório: `ex02/`
- Arquivos: `Makefile`, `main.cpp`, `Array.hpp`, opcional: `Array.tpp`

---

## 📤 Submission

- Enviar tudo via repositório Git.
- Os avaliadores verão apenas os arquivos entregues.
- Verifique nomes de arquivos e pastas.