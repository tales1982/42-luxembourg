
# 🧙 Exercícios Preparatórios para o Exame Rank 05 - 42

Este conjunto de exercícios foi criado para ajudá-lo a entender e praticar os conceitos necessários para o exame Rank 05 da 42. Os exercícios foram inspirados no conteúdo oficial, mas adaptados para serem mais didáticos e progressivos, com foco no aprendizado dos fundamentos antes da implementação completa.

---

## 📦 Módulo 00 - Warlock Básico

### 🎯 Objetivo

Aprender a criar uma classe simples com atributos privados, construtor e métodos públicos. É o primeiro passo para entender a base da programação orientada a objetos.

### 🧪 Exercício: WarlockIntro

Crie uma classe chamada `Warlock` com os seguintes requisitos:

- Atributos privados:

  - `name` (string): nome do warlock
  - `title` (string): título do warlock
- Métodos públicos:

  - Construtor que recebe o nome e o título
  - `getName()`: retorna o nome
  - `getTitle()`: retorna o título
  - `introduce()`: imprime `"name: I am name, title!"`

---

## 📦 Módulo 01 - Magia e Alvos

### 🎯 Objetivo

Introdução a herança e polimorfismo em C++. Criar feitiços e alvos que podem ser manipulados por um Warlock.

### 🧪 Exercício: MagiaSimples

1. Crie uma classe abstrata `ASpell` com:

   - Atributos: `name`, `effects`
   - Métodos: `getName()`, `getEffects()`, `clone()`
2. Crie uma classe abstrata `ATarget` com:

   - Atributo: `type`
   - Método: `getType()`, `clone()`
3. Crie uma classe derivada `Fireball` de `ASpell`:

   - Construtor define `name = "Fireball"` e `effects = "burns everything"`
4. Crie uma classe derivada `DummyTarget` de `ATarget`:

   - Construtor define `type = "training dummy"`
5. Faça o Warlock lançar um feitiço:

   - Ao lançar, imprime: `"name: casts spell on target"`

---

## 📦 Módulo 02 - Clone e Gerenciamento de Feitiços

### 🎯 Objetivo

Praticar o uso de ponteiros, clonagem e gerenciamento de memória com STL.

### 🧪 Exercício: SpellBook

- Crie uma classe `SpellBook` que gerencia uma coleção de ponteiros para feitiços (`ASpell*`)
- Métodos:
  - `learnSpell(ASpell*)`: adiciona uma cópia (via `clone()`) do feitiço
  - `forgetSpell(string name)`: remove feitiço da lista
  - `createSpell(string name)`: retorna nova instância de feitiço com nome correspondente

---

## 📦 Módulo 03 - MultiWarlock

### 🎯 Objetivo

Simular múltiplos magos interagindo com o sistema de feitiços.

### 🧪 Exercício: MultiWarlock

- Crie múltiplos objetos `Warlock`
- Cada Warlock pode:
  - Aprender feitiços do `SpellBook`
  - Esquecer feitiços
  - Lançar feitiços em diferentes alvos
- Utilize polimorfismo e encapsulamento para separar responsabilidades

---

## 📦 Módulo 04 - Containers STL

### 🎯 Objetivo

Trabalhar com `std::list` ou `std::map` para armazenar e manipular feitiços.

### 🧪 Exercício: ListaDeFeiticos

- Use um `std::list` de ponteiros para `ASpell`
- Métodos:
  - `addSpell()`
  - `removeSpell()`
  - `findSpellByName()`
  - `printAllSpells()`: itera e imprime todos os feitiços armazenados

---

## ⚙️ Como Compilar

Utilize um `Makefile` básico como este:

```Makefile
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = magictest
SRC = main.cpp Warlock.cpp Fireball.cpp DummyTarget.cpp SpellBook.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
```
