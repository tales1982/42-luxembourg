# Minishell - Escola 42

## Descrição
Este projeto faz parte do currículo da Escola 42 e envolve a criação de um shell simples chamado **Minishell**. O objetivo é replicar o comportamento de um shell Unix, permitindo a execução de comandos básicos, manipulação de processos e sinais, redirecionamento de entrada/saída, e muito mais.

## Tópicos de Estudo
Para a realização deste projeto, é necessário ter um bom entendimento dos seguintes tópicos:

### 1. Programação em C
- Conhecimento avançado da linguagem C, pois o Minishell é implementado nesta linguagem.
- **Manipulação de strings e arrays**: O Minishell envolve muitas operações com strings, como parsing de comandos.
- **Ponteiros e memória**: Entender bem a alocação dinâmica de memória e como manipular ponteiros é essencial.

### 2. Sistemas Operacionais
- **Processos**: Como criar e manipular processos utilizando `fork()`, `execve()` e `waitpid()`.
- **Sinais**: Entender como enviar e capturar sinais (`signal handling`) em um ambiente Unix.
- **Pipes**: Como criar comunicação entre processos usando `pipe()`.

### 3. Shell Scripting e Comandos Unix
- Conhecimento básico de como um shell funciona.
- Familiaridade com comandos Unix, redirecionamento de entrada/saída, e pipelines.

### 4. Manipulação de Arquivos
- Como abrir, ler, escrever e fechar arquivos em C.
- Redirecionamento de entrada e saída padrão (`stdin`, `stdout`, `stderr`).

### 5. Parsing e Interpretação de Comandos
- Como dividir uma linha de comando em comandos e argumentos.
- Como interpretar operadores como `|`, `;`, `&&`, `||`, e redirecionamentos (`>`, `<`).

### 6. Estruturas de Dados
- Conhecimento em listas ligadas pode ser útil para gerenciar a lista de comandos e argumentos.

### 7. Documentação e Leitura de Manuais
- Capacidade de ler e entender a documentação do sistema, como as man pages (`man`), para funções do Unix.

## Como Usar
Instruções sobre como compilar e usar o Minishell serão adicionadas conforme o desenvolvimento do projeto avança.

## Contribuições
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests.

## Licença
Este projeto está licenciado sob a Licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.
