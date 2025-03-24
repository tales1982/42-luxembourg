#ifndef __MICROSHELL_H__
# define __MICROSHELL_H__

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>


int	ft_strlen(char *str);
void exit_fatal(void);
int exec_cd(char **av, int count);
int exec_cmd(char **av, int count, char **env, int tmp);

#endif
