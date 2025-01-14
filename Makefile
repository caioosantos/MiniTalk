# 📝 Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SERVER = server
CLIENT = client

PRINTF_DIR = printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

# 🛠️ Regras Principais
all:
	@$(MAKE) -C $(PRINTF_DIR) all
	@$(CC) $(CFLAGS) $(SRCS_SERVER) $(PRINTF_LIB) -o $(SERVER)
	@$(CC) $(CFLAGS) $(SRCS_CLIENT) $(PRINTF_LIB) -o $(CLIENT)
	@echo "✅ Server e Client compilados com sucesso!"

# 🧹 Limpeza
clean:
	@$(MAKE) -C $(PRINTF_DIR) clean
	@rm -f $(SERVER)
	@rm -f $(CLIENT)
	@echo "🧹 Objetos e binários limpos!"

fclean: clean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@echo "🗑️ Biblioteca Printf limpa!"

# 🔄 Recompilação Total
re: fclean all

# 🎁 Regra de Bônus (caso existam bônus em printf)
bonus: fclean
	@$(MAKE) -C $(PRINTF_DIR) all
	@echo "🎁 Bônus recompilado com sucesso!"

# 🚀 Execução
run_server: $(SERVER)
	@./$(SERVER)

run_client: $(CLIENT)
	@echo "🔄 Execute './client <PID> <mensagem>' para enviar uma mensagem ao server"

# 📌 Garante que comandos específicos não sejam confundidos com arquivos
.PHONY: all clean fclean re bonus run_server run_client
