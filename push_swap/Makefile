# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tales <tales@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 17:34:59 by tlima-de          #+#    #+#              #
#    Updated: 2024/06/22 15:43:24 by tales            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap
SRC = src/error_handling.c \
      src/index.c \
      src/ps_check_dup.c \
      src/ps_initstack.c \
      src/ps_stackclear.c \
      src/push_swap.c \
      src/push.c \
      src/radix.c \
      src/reverse.c \
      src/rotate.c \
      src/simple_sort_utils.c \
      src/stack_operations.c \
      src/swap.c \
      utils/free_split.c \
      utils/ft_atoi.c \
      utils/ft_atol.c \
      utils/ft_putstr_fd.c \
      utils/ft_split.c \
      utils/ft_strlen.c \
      utils/is_number.c \
      utils/lst_utils.c \


OBJS		= $(SRC:.c=.o)

# Compiler options
CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -g

# Implicit rule for compiling .c to .o
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
# Rule to link the executable
$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

# Default rule
all: $(NAME)

# Roda o valgrind
check: $(NAME)
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(NAME); true


# Rule for cleaning up
fclean:
	@$(RM) $(NAME) $(OBJS)

# Rule to re-make everything
re: fclean all
