CC := cc
CFLAGS := -Wall -Wextra -Werror

AR := ar
ARFLAGS := rcs

INCLUDE_DIR := include
SRC_DIRS := src
BONUS_DIRS := bonus
LIBFTDIR := ./libft

LIBFT := $(LIBFTDIR)/libft.a
INCLUDE := $(INCLUDE_DIR)/minitalk.h
INCLUDE_BONUS := $(INCLUDE_DIR)/minitalk_bonus.h
CLIENT_SRC_FILES := client.c str_to_bits.c
CLIENT_SRC_FILES := $(addprefix $(SRC_DIRS)/,$(CLIENT_SRC_FILES))
SERVER_SRC_FILES := server.c
SERVER_SRC_FILES := $(addprefix $(SRC_DIRS)/,$(SERVER_SRC_FILES))
CLIENT_BONUS_FILES := client_bonus.c str_to_bits_bonus.c
CLIENT_BONUS_FILES := $(addprefix $(BONUS_DIRS)/,$(CLIENT_BONUS_FILES))
SERVER_BONUS_FILES := server_bonus.c
SERVER_BONUS_FILES := $(addprefix $(BONUS_DIRS)/,$(SERVER_BONUS_FILES))

NAME := client
NAME_2 := server
NAME_BONUS:= client_bonus
NAME_BONUS_2 := server_bonus

all: lib $(NAME) $(NAME_2)

$(NAME): $(CLIENT_SRC_FILES) $(INCLUDE) $(LIBFT)
	@echo "\033[0;34mCompiling \033[1;34m$(NAME) ...\033[0m"
	@$(CC) $(CFLAGS) $(CLIENT_SRC_FILES) $(LIBFT) -o $@
	@echo "\033[1;32m$(NAME) \033[0;32mhas been compiled\033[0m"

$(NAME_2): $(SERVER_SRC_FILES) $(INCLUDE) $(LIBFT)
	@echo "\033[0;34mCompiling \033[1;34m$(NAME_2) ...\033[0m"
	@$(CC) $(CFLAGS) $(SERVER_SRC_FILES) $(LIBFT) -o $@
	@echo "\033[1;32m$(NAME_2) \033[0;32mhas been compiled\033[0m"

bonus: lib $(NAME_BONUS) $(NAME_BONUS_2)

$(NAME_BONUS): $(CLIENT_BONUS_FILES) $(INCLUDE_BONUS) $(LIBFT)
	@echo "\033[0;34mCompiling \033[1;34m$(NAME_BONUS) ...\033[0m"
	@$(CC) $(CFLAGS) $(CLIENT_BONUS_FILES) $(LIBFT) -o $@
	@echo "\033[1;32m$(NAME_BONUS) \033[0;32mhas been compiled\033[0m"

$(NAME_BONUS_2): $(SERVER_BONUS_FILES) $(INCLUDE_BONUS) $(LIBFT)
	@echo "\033[0;34mCompiling \033[1;34m$(NAME_BONUS_2) ...\033[0m"
	@$(CC) $(CFLAGS) $(SERVER_BONUS_FILES) $(LIBFT) -o $@
	@echo "\033[1;32m$(NAME_BONUS_2) \033[0;32mhas been compiled\033[0m"

$(LIBFT):
	# @echo "\033[0;34mCompiling \033[1;34mlibft.a ..."
	# @$(MAKE) -C $(LIBFTDIR)
	# @echo "\033[1;32mlibft.a \033[0;32mhas been compiled"

lib:
	@$(MAKE) -C $(LIBFTDIR)

clean:
	@$(MAKE) clean -C $(LIBFTDIR) 
	@echo "\033[0;31mCleaning\033[0m"
	@echo "\033[0;32mDone\033[0m"

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR) 
	@rm -f $(NAME) $(NAME_2) $(NAME_BONUS_2) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus lib