
#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct s_redi
{
    char *file_num;
    int type;
    struct s_redi *next;
}t_redi;

typedef struct s_node
{
    char **cmd;
    t_redi *file;
    struct s_node *next;
}t_node;

int lexer(t_node **test, char *s_line ,char **p_line);
t_redi *creat_file(t_redi *head, char *file_num, char *check);
t_node *init_node(int num_cmd);
t_node *creat_node(t_node *head, char **cmd, int num_cmd);
int check_split(char *line, int i, char q);
int d_quote(char *line, int dquote, int quote, int i);
int check_pipe(char *line);
int if_check_pipe(char *line, int i, char q);
char *fix_line(char *line);
int len_forma(char *line);
int check_redirections(char **p_line);
int num_cmd(char **p_line);

#endif