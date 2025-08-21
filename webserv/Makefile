NAME = webserv
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
INCS = -Iinclude

SRCS = \
	src/main.cpp \
	src/Config.cpp \
	src/Server.cpp \
	src/Http.cpp \
	src/Router.cpp \
	src/Utils.cpp \
	src/AutoIndex.cpp \
	src/CGI.cpp \
	src/CGIManager.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
