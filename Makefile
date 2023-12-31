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
C_OBJ_FILES := $(CLIENT_SRC_FILES:.c=.o)

SERVER_SRC_FILES := server.c
SERVER_SRC_FILES := $(addprefix $(SRC_DIRS)/,$(SERVER_SRC_FILES))
S_OBJ_FILES := $(SERVER_SRC_FILES:.c=.o)

CLIENT_BONUS_FILES := client_bonus.c str_to_bits_bonus.c
CLIENT_BONUS_FILES := $(addprefix $(BONUS_DIRS)/,$(CLIENT_BONUS_FILES))
C_OBJ_FILES_BONUS := $(CLIENT_BONUS_FILES:.c=.o)

SERVER_BONUS_FILES := server_bonus.c
SERVER_BONUS_FILES := $(addprefix $(BONUS_DIRS)/,$(SERVER_BONUS_FILES))
S_OBJ_FILES_BONUS := $(SERVER_BONUS_FILES:.c=.o)

NAME := client
NAME_2 := server
NAME_BONUS:= client_bonus
NAME_BONUS_2 := server_bonus

all: lib $(NAME) $(NAME_2)

$(NAME): $(C_OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(C_OBJ_FILES) $(LIBFT) -o $@
	@echo "\033[1;32m$(NAME) \033[0;32mhas been compiled\033[0m"

$(NAME_2): $(S_OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(S_OBJ_FILES) $(LIBFT) -o $@
	@echo "\033[1;32m$(NAME_2) \033[0;32mhas been compiled\033[0m"

$(SRC_DIRS)/%.o: $(SRC_DIRS)/%.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@


bonus: lib $(NAME_BONUS) $(NAME_BONUS_2)

$(NAME_BONUS): $(C_OBJ_FILES_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(C_OBJ_FILES_BONUS) $(LIBFT) -o $@
	@echo "\033[1;32m$(NAME_BONUS) \033[0;32mhas been compiled\033[0m"

$(NAME_BONUS_2): $(S_OBJ_FILES_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(S_OBJ_FILES_BONUS) $(LIBFT) -o $@
	@echo "\033[1;32m$(NAME_BONUS_2) \033[0;32mhas been compiled\033[0m"

$(BONUS_DIRS)/%.o: $(BONUS_DIRS)/%.c $(INCLUDE_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

lib:
	@$(MAKE) -C $(LIBFTDIR)

clean:
	@echo "\033[0;31mCleaning\033[0m"
	@$(MAKE) clean -C $(LIBFTDIR)
	@rm -f $(C_OBJ_FILES) $(S_OBJ_FILES) $(C_OBJ_FILES_BONUS) $(S_OBJ_FILES_BONUS)
	@echo "\033[0;32mDone\033[0m"

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR) 
	@rm -f $(NAME) $(NAME_2) $(NAME_BONUS_2) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus lib