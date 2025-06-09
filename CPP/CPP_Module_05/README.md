# C++ - Module 05: Repetition and Exceptions

## 📌 Summary

Este módulo tem como objetivo trabalhar com **exceções**, **formas (forms)**, e o **design de classes** seguindo o **Orthodox Canonical Form**.

---

## 🧠 Chapter I - Introduction

- C++ é uma linguagem de propósito geral derivada do C.
- Foco do módulo: **Programação Orientada a Objetos** (POO) em C++98.
- Códigos devem ser compatíveis com o padrão `-std=c++98`.

---

## 📋 Chapter II - General Rules

### ✅ Compilação

- Compilar com: `-Wall -Wextra -Werror`
- Adicionar: `-std=c++98`

### 🧱 Formatação

- Diretórios: `ex00`, `ex01`, etc.
- Arquivos devem seguir o padrão da classe: `ClassName.hpp`, `ClassName.cpp`.

### ❌ Proibições

- Proibido usar:
  - `*printf()`, `*alloc()`, `free()`
  - `using namespace <ns_name>`
  - `friend` keyword
  - STL (somente permitido nos módulos 08 e 09)

### ✅ Permissões

- Pode-se usar funções da biblioteca padrão do C++.
- Classes devem seguir o **Orthodox Canonical Form**.
- Headers devem ser independentes e conter include guards.

---

## 🧪 Chapter III - Exercise 00: Mommy, when I grow up, I want to be a bureaucrat!

### 🗂️ Arquivos:

- `Makefile`, `main.cpp`, `Bureaucrat.hpp`, `Bureaucrat.cpp`

### 🎯 Objetivo:

- Criar a classe `Bureaucrat`
  - Atributos:
    - `const std::string name`
    - `int grade` (de 1 a 150)
  - Exceções:
    - `GradeTooHighException`
    - `GradeTooLowException`
  - Métodos:
    - `getName()`, `getGrade()`
    - `incrementGrade()`, `decrementGrade()`
    - Sobrecarga do operador `<<`

---

## 📄 Chapter IV - Exercise 01: Form up, maggots!

### 🗂️ Arquivos:

- Arquivos do exercício 00 + `Form.hpp`, `Form.cpp`

### 🎯 Objetivo:

- Criar a classe `Form`

  - Atributos:
    - `const std::string name`
    - `bool isSigned`
    - `const int gradeToSign`
    - `const int gradeToExecute`
  - Métodos:
    - `getName()`, `getIsSigned()`, `getGradeToSign()`, `getGradeToExecute()`
    - `beSigned(Bureaucrat&)`
    - Sobrecarga do operador `<<`
- Atualizar `Bureaucrat` com método `signForm()`

---

## 🧾 Chapter V - Exercise 02: No, you need form 28B, not 28C...

### 🗂️ Arquivos:

- `Makefile`, `main.cpp`, `Bureaucrat.*`, `AForm.*`, `ShrubberyCreationForm.*`, `RobotomyRequestForm.*`, `PresidentialPardonForm.*`

### 🎯 Objetivo:

- Criar a classe abstrata `AForm`
- Criar classes concretas:

  - `ShrubberyCreationForm`:
    - Cria arquivo `<target>_shrubbery` com árvores ASCII
  - `RobotomyRequestForm`:
    - Robomiza o `target` com sucesso 50% das vezes
  - `PresidentialPardonForm`:
    - Informa que o `target` foi perdoado por Zaphod Beeblebrox
- Método `execute(Bureaucrat const & executor)` deve verificar:

  - Se o formulário está assinado
  - Se o executor tem nota suficiente
- Adicionar em `Bureaucrat`:

  - `executeForm(AForm const & form)`

---

## 👨‍💼 Chapter VI - Exercise 03: At least this beats coffee-making

### 🗂️ Arquivos:

- Arquivos anteriores + `Intern.hpp`, `Intern.cpp`

### 🎯 Objetivo:

- Criar classe `Intern`
- Função principal: `makeForm(formName, target)`

  - Retorna ponteiro para objeto de `Form`
  - Imprime: `Intern creates <form>`
  - Se nome do formulário não existir: erro explícito
- ❌ **Evitar uso excessivo de `if/else`** — soluções desorganizadas não serão aceitas

---

## 📤 Chapter VII - Submission and Peer Evaluation

- Submeter o projeto no repositório Git
- Avaliação será feita apenas sobre os arquivos do repositório
