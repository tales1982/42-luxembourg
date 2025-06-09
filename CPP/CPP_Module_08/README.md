
# 📘 C++ Module 08 - Containers, Templates, Iterators & Algorithms

## 🧩 Introdução
- C++ é uma linguagem multi-paradigma (procedural, OOP, genérica).
- Este módulo foca na introdução à Programação Orientada a Objetos (OOP).
- Utilizaremos o padrão C++98.
- Incentivo ao uso da STL neste módulo (permitido a partir dos módulos 08 e 09).

---

## 📋 Consignes Gerais

- **Compilação**: `c++ -Wall -Wextra -Werror -std=c++98`
- **Formato & Nomenclatura**:
  - Diretórios: `ex00`, `ex01`, etc.
  - Nomes das classes: UpperCamelCase
  - Arquivos de classe: `Classe.hpp`, `Classe.cpp`, etc.
- **Restrições**:
  - Sem `*printf()`, `*alloc()`, `free()`
  - Sem `using namespace`, nem `friend`
  - STL só é permitida nos módulos 08 e 09
- **Boas práticas**:
  - Evitar memory leaks
  - Implementar forma canônica de Coplien
  - Usar include guards nos headers

---

## 🔧 Consignes Específicas do Módulo

- **Use Containers da STL**: `vector`, `list`, `map`, etc.
- **Use Algoritmos da STL**: `<algorithm>`, `find()`, etc.
- **Use Templates**
- **Evite soluções alternativas que não envolvam STL**

---

## 📂 Exercício 00 - `EasyFind`

- **Objetivo**: Escreva uma função template `easyfind` que encontra a primeira ocorrência de um número inteiro num container do tipo `T`.
- **Parâmetros**: `T container`, `int toFind`
- **Se não encontrado**: Lançar exceção ou retornar erro
- **Restrições**: 
  - Sem containers associativos
- **Arquivos esperados**: `Makefile`, `main.cpp`, `easyfind.hpp`

---

## 📂 Exercício 01 - `Span`

- **Objetivo**: Criar uma classe `Span` que armazene `N` inteiros.
- **Funções principais**:
  - `addNumber(int)`: adiciona número, lança exceção se cheio.
  - `shortestSpan()`: menor distância entre dois valores
  - `longestSpan()`: maior distância
  - `addNumber(iterator begin, iterator end)`: adiciona vários
- **Testes esperados**: incluir pelo menos 10.000 números
- **Arquivos esperados**: `Makefile`, `main.cpp`, `Span.hpp`, `Span.cpp`

---

## 📂 Exercício 02 - `MutantStack`

- **Objetivo**: Tornar a `std::stack` iterável criando `MutantStack`.
- **Funcionalidade**: herda ou utiliza internamente `std::stack`, adicionando iteração.
- **Requisitos**:
  - Mesmo comportamento de `stack`
  - Deve permitir begin() e end() com iteração sobre os dados
- **Arquivos esperados**: `Makefile`, `main.cpp`, `MutantStack.hpp`

---

## ✅ Submissão

- **Git**: Enviar via repositório Git
- **Verificar**: Estrutura de pastas e nomes dos arquivos
- **Avaliação**: Baseada no código presente no Git e testes próprios
