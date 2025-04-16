# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 15:47:31 by tales             #+#    #+#              #
#    Updated: 2025/04/16 09:55:38 by tlima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = aform

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iinclude

SRCDIR = src
INCDIR = include
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

all: $(NAME)

# Cria o executável a partir dos objetos
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

# Garante que o diretório obj/ exista antes de compilar
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria o diretório obj/ se não existir
$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
