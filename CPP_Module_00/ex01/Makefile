# Nome do executável
NAME = PhoneBook

# Compilador e flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CPPFLAGS = -Iinclude  # Adiciona o diretório 'include' para arquivos de cabeçalho

# Diretório dos arquivos
SRCDIR = src

# Arquivos
SRCS = $(SRCDIR)/PhoneBook.cpp \
       $(SRCDIR)/Contact.cpp \
       $(SRCDIR)/main.cpp
OBJS = $(SRCS:.cpp=.o)

# Regras
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJS)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Phony para evitar conflito com arquivos de mesmo nome
.PHONY: all clean fclean re
