# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tales <tales@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 22:08:58 by tales             #+#    #+#              #
#    Updated: 2024/12/05 22:12:44 by tales            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável
NAME = ClapTrap

# Compilador
CXX = g++

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
