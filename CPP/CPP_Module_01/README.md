# C++ - Module 01

> **Tópicos:** Alocação de memória, ponteiros para membros, referências, instrução `switch`.

---

## 📌 Introdução

- C++ é uma linguagem derivada de C, voltada para programação orientada a objetos.
- O objetivo dos módulos é introduzir os conceitos fundamentais de OOP.
- Código deve seguir o padrão C++98.

---

## 📜 Regras Gerais

### Compilação

- Compilar com: `c++ -Wall -Wextra -Werror -std=c++98`

### Convenções de nomenclatura

- Pastas: `ex00`, `ex01`, etc.
- Classes em UpperCamelCase.
- Arquivos `.hpp`/`.cpp` com o mesmo nome da classe.

### Estilo de código

- Não há uma norminette, mas o código deve ser limpo e compreensível.

### Permitido / Proibido

- Permitido: Tudo da STL **apenas no módulo 08 e 09**.
- Proibido:
  - C++11 e além
  - Bibliotecas externas
  - `*printf()`, `malloc()`, `free()`
  - `using namespace`, `friend`
- Evite memory leaks.
- Funções não devem ser implementadas em headers (exceto templates).
- Headers devem ser independentes, com guards de inclusão.

---

## 🧠 Exercício 00: BraiiiiiiinnnzzzZ

- Diretório: `ex00/`
- Arquivos:
  - `Zombie.hpp`, `Zombie.cpp`
  - `newZombie.cpp`
  - `randomChump.cpp`
  - `main.cpp`, `Makefile`
- Criar a classe `Zombie` com:
  - Atributo `name`
  - Função `announce()` → imprime: `Foo: BraiiiiiiinnnzzzZ...`
- Funções adicionais:
  - `Zombie* newZombie(std::string name)`
  - `void randomChump(std::string name)`
- Objetivo: entender diferença entre heap e stack

---

## 🧟‍♂️ Exercício 01: Moar brainz!

- Diretório: `ex01/`
- Função:
  - `Zombie* zombieHorde(int N, std::string name)`
  - Cria N zumbis com o mesmo nome usando alocação única
- Testar com `announce()`
- Liberar a memória e verificar leaks

---

## 🧠 Exercício 02: HI THIS IS BRAIN

- Diretório: `ex02/`
- Declarar:
  - string → `"HI THIS IS BRAIN"`
  - `stringPTR` → ponteiro
  - `stringREF` → referência
- Exibir:
  - Endereço da string, `stringPTR` e `stringREF`
  - Valor da string, `*stringPTR`, `stringREF`

---

## 🛡️ Exercício 03: Unnecessary violence

- Diretório: `ex03/`
- Classes:
  - `Weapon` com `type`, `getType()` e `setType()`
  - `HumanA` (com `Weapon` no construtor)
  - `HumanB` (usa `setWeapon`)
- Função `attack()` imprime: `<name> attacks with their <weapon type>`
- Testar com mudanças de tipo da arma

---

## ✍️ Exercício 04: Sed is for losers

- Diretório: `ex04/`
- Programa recebe: `filename s1 s2`
- Cria `<filename>.replace` substituindo `s1` por `s2`
- Proibido:
  - `std::string::replace`
  - funções C de manipulação de arquivos
- Tratar erros de entrada

---

## 🤖 Exercício 05: Harl 2.0

- Diretório: `ex05/`
- Classe `Harl` com funções privadas:
  - `debug()`, `info()`, `warning()`, `error()`
- Função pública:
  - `void complain(std::string level)`
  - Deve usar ponteiros para funções membro (sem if/else)

---

## 🔇 Exercício 06: Harl filter

- Diretório: `ex06/`
- Programa: `./harlFilter <LEVEL>`
- Exibe mensagens a partir do nível especificado (inclusive)
- Exemplo:
  - `"WARNING"` → mostra `WARNING` e `ERROR`
  - Qualquer outro input → "Probably complaining about insignificant problems"
- Deve usar `switch`

---

## 📥 Entrega e Avaliação

- Submeter no repositório Git.
- Somente o conteúdo do repositório será avaliado.
