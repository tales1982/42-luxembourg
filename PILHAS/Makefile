SRC     = main.c \
          ft_pop.c \
          ft_push.c \
          ft_estaVazia.c \
          ft_imprimirPilha.c \
          ft_inicializarPilha.c

NAME    = pilha_exec
OBJS    = $(SRC:.c=.o)
CC      = cc
RM      = rm -f
DEBUG   = -g
CFLAGS  = -Wall -Wextra -Werror

.c.o:
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
