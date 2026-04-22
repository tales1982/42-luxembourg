# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 22:08:58 by tales             #+#    #+#              #
#    Updated: 2024/12/09 13:17:46 by tlima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável
NAME = ClapTrap

# Compilador
CXX = c++

# Flags de compilação (garantindo o padrão C++98)
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Arquivos de origem e objetos
SRCS =	main.cpp\
		ClapTrap.cpp \
		
OBJS = $(SRCS:.cpp=.o)

# Regra padrão: compilar o executável
all: $(NAME)

# Como criar o executável
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

# Regra para compilar arquivos .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza de arquivos compilados
clean:
	rm -f $(OBJS)

# Limpeza geral (arquivos objetos e o executável)
fclean: clean
	rm -f $(NAME)

# Recompilar do zero
re: fclean all
