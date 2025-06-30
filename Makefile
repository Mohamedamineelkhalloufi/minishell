NAME = minishell

CC = cc

CFLAGS =-Wall -Wextra -Werror  -g3  #-fsanitize=address

SRC = src/signal.c src/main.c src/lexer.c src/parser.c src/syntax_error.c src/expand.c \
	src/handel_pipe.c src/utills_v2.c src/utills_v1.c src/utills_v0.c src/redirctions.c \
	builtins/ft_unset.c builtins/bultins_parsing.c builtins/ft_cd.c builtins/ft_echo.c \
	builtins/ft_env.c builtins/ft_exit.c builtins/ft_export.c builtins/ft_pwd.c \
	builtins/cd_utills.c builtins/export_utils.c src/utills_v3.c src/utills_v4.c \
	src/utills_v5.c src/pipe_utils.c src/pipe_utils_2.c src/here_doc_utils.c builtins/utills.c \
	src/utills_v6.c src/utills_v7.c 

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)
	@printf "\033[32m[OK]\033[0m $(NAME) created!\n"

$(LIBFT):
	@make -C libft

clean:
	@make -C libft clean
	@rm -rf $(OBJ)
	@printf "\033[32m[OK]\033[0m clean\n"


fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)
	@printf "\033[32m[OK]\033[0m fclean\n"

re: fclean all