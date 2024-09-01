# Nome do executável
NAME = c00

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Diretórios
SRCDIR = .
INCDIR = .
OBJDIR = obj

# Arquivos fonte e objetos
SRC = $(SRCDIR)/main.c \
      $(SRCDIR)/ex00/ft_putchar.c \
      $(SRCDIR)/ex01/ft_print_alphabet.c \
	  $(SRCDIR)/ex02/ft_print_reverse_alphabet.c \
	  $(SRCDIR)/ex03/ft_print_numbers.c \
	  $(SRCDIR)/ex04/ft_is_negative.c \
	  $(SRCDIR)/ex05/ft_print_comb.c \
	  $(SRCDIR)/ex06/ft_print_comb2.c \
	  $(SRCDIR)/ex07/ft_putnbr.c \
	  $(SRCDIR)/ex08/ft_print_combn.c \

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
