# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tales <tales@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/08 12:37:36 by tales             #+#    #+#              #
#    Updated: 2024/09/08 13:45:13 by tales            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRC		= src/exec_cmd.c \
		  src/free_resources.c \
		  src/ft_erro.c \
		  src/ft_print_ascii.c \
		  src/minishell.c \
		  src/path.c \
		  src/signal_handler.c \
		  src/utils.c

OBJS	= $(SRC:.c=.o)

# Compiler options
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g
LIBS	= -lreadline

# Implicit rule for compiling .c to .o
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to link the executable
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)

# Default rule
all: $(NAME)

# Run valgrind
check: $(NAME)
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(NAME); true

# Rule for cleaning up object files
clean:
	@$(RM) $(OBJS)

# Rule for cleaning up everything
fclean: clean
	@$(RM) $(NAME)

# Rule to re-make everything
re: fclean all
