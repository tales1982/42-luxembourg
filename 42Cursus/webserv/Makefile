NAME      := webserv
CXX       := c++
CXXFLAGS  := -Wall -Wextra -Werror -std=c++98
INCS      := -Iinclude

SRC_DIR   := src
OBJ_DIR   := OBJ
PROGRESS  := scripts/progress.sh
COUNT_FILE:= $(OBJ_DIR)/.count

SRCS := \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/Config.cpp \
	$(SRC_DIR)/Server.cpp \
	$(SRC_DIR)/Http.cpp \
	$(SRC_DIR)/Router.cpp \
	$(SRC_DIR)/Utils.cpp \
	$(SRC_DIR)/AutoIndex.cpp \
	$(SRC_DIR)/CGI.cpp \
	$(SRC_DIR)/CGIManager.cpp

OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
TOTAL := $(words $(SRCS))

.PHONY: all clean fclean re prep

all: prep $(NAME)

$(NAME): $(OBJS)
	@printf "\n\033[1;34m[Link]\033[0m -> %s\n" "$@"
	@$(CXX) $(CXXFLAGS) $(INCS) -o $@ $(OBJS)
	@printf "\033[1;32m✓ Build finalizado:\033[0m %s\n" "$@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(INCS) -MMD -MP -c $< -o $@
	@count=$$(($$(cat $(COUNT_FILE)) + 1)); echo $$count > $(COUNT_FILE); \
	bash $(PROGRESS) $$count $(TOTAL) "[$(@F)]"

-include $(DEPS)

prep:
	@mkdir -p $(OBJ_DIR) $(dir $(PROGRESS))
	@echo 0 > $(COUNT_FILE)
	@printf "\033[1;34mCompilando %d arquivos...\033[0m\n" $(TOTAL)

clean:
	@printf "\033[1;33m[Limpando objetos]\033[0m %s\n" "$(OBJ_DIR)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "\033[1;33m[Limpando binário]\033[0m %s\n" "$(NAME)"
	@rm -f $(NAME)

re: fclean all
