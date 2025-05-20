NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror  #-g3 -fsanitize=address

SRC = src/signal.c src/main.c src/lexer.c src/parser.c src/syntax_error.c src/expand.c \
	src/handel_pipe.c src/utills_v2.c src/utills_v1.c src/utills_v0.c src/redirctions.c \
	builtins/ft_unset.c builtins/bultins_parsing.c builtins/ft_cd.c builtins/ft_echo.c \
	builtins/ft_env.c builtins/ft_exit.c builtins/ft_export.c builtins/ft_pwd.c

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all