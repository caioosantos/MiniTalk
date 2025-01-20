# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SERVER_SRC = server.c
CLIENT_SRC = client.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_BIN = server
CLIENT_BIN = client
LIBFT_DIR = libft
PRINTF_DIR = printf
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

# Regras principais
all: $(LIBFT) $(PRINTF) $(SERVER_BIN) $(CLIENT_BIN)

# Compilação do servidor
$(SERVER_BIN): $(SERVER_OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação do cliente
$(CLIENT_BIN): $(CLIENT_OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação dos objetos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compilação da libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compilação da ft_printf
$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

# Limpeza
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(PRINTF_DIR)

fclean: clean
	rm -f $(SERVER_BIN) $(CLIENT_BIN)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean re
