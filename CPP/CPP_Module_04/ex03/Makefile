# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tales <tales@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 14:13:36 by sanweber          #+#    #+#              #
#    Updated: 2025/02/24 10:40:16 by tales            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = materia

# Compilador e flags
CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Arquivos fonte
SRCS = main.cpp \
       AMateria.cpp \
       Ice.cpp \
       Cure.cpp \
       Character.cpp \
       MateriaSource.cpp

# Arquivos objeto
OBJS = $(SRCS:.cpp=.o)

# Regra padrão
all: $(NAME)

# Regra para criar o executável
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

# Regra para compilar os arquivos fonte em objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar os arquivos objeto
clean:
	rm -f $(OBJS)

# Limpar tudo (objetos e executável)
fclean: clean
	rm -f $(NAME)

# Recompilar do zero
re: fclean all

