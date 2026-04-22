# C++ - Module 03: Inheritance

## 🧠 Objetivo

Introdução à Programação Orientada a Objetos (OOP) com C++, focando no uso de herança e construção/destruição de objetos em cadeia.

---

## ⚙️ Regras Gerais

- **Compilação**: Use `c++` com as flags `-Wall -Wextra -Werror` e `-std=c++98`
- **Nomeação**:
  - Diretórios: `ex00`, `ex01`, etc.
  - Classes: UpperCamelCase
  - Arquivos: Nome da classe (`Classe.hpp`, `Classe.cpp`)
- **Proibido**:
  - `printf`, `malloc`, `free`
  - `using namespace` e `friend`
  - STL (exceto nos módulos 08 e 09)
- **Design**:
  - Usar Orthodox Canonical Form (OCF)
  - Sem vazamentos de memória
  - Headers devem ser independentes e usar include guards

---

## 📂 Exercício 00: Aaaaand... OPEN!

### 🎯 Objetivo

Criar uma classe `ClapTrap`.

### 🛠️ Arquivos

- `main.cpp`
- `ClapTrap.hpp`
- `ClapTrap.cpp`
- `Makefile`

### 🧱 Atributos Privados

- `name` (passado no construtor)
- `hitPoints` = 10
- `energyPoints` = 10
- `attackDamage` = 0

### 🔧 Métodos Públicos

- `attack(const std::string& target)`
- `takeDamage(unsigned int amount)`
- `beRepaired(unsigned int amount)`

### 📢 Requisitos

- Imprimir mensagens nas funções (inclusive nos construtores e destrutores)
- Testes próprios no `main.cpp`

---

## 📂 Exercício 01: Serena, my love!

### 🎯 Objetivo

Criar uma classe derivada `ScavTrap` de `ClapTrap`.

### 🛠️ Arquivos

- Adicionar: `ScavTrap.hpp`, `ScavTrap.cpp`

### 🔧 Características

- Construtores, destrutor e `attack()` com mensagens diferentes
- Atributos atualizados:
  - `hitPoints` = 100
  - `energyPoints` = 50
  - `attackDamage` = 20
- Novo método: `void guardGate()`

---

## 📂 Exercício 02: Repetitive work

### 🎯 Objetivo

Criar outra classe derivada `FragTrap` de `ClapTrap`.

### 🛠️ Arquivos

- Adicionar: `FragTrap.hpp`, `FragTrap.cpp`

### 🔧 Características

- Construtores, destrutor e `attack()` com mensagens diferentes
- Atributos atualizados:
  - `hitPoints` = 100
  - `energyPoints` = 100
  - `attackDamage` = 30
- Novo método: `void highFivesGuys()`

---

## 📂 Exercício 03: Now it’s weird!

### 🎯 Objetivo

Criar a classe `DiamondTrap` que herda de `FragTrap` e `ScavTrap`.

### 🛠️ Arquivos

- Adicionar: `DiamondTrap.hpp`, `DiamondTrap.cpp`

### 🔧 Requisitos Específicos

- Atributo `name` com o mesmo nome do atributo de `ClapTrap`
- Atributos definidos:
  - `hitPoints`: de `FragTrap`
  - `energyPoints`: de `ScavTrap`
  - `attackDamage`: de `FragTrap`
  - `attack()`: de `ScavTrap`
- Novo método: `void whoAmI()`

---

## ✅ Entrega e Avaliação

- Submeter no repositório Git da 42
- Verificar nome correto de arquivos e diretórios
- Siga os requisitos obrigatórios e escreva código limpo

---

> 💬 **Dica**: Você pode passar esse módulo sem fazer o exercício 03, mas é altamente recomendado tentar.
>
