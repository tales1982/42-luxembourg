# ft_otp — Manual de Uso

Gerador de senhas temporárias (OTP) usando o algoritmo HOTP/TOTP (RFC 4226 / RFC 6238).

---

## Dependências

Apenas bibliotecas padrão do Python 3 — nenhuma instalação necessária.

---

## Como executar

### Passo 1 — Criar um arquivo com a chave hexadecimal

A chave deve ter **no mínimo 64 caracteres hexadecimais** (0-9 e a-f).

```bash
# Exemplo: gerar uma chave de 64 caracteres
python3 -c "print('a' * 64, end='')" > key.hex

# Ou usar uma chave real (64 hex chars)
echo -n "4d793132334e756e63615365637265743132334e756e63615365637265743132" > key.hex
```

### Passo 2 — Salvar a chave com -g

```bash
./ft_otp -g key.hex
```

Saída esperada:
```
Key was successfully saved in ft_otp.key.
```

### Passo 3 — Gerar uma senha com -k

```bash
./ft_otp -k ft_otp.key
```

Saída esperada:
```
836492
```

A senha muda a cada 30 segundos.

---

## Exemplos de erro

```bash
# Chave com menos de 64 caracteres ou não hexadecimal
echo -n "NEVER GONNA GIVE YOU UP" > key.txt
./ft_otp -g key.txt
# ./ft_otp: error: key must be 64 hexadecimal characters.
```

---

## Verificar se está correto com oathtool

Instale o oathtool:
```bash
sudo apt install oathtool
```

Compare as saídas (execute os dois rapidamente):
```bash
./ft_otp -k ft_otp.key
oathtool --totp "$(cat key.hex)"
```

Os dois devem mostrar o **mesmo número**. A senha muda a cada 30 segundos, então execute ambos dentro da mesma janela de tempo.
