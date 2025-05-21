# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coder <coder@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 11:27:22 by coder             #+#    #+#              #
#    Updated: 2025/05/21 11:27:23 by coder            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Nome do executável
NAME = array

# Arquivos fonte
SRC = main.cpp

# Regra padrão
all: $(NAME)

# Regra para compilar o executável
$(NAME): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

# Regra para limpar arquivos gerados
clean:
	rm -f $(NAME)

# Regra para recompilar tudo
fclean: clean

# Regra para recompilar tudo do zero
re: fclean all

# Indica que os alvos não são arquivos
.PHONY: all clean fclean re
