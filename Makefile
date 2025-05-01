NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror  #-g3 -fsanitize=address

SRC = src/main.c src/lexer.c src/parser.c src/syntax_error.c src/expand.c

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