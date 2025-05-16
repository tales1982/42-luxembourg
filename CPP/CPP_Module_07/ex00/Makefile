# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 17:56:26 by tales             #+#    #+#              #
#    Updated: 2025/05/16 12:07:58 by tlima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 17:56:26 by tales             #+#    #+#              #
#    Updated: 2025/05/16 12:04:07 by tlima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável
NAME = whatever

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
