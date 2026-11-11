# Reverse_me — Manual de Uso

Engenharia reversa de 3 crackmes (`level1` 32-bit, `level2` 32-bit, `level3` 64-bit).
Cada senha foi obtida com `objdump`/`strings` para localizar a lógica de
comparação e `gdb` para inspecionar a memória em tempo de execução, sem
qualquer força bruta.

---

## Estrutura

```
level1/level1, senha, source.c
level2/level2, senha, source.c
level3/level3, senha, source.c
bonus/level{1,2,3}_patched, README.md   # parte bônus: aceitam qualquer senha
binary/                                  # binários originais (do binary.tgz)
```

## Como validar

```bash
./level1/level1 < level1/senha
./level2/level2 < level2/senha
./level3/level3 < level3/senha
```

Cada um deve responder `Good job.`.

## Senhas encontradas

| Nível | Senha |
|---|---|
| level1 | `__stack_check` (armazenada em texto puro no `.rodata`) |
| level2 | `00101108097098101114101` (ver decodificação abaixo) |
| level3 | `42042042042042042042042` (ver decodificação abaixo) |

### level1

`strcmp(input, "__stack_check")` direto — a senha está em texto plano no
binário, confirmado com `strings level1` e `gdb`.

### level2

O programa lê no máximo 23 caracteres (`scanf("%23s", ...)`). Os dois
primeiros caracteres devem ser `"00"`. A partir do 3º caractere, a
entrada é lida em grupos de 3 dígitos; cada grupo é convertido com
`atoi()` e truncado para 1 byte, formando (junto com um `'d'` fixo no
início) a string a comparar com a senha real `"delabere"`. Cada
caractere de `"elabere"` foi convertido para seu código ASCII decimal de
3 dígitos: `101 108 097 098 101 114 101`, prefixado por `"00"`.

### level3

Mesmo esquema do level2, mas os dois caracteres fixos exigidos são
`"42"` e a senha alvo é `"********"` (8 asteriscos, byte `0x2a`). Como o
primeiro `'*'` já é fixo no código, bastam 7 grupos `"042"` (que via
`atoi` viram `42 = '*'`) após o prefixo `"42"`.

## source.c

Cada `source.c` é uma reimplementação em C que reproduz exatamente o
comportamento observado no binário (mesmos prompts, mesma lógica de
decodificação, mesmas mensagens `Good job.` / `Nope.`), verificada
compilando e comparando a saída com o binário original para várias
entradas (senha certa, senha errada, entrada malformada).

```bash
gcc -o level1_repro level1/source.c
gcc -o level2_repro level2/source.c
gcc -o level3_repro level3/source.c
```

## Bônus

Ver [`bonus/README.md`](bonus/README.md): patches binários que fazem
cada programa aceitar **qualquer** senha, aplicados diretamente nos
bytes do executável (sem `LD_PRELOAD`, sem sobrescrever funções de
biblioteca), com a justificativa de cada byte alterado.
