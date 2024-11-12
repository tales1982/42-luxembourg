# Nome do executável
NAME = megaphone

# Compilador e flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Arquivos
SRCS = megaphone.cpp
OBJS = $(SRCS:.cpp=.o)

# Regras
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Phony para evitar conflito com arquivos de mesmo nome
.PHONY: all clean fclean re
