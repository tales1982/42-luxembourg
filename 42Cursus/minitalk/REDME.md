<# Minitalk

## Objetivos do Minitalk

- **Entendimento de sinais UNIX:** Aprender a usar sinais como SIGUSR1 e SIGUSR2 para comunicação entre processos.
- **Implementação de um protocolo de comunicação simples:** Criar um protocolo para enviar e receber mensagens usando apenas esses sinais.
- **Manuseio de processos:** Trabalhar com processos em C, incluindo como criar, matar e manipular processos filhos.
- **Tratar sinais:** Saber como capturar e lidar com sinais recebidos, garantindo que o programa se comporte corretamente.

## Estrutura do Projeto

- **Servidor (`server.c`):** Um programa que espera receber mensagens de um cliente. O servidor decodifica as mensagens recebidas e as exibe.
- **Cliente (`client.c`):** Um programa que envia mensagens ao servidor, codificando cada caractere da mensagem em uma série de sinais.
- **Comunicação:** A comunicação é feita enviando sinais do cliente para o servidor. Cada caractere da mensagem pode ser convertido em uma sequência de bits e enviado bit a bit usando os sinais SIGUSR1 e SIGUSR2.

## Exemplo de Funcionamento

1. O servidor é iniciado e imprime seu PID (Process ID).
2. O cliente é executado com o PID do servidor e a mensagem a ser enviada como argumentos.
3. O cliente envia a mensagem ao servidor usando sinais.
4. O servidor recebe os sinais e reconstrói a mensagem, exibindo-a.

## Desafios Comuns

- **Sincronização:** Garantir que os sinais sejam enviados e recebidos na ordem correta.
- **Taxa de Sinais:** Manter a taxa de envio de sinais de modo que o servidor possa processar cada sinal corretamente.
- **Erro e Recuperação:** Implementar mecanismos para detectar e corrigir erros na transmissão.

## Considerações Finais

O exercício Minitalk é excelente para aprender sobre comunicação entre processos, sinais UNIX e manipulação de processos em C. Ele também reforça conceitos importantes de programação de sistemas, como sincronização e tratamento de erros.

