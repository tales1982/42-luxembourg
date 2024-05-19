# Nome dos executáveis
SERVER = server
CLIENT = client

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Caminho para a libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Arquivos fonte
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Arquivos objeto
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Regras principais
all: $(SERVER) $(CLIENT)

# Compilar a libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Compilar o servidor com a libft
$(SERVER): $(SERVER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ) -L$(LIBFT_DIR) -lft

# Compilar o cliente com a libft
$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ) -L$(LIBFT_DIR) -lft

# Regras para criar arquivos objeto
$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

# Limpar arquivos compilados
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

# Guia rápido de uso
.PHONY: all clean fclean re help

help:
	@echo "Makefile para o projeto Minitalk"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make all      - Compila os programas server e client"
	@echo "  make clean    - Remove arquivos objeto (.o)"
	@echo "  make fclean   - Remove arquivos objeto (.o) e executáveis"
	@echo "  make re       - Recompila os programas"
	@echo "  make help     - Exibe este guia"
	@echo ""
	@echo "Uso:"
	@echo "  1. Compile o projeto: make all"
	@echo "  2. Execute o servidor: ./server"
	@echo "  3. Em outra janela do terminal, execute o cliente: ./client <PID do servidor> <mensagem>"
