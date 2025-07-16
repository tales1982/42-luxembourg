# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: 42Webserv                                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 10:30:00 by tales             #+#    #+#              #
#    Updated: 2025/07/16 10:30:00 by tales            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = webserv
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98

# Diretórios
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include

# Subpastas organizadas
SRC_CONFIG  = $(SRC_DIR)/config
SRC_SERVER  = $(SRC_DIR)/server

# Fontes
SRCS        = \
	$(SRC_DIR)/main.cpp \
	$(SRC_CONFIG)/ConfigParser.cpp \
	$(SRC_SERVER)/Server.cpp \
	$(SRC_SERVER)/RequestHandler.cpp \
	$(SRC_SERVER)/ResponseBuilder.cpp

# Objetos
OBJS        = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Includes
INCLUDES    = -I$(INC_DIR) -I$(INC_DIR)/config -I$(INC_DIR)/parser -I$(INC_DIR)/server

# Regras
all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Compilado com sucesso!"

# Criação dos diretórios de objetos se necessário
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Objetos removidos"

fclean: clean
	@rm -f $(NAME)
	@echo "🧹 Binário removido"

re: fclean all

.PHONY: all clean fclean re
