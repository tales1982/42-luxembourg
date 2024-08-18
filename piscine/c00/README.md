# C00 - 42 Piscine Project

Este repositório contém os exercícios e funções desenvolvidas para o projeto C00 da 42 School. O objetivo deste projeto é praticar a linguagem C, abordando conceitos básicos e manipulação de funções.

## Estrutura do Projeto

O projeto está estruturado da seguinte forma:

```plaintext
c00/
├── ex00/
│   └── ft_putchar.c
├── ex01/
│   └── ft_print_alphabet.c
├── ex02/
│   └── ft_print_reverse_alphabet.c
├── ex03/
│   └── ft_print_numbers.c
├── ex04/
│   └── ft_is_negative.c
├── ex05/
│   └── ft_print_comb.c
├── ex06/
│   └── ft_print_comb2.c
├── main.c
├── main.h
└── Makefile
```

# Como Compilar o Projeto
Para compilar o projeto, você precisa ter o compilador gcc instalado no seu sistema. Siga os passos abaixo:

Clone o repositório (se ainda não o fez):

```bash
git clone https://github.com/seu-usuario/42-c00-project.git
cd 42-c00-project/c00
```
Compile o projeto:
No diretório raiz do projeto (c00), execute o seguinte comando para compilar todos os arquivos e gerar o executável:

```bash
make
```
Isso irá compilar todos os arquivos .c dentro dos diretórios ex00, ex01, etc., e criar um executável chamado c00.

Executar o programa:
Após a compilação, você pode executar o programa com o seguinte comando:

```bash
./c00
```
Limpeza
Para limpar os arquivos objeto (.o) gerados durante a compilação, execute:

```bash
make clean
```
Para limpar os arquivos objeto e o executável, execute:

```bash
make fclean
```
Para recompilar tudo do zero, execute:

```bash
make re
```