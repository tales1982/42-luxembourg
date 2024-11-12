# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlima-de <tlima-de@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 13:20:51 by tlima-de          #+#    #+#              #
#    Updated: 2024/11/11 13:20:52 by tlima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C++ = c++
C++_FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
INFILES = 	tests.cpp\
			Account.cpp\

OBJFILES = $(INFILES:.cpp=.o)

NAME = Bank

all: $(NAME)

$(NAME):$(OBJFILES)
	$(C++) $(C++_FLAGS) $(OBJFILES) -o $(NAME) 

%.o: %.cpp
	$(C++) $(C++_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re