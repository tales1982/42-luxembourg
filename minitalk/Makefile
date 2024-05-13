# Nome dos executáveis
SERVER = server
CLIENT = client

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Arquivos fonte
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Arquivos objeto
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Regras principais
all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ)

$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ)

# Regras para criar arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos compilados
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

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

