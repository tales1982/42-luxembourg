# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 15:28:17 by sanweber          #+#    #+#              #
#    Updated: 2024/12/05 13:49:21 by tlima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = point 

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Arquivos de cabeçalho e código fonte
HEADERS = Fixed.hpp Point.hpp
SOURCES = main.cpp Fixed.cpp Point.cpp bsp.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Regras principais
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para compilar arquivos .cpp em .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos .o e do executável
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(TARGET)

# Regra para rodar o programa
run: all
	./$(TARGET)
