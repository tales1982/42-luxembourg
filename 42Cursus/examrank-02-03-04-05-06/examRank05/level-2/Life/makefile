# **************************************************************************** #
#                                  SETTINGS                                    #
# **************************************************************************** #

NAME = live

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# **************************************************************************** #
#                                 RULES                                        #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

