
# Exercícios Preparatórios para o Exame Rank 05

Este conjunto de exercícios visa preparar você para o exame Rank 05 da 42, com base nos tópicos encontrados no repositório oficial.

---

## 📦 Módulo 00 - Warlock Básico

### Objetivo

Entender o uso de classes simples e construtores.

### Exercício: WarlockIntro

Crie uma classe `Warlock` com:

- Nome e título (string)
- Construtor que define ambos
- Métodos `getName()`, `getTitle()`, `introduce()`

---

## 📦 Módulo 01 - Magia e Alvos

### Objetivo

Aprofundar herança e polimorfismo.

### Exercício: MagiaSimples

- Crie classe base `ASpell` com nome e efeito
- Crie classe base `ATarget` com tipo
- Crie uma classe derivada de `ASpell`: `Fireball`
- Crie uma classe derivada de `ATarget`: `DummyTarget`
- Warlock pode lançar um feitiço em um alvo, imprimindo uma mensagem.

---

## 📦 Módulo 02 - Clone e Gerenciamento

### Objetivo

Aprender a clonar objetos e armazená-los.

### Exercício: SpellBook

- Crie uma classe `SpellBook` que pode armazenar feitiços
- Adicione método `learnSpell(ASpell*)` e `createSpell(string)`
- Use `clone()` para retornar nova instância de um feitiço existente

---

## 📦 Módulo 03 - Interface de Interface

### Objetivo

Lidar com múltiplos Warlocks e Tarefas

### Exercício: MultiWarlock

- Crie vários Warlocks
- Permita que eles aprendam e esqueçam feitiços
- Warlocks podem lançar feitiços em diferentes alvos

---

## 📦 Módulo 04 - Container de Magias

### Objetivo

Trabalhar com listas STL para armazenar objetos.

### Exercício: ListaDeFeiticos

- Crie uma lista (`std::list`) de feitiços
- Permita adicionar, remover e buscar feitiços pelo nome
- Use `iterator` para imprimir todos os feitiços

---

## Como Compilar

Use um `Makefile` básico com:

```Makefile
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = magictest
SRC = main.cpp Warlock.cpp Spell.cpp Target.cpp
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

---

Esses exercícios ajudam a solidificar os conceitos exigidos na prova Rank 05 com abordagens mais simples.
