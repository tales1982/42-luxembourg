# Makefile estilo 42, C++98, sem dependências extras

NAME := vect2_demo
CXX  := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

SRCS := main.cpp vect2.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := vect2.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
