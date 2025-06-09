
# 🧠 Exercícios Estilo Rank 5 – Escola 42

## 1. Conversão de Literais (Module 06)
Crie um programa `converter` que converte strings em diferentes tipos primitivos:
- `char` (ex: `'a'`)
- `int` (ex: `42`)
- `float` (`42.0f`)
- `double` (`42.0`)
- Pseudo-literal (`nan`, `+inf`, `-inff`)

Imprima os valores convertidos:
```
char: ’a’
int: 42
float: 42.0f
double: 42.0
```
Use mensagens como `impossible` ou `non displayable` quando apropriado.

---

## 2. Serialização de Ponteiros (Module 06)
Crie uma struct `Data { int x; char y; };` com métodos:
```cpp
static uintptr_t serialize(Data* ptr);
static Data* deserialize(uintptr_t raw);
```
Garanta que `deserialize(serialize(ptr)) == ptr`.

---

## 3. Identificação de Tipos Dinâmicos (Module 06)
Implemente:
- `class Base`
- `class A : public Base`, idem para B e C
- `Base* generate()` retorna `A`, `B` ou `C`
- `void identify(Base* p)` e `identify(Base& p)` usam `dynamic_cast`

---

## 4. Templates Básicos (Module 07)
Crie `whatever.hpp` com:
```cpp
template<class T> void swap(T& a, T& b);
template<class T> T min(const T& a, const T& b);
template<class T> T max(const T& a, const T& b);
```
Teste com `int`, `double`, `std::string`.

---

## 5. Iterador de Array (Module 07)
Função `iter` genérica:
```cpp
template<typename T>
void iter(T* arr, size_t n, void (*func)(T&));
```
Aplique uma função a todos os elementos.

---

## 6. Classe Array Template (Module 07)
Requisitos:
- `Array<T> arr(n)`
- Acesso por `arr[i]` com exceções para índice inválido
- Método `size()`
- Suporte a deep copy

---

## 7. EasyFind (Module 08)
Template `easyfind` que busca um valor em containers STL:
```cpp
template<typename T>
typename T::iterator easyfind(T& container, int to_find);
```
Lança exceção se não encontrar.

---

## 8. Span (Module 08)
Classe `Span` que calcula:
- `shortestSpan()`
- `longestSpan()`
- Adição individual e por range

---

## 9. MutantStack (Module 08)
Classe que herda `std::stack` e permite iteração:
```cpp
typedef typename std::stack<T>::container_type::iterator iterator;
iterator begin();
iterator end();
```

---

## 10. Bitcoin Exchange (Module 09)
Dado um CSV com preços do Bitcoin e um `input.txt`, converta valores com base na data mais próxima anterior.

---

## 11. RPN - Reverse Polish Notation (Module 09)
Avalie expressões como `"3 4 + 2 *"` usando `std::stack<int>`.
Trate:
- Operadores `+ - * /`
- Divisão por zero
- Tokens inválidos

---

## 12. PmergeMe - Ford-Johnson Sort (Module 09)
- Recebe números em `argv`
- Usa `vector` e `deque`
- Ordena usando Ford-Johnson
- Mostra tempos de execução

---

## ✅ Dicas
- Compile com `-std=c++98 -Wall -Wextra -Werror`
- Sempre trate exceções e valide entradas
- Crie Makefiles para cada exercício
