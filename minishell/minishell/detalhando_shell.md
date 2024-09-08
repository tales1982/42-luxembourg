# SHELL
- 1. **Entendimento básico de um shell**
Um shell é um programa que oferece uma interface de linha de comando para interagir com o sistema operacional. Ele lê comandos, os interpreta e, em seguida, executa-os.

- 2. **Inicializar o shell**
Crie um loop principal que irá ler os comandos do usuário repetidamente até que ele decida sair (exit).
No loop principal:
Exiba um prompt para o usuário (por exemplo, $ ).
Leia o comando do usuário.
Processe e execute o comando.

- 3. **Dividir o comando em tokens**
Após ler o comando, você precisa dividi-lo em partes (tokens) para identificar o comando e seus argumentos. Isso pode ser feito usando a função strtok() ou ft_split da Libft (se estiver usando a biblioteca).
Exemplo: O comando "ls -la" deve ser dividido em:
```bash
cmd = "ls"
arg1 = "-la"
```
- 4. **Implementar a execução do comando**
Use a função fork() para criar um novo processo. O processo filho vai executar o comando enquanto o processo pai espera o filho terminar usando wait() ou waitpid().
Use execve() para substituir o processo filho pelo novo programa (o comando fornecido). A função execve() carrega e executa um novo programa no processo.
Um exemplo básico de uso seria:
```bash
pid_t pid = fork();
if (pid == 0) {
    // Processo filho
    execve(cmd, args, envp);  // Executa o comando
    perror("execve failed");  // Caso o execve falhe
    exit(EXIT_FAILURE);       // Saída do filho em caso de erro
} else if (pid > 0) {
    // Processo pai
    wait(NULL);  // Espera o processo filho terminar
} else {
    // Erro no fork
    perror("fork failed");
}
```
- 5. Gerenciar variáveis de ambiente
O shell precisa ter acesso às variáveis de ambiente, como o PATH, que especifica os diretórios onde procurar executáveis. Use getenv() para acessar variáveis de ambiente e busque o caminho correto dos comandos.
Ao usar execve(), você também deve fornecer o ambiente atual no terceiro argumento (o envp[]).

- 6. Implementar comandos internos (builtins)
Alguns comandos não são executáveis externos, mas são internos do shell. Os mais comuns incluem:
cd: mudar de diretório.
exit: sair do shell.
env: listar variáveis de ambiente.
Esses comandos precisam ser tratados de maneira especial, pois não devem ser executados usando execve(). Eles são processados diretamente no shell.

- 7. Gerenciar sinais
O shell precisa gerenciar sinais como Ctrl+C (SIGINT) e Ctrl+Z (SIGTSTP) para permitir que o usuário possa interromper ou parar processos. Use a função signal() ou sigaction() para capturar e lidar com esses sinais.
Exemplo:
signal(SIGINT, handle_sigint);

- 8. Gerenciar redirecionamento e pipes
Redirecionamento: Implementar a capacidade de redirecionar a saída ou entrada de comandos para arquivos (>, <, >>).
Você pode usar as funções open() e dup2() para redirecionar stdin ou stdout.
Pipes: Implementar pipes (|) para permitir que a saída de um comando seja a entrada de outro comando. Use pipe() para criar pipes entre processos.

- 9. Gerenciamento de erros
Trate adequadamente erros, como comandos não encontrados, permissões negadas e outros problemas que podem surgir durante a execução de um comando.
Use perror() para exibir mensagens de erro baseadas no valor de errno.

- 10. Loop principal e saída do shell
O shell continua executando até o comando exit ser chamado, fechando o loop principal.
Estrutura Básica do Código:
```bash
int main(int argc, char **argv, char **envp) 
{
    char *input;
    char **args;
   
    while (1) {
        // 1. Exibir o prompt
        printf("$ ");
        
        // 2. Ler comando do usuário
        input = read_input();
        
        // 3. Dividir o comando em tokens (usando strtok ou ft_split)
        args = split_input(input);
        
        // 4. Verificar se é um comando builtin (como 'cd' ou 'exit')
        if (is_builtin(args)) {
            execute_builtin(args);
        } else {
            // 5. Criar um processo filho e executar o comando
            execute_command(args, envp);
        }

        // 6. Liberar memória alocada (se necessário)
        free(input);
        free(args);
    }
    
    return 0;
}
```
Recursos úteis:
Funções importantes: fork(), execve(), wait(), signal(), dup2(), pipe(), open(), close().
Para lidar com strings e parsing, a biblioteca Libft pode ser útil.
Essas são as etapas principais para criar um shell simples em C.


Aqui está uma lista das funções e uma breve explicação do que cada uma faz:

