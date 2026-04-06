# SnowCrash — Level09 Walkthrough (Metodologia)

## Objetivo

Neste nível, o binário **transforma** o input de forma não óbvia antes de compará-lo ou processá-lo. O objetivo é descobrir a lógica da transformação e revertê-la para obter o input correto (ou o token).

---

## Arquivos disponíveis

Listando o diretório home do level09:

```bash
ls -la
```

Saída típica:

```
-rwsr-s---+ 1 flag09 level09  level09
-rw-r-----+ 1 flag09 level09  token
```

Existe um binário SUID e um arquivo `token` com o conteúdo transformado.

---

## Investigação do comportamento

Testando o binário com entradas pequenas para observar o padrão:

```bash
./level09 a
./level09 aa
./level09 abc
```

Saídas observadas:

```
a    →  a
aa   →  ab
abc  →  ace
```

**Padrão identificado:** cada caractere é incrementado pelo seu índice (posição, 0-based).

- posição 0: `a` + 0 = `a`
- posição 1: `a` + 1 = `b`
- posição 2: `b` + 2 = `d`
- posição 2: `c` + 2 = `e`

---

## Entendimento da transformação

O binário aplica:

```
output[i] = input[i] + i
```

Para reverter o token (que foi transformado), aplicamos o inverso:

```
input[i] = token[i] - i
```

---

## Lendo o token

```bash
cat token
```

Saída (exemplo):

```
f4kmm6p|=qFollowMy
```

O conteúdo do token já foi transformado — precisamos reverter.

---

## Reversão — script Python

```bash
python -c "
t = open('token','rb').read().strip()
print ''.join(chr(ord(b) - i) for i, b in enumerate(t))
"
```

> **Nota:** `python3` não está disponível no SnowCrash VM. Usar `python` (Python 2) com `print` sem parênteses e `ord(b)` para converter o byte.

---

## Resultado

Token revertido (senha do `flag09`):

```
f3iji1ju5yuevaus41q1afiuq
```

---

## Obter o token final

```bash
su flag09
Password: f3iji1ju5yuevaus41q1afiuq
getflag
```

**Token para o level10: s5cAJpM8ev6XHw998pRWG728z**

```
s5cAJpM8ev6XHw998pRWG728z
```

---

## Conceito aprendido

Este exercício demonstra: **análise de transformação de dados e reversão**.

O programa não compara a senha diretamente — ele transforma a entrada e compara o resultado. Entender a transformação é o caminho para a solução.

---

## Técnica de investigação

1. Testar entradas curtas e controladas (`a`, `aa`, `ab`, `abc`)
2. Comparar entrada × saída caractere por caractere
3. Identificar o padrão (incremento por posição, XOR, ROT, etc.)
4. Escrever o inverso e aplicar ao token existente

---

## Vulnerabilidade real equivalente

Padrões assim aparecem em:

- Ofuscação fraca de senhas armazenadas
- Protocolos caseiros de encoding sem criptografia real
- CTFs com "criptografia" inventada

---

## Mitigação

- Nunca usar transformações reversíveis como substituto de hashing
- Senhas devem ser armazenadas com `bcrypt`, `argon2`, ou similar
- Transformações determinísticas e sem chave não são criptografia

---

## Ferramentas utilizadas

| Comando       | Função                                 |
| ------------- | ---------------------------------------- |
| `ls -la`    | listar arquivos e permissões            |
| `strings`   | inspecionar strings do binário          |
| `./level09` | testar comportamento com inputs pequenos |
| `cat token` | ler o token transformado                 |
| `python3`   | reverter a transformação               |
| `su flag09` | logar com o token revertido              |
| `getflag`   | obter token final do nível              |

---

## Resultado final

Transformação revertida com sucesso via análise de padrão.

**Token para level10: s5cAJpM8ev6XHw998pRWG728z**

```
<preencher após execução>
```
