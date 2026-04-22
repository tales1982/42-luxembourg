# C++ - Module 02: Polymorphisme ad-hoc, surcharge d’opérateurs et forme canonique

## 📚 Objetivo do Módulo

Introduzir os conceitos fundamentais da Programação Orientada a Objetos (POO) utilizando C++98:

- Forma canônica (Coplien form)
- Sobrecarga de operadores
- Conceitos de número de ponto fixo
- Comparações, operações aritméticas, incremento/decremento

---

## ✅ Regras Gerais

- Use `c++ -Wall -Wextra -Werror -std=c++98` para compilar.
- Nomes de arquivos e classes devem seguir o padrão:
  - Classes em UpperCamelCase
  - Arquivos: `Classe.hpp` / `Classe.cpp`
- Evite bibliotecas C (`printf`, `malloc`, `free`) e bibliotecas modernas como C++11 ou Boost.
- Proibido containers STL (`vector`, `map`, etc.) até o módulo 08.
- Evite `using namespace` e `friend`.
- Sem memory leaks: tudo que for alocado com `new` deve ser liberado com `delete`.
- Separar arquivos `.hpp` e `.cpp`.

---

## ✨ Forma Canônica (Coplien Form)

Cada classe deve conter:

- Construtor padrão
- Construtor de cópia
- Operador de atribuição
- Destrutor

---

## 🧪 Exercício 00 - Mon premier canon

### Objetivo:

Criar a classe `Fixed` com forma canônica.

### Requisitos:

- Atributos:
  - `_value` (int)
  - `_fractionalBits` (const static int, valor fixo 8)
- Métodos:
  - `getRawBits(void) const`
  - `setRawBits(int const raw)`

### Arquivos a entregar:

- `main.cpp`
- `Fixed.hpp`
- `Fixed.cpp`
- `Makefile`

---

## 🔧 Exercício 01 - Premiers pas vers une classe utile

### Objetivo:

Expandir a classe `Fixed` para trabalhar com int e float.

### Novos métodos:

- Construtor com `int`
- Construtor com `float`
- `toFloat() const`
- `toInt() const`
- Operador `<<` (ostream)

---

## ➕ Exercício 02 - Maintenant, on peut parler

### Objetivo:

Adicionar operações à classe `Fixed`.

### Operadores a implementar:

- Comparação: `>`, `<`, `>=`, `<=`, `==`, `!=`
- Aritméticos: `+`, `-`, `*`, `/`
- Incremento/Decremento: `++`, `--` (pré e pós)

### Métodos Estáticos:

- `min(Fixed&, Fixed&)`
- `min(const Fixed&, const Fixed&)`
- `max(Fixed&, Fixed&)`
- `max(const Fixed&, const Fixed&)`

---

## 🔺 Exercício 03 - BSP (opcional)

### Objetivo:

Criar uma função que verifica se um ponto está dentro de um triângulo.

### Classe `Point`:

- Atributos: `x`, `y` (ambos `Fixed`, constantes)
- Implementar forma canônica

### Função:

```cpp
bool bsp(Point const a, Point const b, Point const c, Point const point);
```

---

## ✅ Avaliação

- Submeter via repositório Git.
- Verifique nomes de arquivos e pastas.
- Apenas arquivos no repositório serão avaliados.

---

## 🧠 Dicas Gerais

- Leia os artigos recomendados sobre ponto fixo.
- Use `roundf()` quando necessário.
- Teste exaustivamente suas funções.
- Códigos limpos e organizados serão melhor avaliados.
