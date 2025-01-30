# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tales <tales@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/05 18:38:19 by tlima-de          #+#    #+#              #
#    Updated: 2025/01/30 19:43:49 by tales            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Paths and libraries
LIBFT_PATH       = ./lib/libft
LIBFT            = $(LIBFT_PATH)/libft.a

MINILIBX_PATH    = ./lib/minilibx-linux
MINILIBX         = $(MINILIBX_PATH)/libmlx.a

SOURCES_FILES    = so_long.c \
					src/close_window.c \
					src/draw_map.c \
					src/draw_exit.c \
					src/key_event.c \
					src/load_map.c \
					src/copy_image_part.c \
					src/key_event_player.c \
					src/free_resources.c \
					src/image_loaders.c \
					src/game_initializers.c \

OBJS             = $(SOURCES_FILES:.c=.o)

# Compiler options
CC               = cc
RM               = rm -f
CFLAGS           = -Wall -Wextra -Werror -g -I $(LIBFT_PATH) -I $(MINILIBX_PATH)

# Executable name
NAME             = so_long

# Map file
MAP_FILE         = maps/map.ber

# Implicit rule for compiling .c to .o
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to link the executable
$(NAME): $(OBJS)
	@if [ ! -d $(LIBFT_PATH) ]; then \
		echo "Directory $(LIBFT_PATH) does not exist."; \
		exit 1; \
	fi
	@if [ ! -d $(MINILIBX_PATH) ]; then \
		echo "Directory $(MINILIBX_PATH) does not exist."; \
		exit 1; \
	fi
	@$(MAKE) -C $(LIBFT_PATH)
	@$(MAKE) -C $(MINILIBX_PATH)
	@$(CC) $(OBJS) $(LIBFT) $(MINILIBX) -o $(NAME) -L$(MINILIBX_PATH) -lmlx -lXext -lX11 -lm
	@echo "Executable $(NAME) created successfully."

# Default rule
all: $(NAME)

# Run Valgrind check
check: $(NAME)
	@valgrind --leak-check=full ./$(NAME) $(MAP_FILE)

# Rule for cleaning up
fclean:
	@if [ -d $(LIBFT_PATH) ]; then \
		$(MAKE) -C $(LIBFT_PATH) fclean; \
	fi
	@$(RM) $(NAME) $(OBJS)
	@echo "Clean completed."

# Rule to re-make everything
re: fclean all

# Clean up object files only
clean:
	@$(RM) $(OBJS)
	@echo "Object files cleaned."
