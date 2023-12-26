NAME = minitalk
SERVER_NAME = server
CLIENT_NAME = client
SERVER_BONUS_NAME = server_bonus
CLIENT_BONUS_NAME = client_bonus
LIBFT = libft
CC = cc
FLAGS = -Wall -Wextra -Werror
LIBFT_FLAGS = -Llibft -lft
INCLUDES = -Ilibft

SERVER_SRCS = server.c
CLIENT_SRCS = client.c
SERVER_BONUS_SRCS = server_bonus.c
CLIENT_BONUS_SRCS = client_bonus.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_BONUS_OBJS = $(SERVER_BONUS_SRCS:.c=.o)
CLIENT_BONUS_OBJS = $(CLIENT_BONUS_SRCS:.c=.o)

%.o: %.c libft/libft.a
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(SERVER_NAME) $(CLIENT_NAME) 

bonus: $(LIBFT) $(SERVER_BONUS_NAME) $(CLIENT_BONUS_NAME) 

$(SERVER_NAME): $(SERVER_OBJS)
				$(CC) $(FLAGS) $(SERVER_OBJS) -o $@ $(LIBFT_FLAGS) 

$(CLIENT_NAME): ${CLIENT_OBJS}
				$(CC) $(FLAGS) $(CLIENT_OBJS) -o $@ $(LIBFT_FLAGS) 

$(SERVER_BONUS_NAME): $(SERVER_BONUS_OBJS)
				$(CC) $(FLAGS) $(SERVER_BONUS_OBJS) -o $(SERVER_BONUS_NAME) $(LIBFT_FLAGS)

$(CLIENT_BONUS_NAME): ${CLIENT_BONUS_OBJS}
				$(CC) $(FLAGS) $(CLIENT_BONUS_OBJS) -o $(CLIENT_BONUS_NAME) $(LIBFT_FLAGS)

$(LIBFT):
	@make -C libft

clean:
	@$(RM) -f $(SERVER_OBJS) $(CLIENT_OBJS)
	@$(RM) -f $(SERVER_BONUS_OBJS) $(CLIENT_BONUS_OBJS)
	@$(MAKE) clean -C libft
	@echo "Cleaned minitalk objects."

fclean: clean
	@$(MAKE) fclean -C libft
	@$(RM) -rf $(SERVER_NAME) $(CLIENT_NAME)
	@$(RM) -rf $(SERVER_BONUS_NAME) $(CLIENT_BONUS_NAME)
	@echo "Cleaned client and server executables."

re: fclean all

.PHONY: all clean fclean libft






