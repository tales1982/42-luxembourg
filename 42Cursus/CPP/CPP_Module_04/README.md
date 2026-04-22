# 📘 C++ - Module 04

**Polimorfismo por subtipagem, classes abstratas e interfaces**

---

## 📌 Conteúdo

### 🧠 Introdução

- C++ como extensão do C, suportando OOP, programação genérica e procedural.
- Os módulos C++ da 42 focam em OOP com o padrão C++98.
- Evite recursos de C++ moderno (C++11+).

---

### ⚙️ Regras Gerais

- **Compilação**: `c++ -Wall -Wextra -Werror -std=c++98`
- **Nomes e arquivos**:
  - Classes: UpperCamelCase
  - Arquivos devem seguir o nome da classe (ex: `Animal.hpp`)
- **Mensagens**: terminadas por newline, na saída padrão.
- **Proibido**:
  - `*printf`, `*alloc`, `free`
  - `using namespace`, `friend`
  - Containers e algoritmos STL (até o módulo 08)

---

## ✅ Exercícios

### 🧪 Ex00 - Polimorfismo

- Criar classe base `Animal` com atributo `std::string type`
- Criar classes `Dog` e `Cat` que herdam de `Animal`
- Método `makeSound()` virtual e diferente para cada animal
- Criar classes `WrongAnimal` e `WrongCat` para demonstrar erro de polimorfismo sem virtual

### 🧪 Ex01 - "Je ne veux pas brûler le monde"

- Criar classe `Brain` com array `ideas[100]`
- `Dog` e `Cat` possuem `Brain*`
- Implementar **deep copy** corretamente
- Criar array de `Animal*`, metade `Dog`, metade `Cat`, deletar corretamente
- Verificar ausência de **memory leaks**

### 🧪 Ex02 - Classe Abstrata

- Tornar `Animal` **classe abstrata** com pelo menos uma função `virtual = 0`
- Previne instanciação direta

### 🧪 Ex03 - Interface & Recap

- Criar classe abstrata `AMateria` com:

  - `getType()`
  - `clone() = 0`
  - `use(ICharacter&)`
- Criar classes `Ice` e `Cure` herdando de `AMateria`
- Criar interface `ICharacter` e classe concreta `Character`

  - Inventário de 4 `AMateria*`
  - Métodos: `equip`, `unequip`, `use`
  - Implementar **deep copy**
- Criar interface `IMateriaSource` e classe `MateriaSource`

  - `learnMateria(AMateria*)`
  - `createMateria(std::string const&)`

---

## 📥 Entrega e Avaliação

- Submeter via Git
- Apenas os arquivos no repositório serão avaliados
- Conferir nomes dos diretórios e arquivos
