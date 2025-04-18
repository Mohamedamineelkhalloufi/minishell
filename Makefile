NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror  #-g3 -fsanitize=address

SRC = main.c lexer.c parser.c syntax_error.c  handel_pipe.c \
	redirctions.c utills.c

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline libft/libft.a -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
