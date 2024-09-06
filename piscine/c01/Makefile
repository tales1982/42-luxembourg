# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tales <tales@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/01 16:38:10 by tales             #+#    #+#              #
#    Updated: 2024/09/06 22:11:59 by tales            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável
NAME = c01

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Diretórios
SRCDIR = .
INCDIR = .
OBJDIR = obj

# Arquivos fonte e objetos
SRC = $(SRCDIR)/main.c \
      $(SRCDIR)/ex00/ft_ft.c \
      $(SRCDIR)/ex01/ft_ultimate_ft.c \
	  $(SRCDIR)/ex02/ft_swap.c \
	  $(SRCDIR)/ex03/ft_div_mod.c \
#	  $(SRCDIR)/ex04/ 
#	  $(SRCDIR)/ex05/ 
#	  $(SRCDIR)/ex06/ 
#	  $(SRCDIR)/ex07/ 
#	  $(SRCDIR)/ex08/ 

OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Regra padrão
all: $(NAME)

# Compilação do executável
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação dos arquivos .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)  # Garante que o diretório existe
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

# Limpeza dos arquivos objeto e do executável
clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

# Recompila tudo
re: fclean all

# Indica que os comandos não são arquivos reais
.PHONY: all clean fclean re
