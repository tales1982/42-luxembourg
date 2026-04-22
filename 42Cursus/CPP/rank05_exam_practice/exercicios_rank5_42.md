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

## 📦 Módulo 01 — Magia e Alvos

### 🧪 Exercício: MagiaSimples

### 🧠 Objetivo do Exercício

Este exercício tem como foco aplicar os fundamentos da Programação Orientada a Objetos em C++:

* **Herança** : uso de classes base abstratas e classes derivadas (`ASpell`, `Fireball`, `ATarget`, `DummyTarget`)
* **Polimorfismo** : chamadas a métodos virtuais por meio de ponteiros ou referências
* **Encapsulamento e abstração** : proteção de atributos e organização lógica das funcionalidades
* **Padrão Prototype** : via o método virtual puro `clone()`, para duplicar objetos polimorficamente

### ✅ O que você deve fazer:

1. **Criar a classe abstrata `ASpell`** , representando um feitiço genérico:

* **Atributos** :
  * `name`: nome do feitiço (ex: "Fireball")
  * `effects`: descrição do efeito (ex: "burns everything")
* **Métodos** :
  * `getName()`: retorna o nome
  * `getEffects()`: retorna o efeito
  * `clone()`: método virtual puro que retorna uma cópia do objeto (ex: `new Fireball(*this)`)
  * `launch(const ATarget&)`: método que chama `target.getHitBySpell(*this)`

1. **Criar a classe abstrata `ATarget`** , representando um alvo genérico:

* **Atributo** :
  * `type`: tipo do alvo (ex: "training dummy")
* **Métodos** :
  * `getType()`: retorna o tipo
  * `clone()`: método virtual puro
  * `getHitBySpell(const ASpell&)`: imprime na tela: `"type has been effects!"`

1. **Criar a classe `Fireball` derivada de `ASpell`** :

* O construtor define:
  * `name = "Fireball"`
  * `effects = "burns everything"`
* Implementa o método `clone()` corretamente.

1. **Criar a classe `DummyTarget` derivada de `ATarget`** :

* O construtor define:
  * `type = "training dummy"`
* Implementa o método `clone()` corretamente.

1. **Simular o lançamento de um feitiço por um Warlock no `main()`** :

* Criar uma instância de `Fireball` e `DummyTarget`
* Imprimir:

  ```bash
  Fireball: casts spell on training dummy
  training dummy has been burns everything!
  ```

  <hr>

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
