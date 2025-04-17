NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror  #-g3 -fsanitize=address

SRC = src/main.c src/lexer.c src/parser.c src/syntax_error.c

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline libft/libft.a -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all