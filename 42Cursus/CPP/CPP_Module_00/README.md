# 📘 C++ Module 00 - Resumo e Conteúdo de Estudo

## 🧭 Introdução

- O módulo visa introduzir a Programação Orientada a Objetos (POO) usando **C++98**.
- C++ é uma extensão do C com suporte à orientação a objetos, genéricos e mais.
- O foco será aprender a construir **classes**, **objetos**, **encapsulamento** e outras bases da OOP.

---

## 📋 Consignes Générales (Regras Gerais)

### ✅ Compilação

- Use:
  ```sh
  c++ -Wall -Wextra -Werror -std=c++98
  ```

### ✅ Nomeação de Arquivos

- Dossiês: `ex00`, `ex01`, etc.
- Arquivos de classe: `NomClasse.hpp`, `NomClasse.cpp`, etc.
- Classes: UpperCamelCase
- Fim de mensagem: com `\n`

### ❌ Proibições

- **STL containers** (vector, list, map...) e algoritmos: proibidos até o módulo 08.
- `printf`, `malloc`, `calloc`, `realloc`, `free`: proibidos
- `using namespace` e `friend`: proibidos
- C++ moderno (C++11+) e Boost: proibidos

### ⚠️ Design

- Sem memory leaks
- Canonical form obrigatória a partir do módulo 02
- Headers devem ter include guards
- Funções não-template **não** devem estar implementadas no `.hpp`

---

## 📦 Exercícios

### 📣 Ex00 - Mégaphone

**Objetivo:**
Criar um programa que converte todos os argumentos recebidos para MAIÚSCULAS.

**Arquivos:**

- `megaphone.cpp`
- `Makefile`

**Comportamento:**

```sh
./megaphone "hello world"
# => HELLO WORLD

./megaphone
# => * LOUD AND UNBEARABLE FEEDBACK NOISE *
```

---

### 📇 Ex01 - My Awesome PhoneBook

**Objetivo:**
Criar uma agenda com no máximo 8 contatos (sem alocação dinâmica).

**Arquivos:**

- `Makefile`
- `Contact.hpp/.cpp`
- `PhoneBook.hpp/.cpp`
- `main.cpp`

**Classes:**

- `PhoneBook` (array de `Contact`, máx. 8)
- `Contact` (first name, last name, nickname, phone number, darkest secret)

**Comandos:**

- `ADD`: solicitar dados do contato e adicioná-lo
- `SEARCH`: mostrar todos os contatos formatados e permitir consultar um pelo índice
- `EXIT`: finaliza o programa

**Formatos:**

- Tabela com 10 caracteres por coluna, alinhamento à direita
- Truncamento com `.` se ultrapassar o limite

---

### 🏦 Ex02 - L’emploi de vos rêves

**Objetivo:**
Recriar `Account.cpp` usando o cabeçalho `Account.hpp` e um `log` (testes fornecidos).

**Arquivos:**

- `Makefile`
- `Account.cpp` (a ser implementado)
- `Account.hpp` (fornecido)
- `tests.cpp` (fornecido)

**O que estudar:**

- Construtores e destrutores
- Atributos estáticos
- Métodos estáticos e de instância
- Manipulação de data/hora (simples)
- Ordenação dos outputs
- Sem memory leaks
- Atenção à ordem de destrutores (pode variar por sistema)

---

### ✅ Entrega & Avaliação

- Todos os arquivos devem estar no **repositório Git**
- Apenas o que estiver no repo será avaliado
- Verifique nomes de arquivos, pastas e siga as convenções
