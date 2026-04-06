# SnowCrash — Level02 Walkthrough (Metodologia)

## Objetivo

Neste nível, o objetivo é recuperar a senha do usuário `flag02` analisando um arquivo de captura de rede (`.pcap`).

Diferente do level01 (password cracking com hash), aqui aprendemos:

- análise de tráfego de rede
- leitura de capturas TCP
- extração manual de credenciais
- reconhecimento de sessões Telnet inseguras

---

## Arquivo disponível

Ao listar o diretório:

```bash
ls
```

Resultado:

```
level02.pcap
```

O arquivo `.pcap` indica captura de tráfego de rede — precisamos analisar os dados transmitidos.

---

## Primeira tentativa: identificar tipo do arquivo

```bash
file level02.pcap
```

Resultado esperado:

```
pcap capture file
```

Confirma que é uma captura de rede válida.

---

## Analisando o tráfego

Utilizamos o `tshark` para reconstruir o fluxo TCP:

```bash
tshark -r level02.pcap -q -z follow,tcp,ascii,0
```

Explicação:

| comando        | função                 |
| -------------- | ------------------------ |
| `tshark`     | versão CLI do Wireshark |
| `-r`         | lê arquivo              |
| `follow,tcp` | reconstrói sessão TCP  |
| `ascii`      | mostra texto legível    |
| `0`          | stream TCP número 0     |

---

## Observação do conteúdo da sessão

O output mostra:

```
wwwbugs login:
```

Depois aparecem caracteres digitados pelo usuário:

```
Password:
f
t
_
w
a
n
d
r
.
.
.
N
D
R
e
l
.
L
0
L
```

Cada linha representa um caractere digitado durante a autenticação Telnet.

---

## Importante

Os caracteres `.` **não fazem parte da senha**.

Eles representam:

- backspace
- controle de terminal
- caracteres não imprimíveis

Ou seja, devem ser ignorados.

---

## Reconstrução da senha

Removendo caracteres inválidos:

```
f t _ w a n d r N D R e l L 0 L
```

Senha final:

```
ft_waNDReL0L
```

---

## Acessando o usuário flag02

```bash
su flag02
```

Senha:

```
ft_waNDReL0L
```

---

## Obtendo a flag

```bash
getflag
```

Resultado: kooda2puivaav1idi4f57q8iq

## Conceito aprendido

Este exercício demonstra um problema clássico de segurança:

> **Telnet transmite senhas em texto puro.**

Ou seja, qualquer captura de rede pode revelar credenciais. Por isso Telnet é considerado inseguro.

Hoje utilizamos **SSH** em vez de Telnet.

---

## Mitigação em ambiente real

Nunca utilizar:

- Telnet
- FTP
- HTTP sem TLS

Sempre preferir:

- SSH
- SFTP
- HTTPS

---

## Ferramentas utilizadas

| ferramenta  | uso                         |
| ----------- | --------------------------- |
| `file`    | identificar tipo do arquivo |
| `tshark`  | analisar tráfego           |
| `strings` | extrair texto bruto         |
| `su`      | trocar usuário             |
| `getflag` | obter flag do nível        |

---

## Resultado final

Senha do usuário `flag02`:

```
ft_waNDReL0L
```

Token obtido com `getflag` (token para o level03): kooda2puivaav1idi4f57q8iq

```
kooda2puivaav1idi4f57q8iq
```
