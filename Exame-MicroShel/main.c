#include "microshel.h"
#include <string.h>

int main(void) {
    char *input;
    char **args;
    t_command cmd;

    while (1) {
        /* Exibe o prompt */
        printf(PROMPT);

        /* Lê a entrada do usuário */
        input = read_input();
        if (!input)
            break;

        /* Remove o caractere de nova linha, se presente */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = '\0';

        /* Separa os argumentos da linha digitada */
        args = parse_input(input);
        free(input);

        /* Se não houver comando, continua o loop */
        if (args[0] == NULL) {
            free(args);
            continue;
        }

        /* Se o comando for "exit", finaliza o shell */
        if (strcmp(args[0], "exit") == 0) {
            free_command(&(t_command){.args = args});
            break;
        }

        /* Prepara a estrutura de comando */
        cmd.args = args;
        cmd.path = NULL; /* Não usamos um caminho fixo, o execvp usará a variável PATH */

        /* Executa o comando */
        if (execute_command(&cmd) == -1) {
            free_command(&cmd);
            break;
        }
        free_command(&cmd);
    }
    return 0;
}
