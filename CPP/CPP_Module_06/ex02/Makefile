# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 17:56:26 by tales             #+#    #+#              #
#    Updated: 2025/05/13 11:40:44 by tlima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Nome do executável
NAME = identify

# Compilador e flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iinclude

# Diretórios
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Fontes
SRC = $(SRCDIR)/main.cpp $(SRCDIR)/functions.cpp

# Objetos
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Regra principal
all: $(NAME)

# Compilação final
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

# Compilar arquivos .cpp para .o no diretório obj/
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criar diretório obj se necessário
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Limpar objetos
clean:
	rm -rf $(OBJDIR)

# Limpar tudo
fclean: clean
	rm -f $(NAME)

# Reconstruir
re: fclean all

.PHONY: all clean fclean re
