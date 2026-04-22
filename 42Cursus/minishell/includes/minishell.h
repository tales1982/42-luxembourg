/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-fif <luis-fif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:04:45 by anolivei          #+#    #+#             */
/*   Updated: 2024/11/04 16:29:48 by luis-fif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define D_QUOTE '\"'
# define QUOTE '\''
# define D_QUOTE_S "\""
# define QUOTE_S "\'"

# define ERROR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERROR_DIR "No such file or directory\n"
# define ERROR_HOME "minishell: cd: HOME not set\n"
# define ERROR_CMD "command not found\n"

typedef struct s_struct	t_tiny;
typedef struct s_env	t_env;
typedef struct s_split	t_split;
typedef struct s_token	t_token;

struct					s_env
{
	char				**env;
	int					len;
	char				**key;
	char				**content;
	int					index;
};

struct					s_split
{
	int					n_comand;
	int					ini;
	int					len;
	int					q;
	int					qtt_pipe;
};

struct					s_token
{
	char				*to_print;
	char				*to_exec;
	char				quote;
	char				*end;
	char				*new;
	int					i;
	int					init;
	int					len;
	int					posic;
};

struct					s_struct
{
	int					last_exit_cmd;
	bool				is_builtin;
	bool				has_flag;
	int					is_append;
	int					last_redir;
	int					out_fd;
	int					in_fd;
	int					num_tokens;
	int					c;
	char				quote;
	char				*line;
	char				*line_read;
	char				*name_file;
	char				*error_name_file;
	char				*home;
	char				*commands[50];
	char				*token_aux;
	char				**tokens;
	char				**path;
	t_env				env_aux;
	t_env				env;
	t_split				split;
	t_token				token;
};

void					init_1(t_tiny *tiny);
void					init_environment(t_tiny *tiny);
void					init_tiny_env(t_tiny *tiny);
int						fix(t_tiny *tiny, char c, char *aux, int nbr);
void					is_builtin(char *cmd, t_tiny *tiny);
void					run_builtin(t_tiny *tiny);
char					*find_env(t_tiny *tiny, char *needle);
int						ft_cd(t_tiny *tiny);
bool					there_is_home(t_tiny *tiny);
void					ft_echo(t_tiny *tiny);
int						init_echo(t_tiny *tiny, int n);
void					print_echo(t_tiny *tiny, char *tiny_tokens_i);
void					ft_env(t_tiny *tiny);
void					create_env(t_tiny *tiny, char **my_env);
void					len_env(t_tiny *tiny);
void					init_tiny_env(t_tiny *tiny);
void					ft_exit(t_tiny *tiny);
void					free_line(char *line_read);
void					free_char_array(char **array);
void					free_char_array2(char **array);
void					ft_export(t_tiny *tiny);
void					verify_if_env_exists(t_tiny *tiny, char **env_aux,
							int i);
void					add_env(t_tiny *tiny, char *new_key, char *new_content);
void					ft_pwd(t_tiny *tiny);
char					*get_cwd_buf(void);
void					ft_unset(t_tiny *tiny);
void					rm_env(t_tiny *tiny);
void					alloc_env_aux(t_tiny *tiny);
int						init_path(t_tiny *tiny);
int						main(void);
void					init(t_tiny *tiny);
void					redirect_in(t_tiny *tiny, int j, char *aux);
char					**double_redir(t_tiny *tiny, char **file, int j);
void					read_until(char *end);
char					*new_comman(int i, char **str);
void					redirect_out(t_tiny *tiny, int j);
void					simple_redir_out(t_tiny *tiny, int j, int flags);
int						find_char(char *string, char needle);
int						file_descriptor_handler(int in, int out);
void					spaces_in_pipe(t_tiny *tiny, int i, char *command);
void					execve_error(t_tiny *tiny);
void					run_commands(t_tiny *tiny);
void					run_commands_aux(t_tiny *tiny);
void					action(t_tiny *tiny);
void					exec_process(t_tiny *tiny, int in, int out);
void					ft_execve_pipe(t_tiny *tiny, int i, char *command);
void					run_signals(int sig);
void					restore_prompt(int sig);
void					ctrl_c(int sig);
void					back_slash(int sig);
void					split_cmd(t_tiny *tiny, char *in, int i);
void					init_split_tiny(t_tiny *tiny);
char					*clean_spaces(char *in);
int						count_pipe(t_tiny *tiny, char *in, int i);
void					tokenizer(t_tiny *tiny);
void					simple_quotes(t_tiny *tiny, char *in, int i, int c);
int						tokent(char *string, char needle);
void					get_home_sign(t_tiny *tiny, t_token *tk);
void					get_dollar_sign(t_tiny *tiny, t_token *tk);
t_token					*init_tk(void);
void					free_tk(t_token *tk);
void					finish_tokenizer(t_tiny *tiny, t_token *tk);
int						count_digits(int n);
int						power(int n_digits);
char					*ft_itoa(int n);
char					*substr_ft(char const *s, unsigned int start,
							size_t len);
int						ft_isset(char c, char const *set);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_putendl_fd(char *s, int fd);
int						count_words(const char *s, char c);
char					*string(const char *s, int init, int end);
char					**ft_split(char const *s, char c);
void					ft_putstr_fd(char *s, int fd);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlen(const char *str);
size_t					ft_strlcpy(char *restrict dst, const char *restrict src,
							size_t dstsize);
char					*ft_strdup(const char *s1);
void					ft_putnbr_fd(int n, int fd);
void					ft_putchar_fd(char c, int fd);
void					print_header(void);
void					ft_print(char *message);

#endif
