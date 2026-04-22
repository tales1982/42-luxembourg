# **************************************************************************** #
#                                   Makefile                                   #
# **************************************************************************** #

NAME     := polyset
CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -I.

SRC := \
	main.cpp \
	array_bag.cpp \
	tree_bag.cpp \
	searchable_array_bag.cpp \
	searchable_tree_bag.cpp \
	set.cpp

OBJ := $(SRC:.cpp=.o)

# --------------------------------- Rules ------------------------------------ #
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

