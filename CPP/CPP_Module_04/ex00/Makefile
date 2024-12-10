# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tales <tales@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/10 11:18:32 by tlima-de          #+#    #+#              #
#    Updated: 2024/12/10 20:05:01 by tales            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável
NAME = Polymorphisme

# Compilador
CXX = c++

# Flags de compilação (garantindo o padrão C++98)
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Arquivos de origem e objetos
SRCS =	main.cpp\
		Animal.cpp\
		Dog.cpp\
		Cat.cpp\
		WrongAnimal.cpp\
		WrongCat.cpp\
		
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
