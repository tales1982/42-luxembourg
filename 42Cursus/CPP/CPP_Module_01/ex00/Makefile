# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tales <tales@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 12:59:14 by tlima-de          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/12/01 10:12:20 by tales            ###   ########.fr        #
=======
#    Updated: 2024/11/22 20:04:59 by tales            ###   ########.fr        #
>>>>>>> b21490d1858790a17896a3ac2af906c3de60d84e
#                                                                              #
# **************************************************************************** #

C++ = c++
C++_FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
INFILES = 	main.cpp\
			Zombie.cpp\
			newZombie.cpp\
<<<<<<< HEAD
			randomChump.cpp\
=======
			randomChump.cpp
>>>>>>> b21490d1858790a17896a3ac2af906c3de60d84e

OBJFILES = $(INFILES:.cpp=.o)

NAME = BraiiiiiiinnnzzzZ

all: $(NAME)


$(NAME):$(OBJFILES)
	$(C++) $(C++_FLAGS) $(OBJFILES) -o $(NAME) 

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re