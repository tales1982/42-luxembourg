# C++ - Module 06: C++ Casts

## 📌 Summary

This module contains exercises for Module 06 of the C++ modules. It focuses on type casting in C++.

---

## 🧠 Chapter I: Introduction

- C++ is a general-purpose language created as an extension of C, often called "C with Classes".
- Goal: Introduce Object-Oriented Programming (OOP) using the C++98 standard.
- You’re encouraged to explore modern C++ later, eyond 42.

---

## 🛠️ Chapter II: General Rules

### Compilation

- Compile with:
  ```sh
  c++ -Wall -Wextra -Werror -std=c++98
  ```

### Formatting and Naming

- Directories: `ex00`, `ex01`, ..., `exn`
- File naming: follow the class name (e.g., `BrickWall.hpp`, `BrickWall.cpp`)
- Class names: UpperCamelCase

### Output

- All messages must end with a newline and be printed to `stdout`.

### Coding Style

- No enforced style, but code must be clean and readable.

### Allowed & Forbidden

✅ Allowed:

- Most of the standard library (C++98 only)

🚫 Forbidden:

- C++11/Boost
- `*printf()`, `*alloc()`, `free()`
- `using namespace`
- `friend`
- STL containers & algorithms (until Modules 08–09)

### Design Guidelines

- No memory leaks (watch `new`/`delete`)
- Follow Orthodox Canonical Form (Modules 02–09)
- No implementation in headers (except templates)
- Use include guards
- Headers must be independent

### Misc

- You can add extra files.
- Examples may show requirements not written in the instruction.
- Read the full module before starting.

---

## 📏 Chapter III: Additional Rule

- Type conversion must be handled using **specific casting types**.
- Your choices will be reviewed during defense.

---

## 💡 Chapter IV: Exercise 00 - Conversion of Scalar Types

### Requirements

- **Turn-in**: `ex00/`, `Makefile`, `*.cpp`, `*.h`, `*.hpp`
- **Allowed functions**: string to int/float/double conversions

### Objective

Create a class `ScalarConverter` with:

```cpp
static void convert(std::string const &literal);
```

### Behavior

- Input: a string literal
- Output: value converted to:
  - `char`
  - `int`
  - `float`
  - `double`
- Only decimal notation (except for `char`)
- Handle pseudo-literals like `nan`, `+inf`, `-inf`, etc.

### Example Output

```txt
./convert 0
char: Non displayable
int: 0
float: 0.0f
double: 0.0
```

If conversion fails, display `impossible`.

---

## 💡 Chapter V: Exercise 01 - Serialization

### Requirements

- **Turn-in**: `ex01/`, `Makefile`, `*.cpp`, `*.h`, `*.hpp`

### Objective

Create a class `Serializer` with:

```cpp
static uintptr_t serialize(Data* ptr);
static Data* deserialize(uintptr_t raw);
```

- `serialize()`: pointer ➜ `uintptr_t`
- `deserialize()`: `uintptr_t` ➜ pointer

### Test

- Define a `Data` struct with data members
- Serialize a `Data*`, then deserialize and verify equality

---

## 💡 Chapter VI: Exercise 02 - Identify Real Type

### Requirements

- **Turn-in**: `ex02/`, `Makefile`, `*.cpp`, `*.h`, `*.hpp`
- **Forbidden**: `std::typeinfo`

### Objective

Create:

- A base class `Base` with a virtual destructor
- Empty classes `A`, `B`, `C` inheriting from `Base`

Implement:

```cpp
Base* generate(void);
void identify(Base* p);  // print "A", "B", or "C"
void identify(Base& p);  // print "A", "B", or "C"
```

- `generate()`: randomly creates and returns `A`, `B`, or `C`
- `identify()` uses dynamic casting
- `typeinfo` and `typeid` are **forbidden**

---

## ✅ Chapter VII: Submission & Peer Evaluation

- Submit via your Git repository.
- Ensure all file and folder names are correct.
- Only submitted files will be graded.
