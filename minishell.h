
#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <time.h>
#include <sys/wait.h>
# define RESET " \e[00m"
int g_exit_status;

typedef struct s_redi
{
    char *file_num;
    int type;
    struct s_redi *next;
}t_redi;

typedef struct s_unset
{
    char *key;
}   t_unset;

typedef struct s_exit
{
    int status;
    int pid;
}t_exit;

typedef struct s_export
{
    int flag; // if flag has 1 u mean export hasn't any key-value (empty arg), 0 otherwisse
    int append; // if a="13" and command is export a+="36" must be add 36 to 13 for get a="1337" 
    char *key;
    char *value;
}t_export;

typedef struct s_echo
{
    int new_line; // we use this in echo if we have echo with the option -n please assign 1 otherwise 0;
    char *echo_str;
    /* please store all of string with echo: 
        example : echo "hello" "world" "amine" "dash"
         struct must be like :
            cmd = {"echo", NULL};
            new_line = 0;
            echo_str = "hello world amine dash";
            !!! to sumlit bash add space between strings!!!   
    */
}t_echo;

typedef struct s_node
{
    char **cmd;//arry of string has command and options like : {"ls", "-l", "-a"}
    char **my_envp;//copie of orginal envp
    t_redi *file;// linkedlist of redirctions (< , << , > , >>)
    t_export *info; //if u have export must be add deatils here
    t_echo *echo_info; //if u have echo must be add details here
    t_unset *unset_info;
    t_exit *exit_info;
    struct s_node *next;
}t_node;

/*-----------------------------------------_syntax_erroe_------------------------------------*/

int check_split(char *line, int i, char q);
int d_quote(char *line, int dquote, int quote, int i);
int check_pipe(char *line);
int if_check_pipe(char *line, int i, char q);

/*--------------------------------------------_lexer_----------------------------------------*/

int lexer(t_node **test, char *s_line ,char **p_line);
int len_forma(char *line);
char *fix_line(char *line);
int check_redirections(char **p_line);
int num_cmd(char **p_line);

/*--------------------------------------------_lexer_----------------------------------------*/

t_redi *creat_file(t_redi *head, char *file_num, char *check, int p);
t_node *init_node(int num_cmd);
t_node *creat_node(t_node *head, char **cmd, int num_cmd);


/*--------------------------------------------_exct_ft_--------------------------------------*/

void	error_exit(const char *msg); // display error msg asd exit
char	*resolve_path(char *command, char **envp); //search for internal command (ls, cat, etc..)in envp(PATH) 
void	pipe_hundel(t_node *cmd,char **envp); // handel one command and multi command like (ls -l) and (ls -l | grep "a" | wc -l) by using fork, pipe and ..etc!
void	ft_redirect(t_redi *redir); // handel reirectins (<, >, <<, >>) like (ls -l >> test.txt| wc -l) by using dup2, pipe, open and ..etc!
int		get_num_commands(t_node *cmd); // count of nodes cause any node has one commnde
char    *get_env_value(const char *key, char **envp);
void    ft_sort(t_node *cmd);

/*--------------------------------------------_builtins_--------------------------------------*/

int ft_cd(t_node *cmd);
int	ft_echo(t_node *cmd);
int ft_env(t_node *cmd);
int ft_exit(t_node *cmd);
int ft_export(t_node *cmd);
int ft_pwd(char **envp);
int ft_unset(t_node *cmd);
//helper :
int	is_builtin(t_node *cmd);
int exec_builtins(t_node *cmd);
char	**ft_split_a(char const *s, char const *delimiter);
void free_split(char **split);
int init_export_info(t_node *cmd);
void one_com(t_node *cmd,int num_commands,pid_t pid,int status);
void multi_com(t_node *cmd,int num_commands,pid_t pid, int prev_pipe,int pipefds,int i);
#endif