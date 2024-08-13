# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tales <tales@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/11 22:14:52 by tales             #+#    #+#              #
#    Updated: 2024/08/13 17:53:04 by tales            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRC		= philo.c \
		launch.c \
		msg_error.c \
		start.c \
		utils.c  \
		
OBJS	= $(SRC:.c=.o)

# Compiler options
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g

# Implicit rule for compiling .c to .o
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	
# Rule to link the executable
$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

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
