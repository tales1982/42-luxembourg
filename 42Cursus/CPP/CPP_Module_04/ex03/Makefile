# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 13:51:19 by tlima-de          #+#    #+#              #
#    Updated: 2025/03/10 10:16:14 by tlima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = materia

# Compilador e flags
CXX = c++
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

