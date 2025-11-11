# **************************************************************************** #
#                                   MAKEFILE                                   #
# **************************************************************************** #

NAME        = bigint
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98
AR          = ar rcs
RM          = rm -f

SRCS        = bigint.cpp main.cpp
OBJS        = $(SRCS:.cpp=.o)
DEPS        = bigint.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
