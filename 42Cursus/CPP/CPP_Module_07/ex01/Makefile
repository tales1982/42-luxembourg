# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coder <coder@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 17:56:26 by tales             #+#    #+#              #
#    Updated: 2025/05/21 11:26:41 by coder            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável
NAME = iter

# Compilador e flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Fontes
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

# Regra principal
all: $(NAME)

# Compilação do executável
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

# Compilação dos objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa objetos
clean:
	rm -f $(OBJ)

# Limpa tudo
fclean: clean
	rm -f $(NAME)

# Reconstrói tudo
re: fclean all

.PHONY: all clean fclean re