## Funções da biblioteca readline:
1. **readline**: Lê uma linha de entrada do usuário com recursos como histórico e edição de linha.
2. **rl_clear_history**: Limpa o histórico de linhas lidas anteriormente.
3. **rl_on_new_line**: Sinaliza para o readline que uma nova linha foi iniciada.
4. **rl_replace_line**: Substitui a linha de entrada atual por uma nova linha.
5. **rl_redisplay**: Atualiza e redisplay a linha de comando editada pelo usuário.
6. **add_history**: Adiciona a linha mais recentemente lida ao histórico de comandos.
## Funções da biblioteca padrão C (stdio.h, stdlib.h, unistd.h, etc.):
8. **printf**: Imprime uma string formatada na saída padrão.
9. **malloc**: Aloca dinamicamente uma quantidade de memória.
10. **free**: Libera a memória previamente alocada por malloc.
11. **write**: Escreve dados para um arquivo ou descritor de arquivo (como stdout ou stderr).
12. **access**: Verifica a acessibilidade de um arquivo (se ele existe, tem permissões, etc.).
13. **open**: Abre um arquivo e retorna um descritor de arquivo.
14. **read**: Lê dados de um arquivo ou descritor de arquivo.
15. **close**: Fecha um arquivo ou descritor de arquivo.
## Funções de criação e gerenciamento de processos:
16. **fork**: Cria um novo processo, o processo filho, que é uma cópia do processo pai.
17. **wait**: Faz o processo pai esperar até que o processo filho termine.
18. **waitpid**: Espera por um processo específico terminar.
19. **wait3**: Espera que qualquer processo filho termine, retornando informações adicionais sobre o uso de recursos.
20. **wait4**: Similar a wait3, mas permite especificar um PID e outras opções.
21. **signal**: Define o comportamento de tratamento de sinais para o processo.
22. **sigaction**: Fornece controle detalhado sobre como os sinais são tratados.
23. **sigemptyset**: Inicializa um conjunto de sinais para não conter sinais.
24. **sigaddset**: Adiciona um sinal a um conjunto de sinais.
25. **kill**: Envia um sinal a um processo (como para terminá-lo ou pausá-lo).
26. **exit**: Termina o processo atual e retorna um status de saída.
## Funções relacionadas a diretórios e arquivos:
27. **getcwd**: Obtém o diretório de trabalho atual.
28. **chdir**: Altera o diretório de trabalho atual.
29. **stat**: Obtém informações sobre um arquivo, como tamanho e permissões.
30. **lstat**: Similar a stat, mas obtém informações sobre links simbólicos.
31. **fstat**: Obtém informações sobre um arquivo descrito por um descritor de arquivo.
32. **unlink**: Remove um arquivo.
32. **execve**: Substitui o processo atual por um novo processo executando o programa especificado.
32. **dup**: Duplica um descritor de arquivo.
33. **dup2**: Duplica um descritor de arquivo para um descritor específico.
34. **pipe**: Cria um pipe, que permite a comunicação entre dois processos.
35. **opendir**: Abre um diretório para leitura.
36. **readdir**: Lê a próxima entrada em um diretório aberto.
37. **closedir**: Fecha um diretório aberto.
## Funções para tratamento de erros e sinais:
38. **strerror**: Retorna uma mensagem de erro legível para um código de erro.
39. **perror**: Imprime uma mensagem de erro baseada no valor atual de errno.
## Funções relacionadas a terminais:
40. **isatty**: Verifica se um descritor de arquivo refere-se a um terminal.
41. **ttyname**: Retorna o nome do arquivo associado ao descritor de terminal.
42. **ttyslot**: Retorna o número do slot de terminal associado ao processo.
43. **ioctl**: Controla dispositivos de I/O, como configurar propriedades do terminal.
## Funções relacionadas a variáveis de ambiente e terminais:
44. **getenv**: Obtém o valor de uma variável de ambiente.
45. **tcsetattr**: Define os atributos do terminal.
46. **tcgetattr**: Obtém os atributos atuais do terminal.
## Funções da biblioteca termcap (para controle de terminais):
47. **tgetent**: Carrega as informações do terminal a partir do banco de dados termcap.
48. **tgetflag**: Obtém o valor de uma flag no banco de dados termcap.
49. **tgetnum**: Obtém o valor numérico de uma capacidade do terminal.
50. **tgetstr**: Obtém uma string associada a uma capacidade do terminal.
51. **tgoto**: Gera uma string de controle para mover o cursor para uma posição específica.
52. **tputs**: Envia strings de controle do terminal para executar operações como mover o cursor.
