# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 17:56:26 by tales             #+#    #+#              #
#    Updated: 2025/05/12 12:53:08 by tlima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável
NAME = serialize

# Compilador e flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iinclude

# Diretórios
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Arquivos fontes
SRC = $(SRCDIR)/main.cpp $(SRCDIR)/Serializer.cpp


# Objetos gerados
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Regra padrão
all: $(NAME)

# Regra para compilar o executável
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

# Compilação dos arquivos .cpp para .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criar diretório obj se não existir
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Limpa os objetos
clean:
	rm -rf $(OBJDIR)

# Limpa tudo
fclean: clean
	rm -f $(NAME)

# Reconstrói tudo
re: fclean all

.PHONY: all clean fclean re