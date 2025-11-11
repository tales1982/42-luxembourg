# BigInt (C++98)

Implementação de inteiros de precisão arbitrária (sinal + magnitude) em C++98.

## Características

- Representação em base 10, dígitos em ordem *LSB-first* (`d[0]` é a unidade).
- Suporte a: `+ - * / %`, comparações, `++ --` (pré e pós), `<<`/`>>` (I/O).
- Construtores: padrão, de `int`, de `std::string`, cópia.
- Forma canônica ortodoxa (Rule of Three).
- Tratamento de zero e normalização.
- Divisão por zero lança `std::runtime_error`.

## Build & run

```bash
make
./bigint
```
