#include "microshell.h"

void ft_put_str(char *str, char *arg)
{
    while(*str)
        write(2, str++, 1);
    if(arg)
        while(*arg)
            write(2, arg++, 1);
    write(2, "\n", 1);
}

void ft_execute(char **argv, int i, int tmp, char **env)
{
    argv[i] = NULL;
    dup2(tmp, STDIN_FILENO);
    close(tmp);
    execve(argv[0], argv, env);
    ft_put_str("error: cannot execute ", argv[0]);
    exit(1);
}

int main(int argc, char **argv, char **env)
{
    int i = 0;
    int tmp;
    tmp = dup(STDERR_FILENO);
    int fd[2];
    int pid;

    (void)argc;
    while (argv[i] && argv[i + 1])
    {
        argv = &argv[i +1];
        i = 0;
        
        while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
        
        if(strcmp(argv[0], "cd") == 0)
        {
            if(i != 2)
                ft_put_str("error: cd: bad arguments", NULL);
            else
                ft_put_str("error: cd: cannot change directory to ", argv[1]);
        }
        else if(i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
        {
            if((pid = fork()) == 0)
                ft_execute(argv, i, tmp, env);
            else
            {
                close(tmp);
                waitpid(pid, NULL, 0);
                tmp = dup(STDIN_FILENO);
            }
        }
        else if(i != 0 && strcmp(argv[i], "|") == 0 )
        {
            pipe(fd);
            if((pid = fork()) == 0)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                ft_execute(argv, i, tmp, env);
            }
            else
            {
                close(fd[1]);
                close(tmp);
                tmp = fd[0];
                waitpid(pid, NULL, 0);
            }

        }
    }
    close(tmp);
    return(0);
}