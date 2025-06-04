
#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include "libft/libft.h"
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
# define RESET " \e[00m"

#ifndef GLOBALS_H
#define GLOBALS_H
extern int	g_es;
#endif

typedef struct s_redi
{
    char *file_num;
    char *heredoc_file;
    int type;
    struct s_redi *next;
}t_redi;

typedef struct s_exit
{
    int status;
    int pid;
}t_exit;

typedef struct s_garbeg_collecter
{
    void *ptr;
    struct s_garbeg_collecter *next;
}   t_garbeg_collecter;

typedef struct s_export
{
    int i_postion;
    int fg;
    int flag; // if flag has 1 u mean export hasn't any key-value (empty arg), 0 otherwisse
    int append; // if a="13" and command is export a+="36" must be add 36 to 13 for get a="1337" 
    char *key;
    char *value;
}   t_export;

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

typedef struct s_env
{
    char **my_envp;
    int env_len;
    struct s_env *next;
}   t_env;

typedef struct s_node
{
    char **cmd;//arry of string has command and options like : {"ls", "-l", "-a"}
    t_redi *file;// linkedlist of redirctions (< , << , > , >>)
    t_export *info; //if u have export must be add deatils here
    t_echo *echo_info; //if u have echo must be add details here
    t_exit *exit_info;
    struct s_node *next;
}t_node;


/*-----------------------------------------_syntax_erroe_------------------------------------*/

int check_split(char *line, int i, char q);
int d_quote(char *line, int dquote, int quote, int i);
int check_pipe(char *line);
int if_check_pipe(char *line, int i, char q);
char	*qoute_remov(char *line, char q, int i, int l);

/*--------------------------------------------_lexer_----------------------------------------*/

int lexer(t_node **test, char *s_line ,char **p_line);
int len_forma(char *line, int i, int l);
char *fix_line(char *line);
int check_redirections(char **p_line);
int num_cmd(char **p_line);
int  handle_quotes(char *line, char *new_line, int *i, int *l);
int  handle_redirects(char *line, char *new_line, int *i, int *l);

/*--------------------------------------------_parser_----------------------------------------*/

t_redi *creat_file(t_redi *head, char *file_num, char *check);
t_node *init_node(int num_cmd);
t_node *creat_node(t_node *head, char **cmd, int num_cmd);
void	process_cmd(t_node *new_node, char **cmd);
void set_redi_type(t_redi *new_redi, char *check);
void add_redi_to_list(t_redi *head, t_redi *new_redi);

/*--------------------------------------------_expand_----------------------------------------*/

char    *expand_line(char *line, int dquote, char *plus, t_env *info);
int    skip_quotes(char *line, int i, int *dquote);
int    handle_dollar(char **plus, char *line, t_env *info);
char	*expand_val(char *s, t_env *info);
char *find_end(char *start);
char	*handle_dollar_case(char *start);

/*--------------------------------------------_exct_ft_--------------------------------------*/

void	error_exit(const char *msg); // display error msg asd exit
char	*resolve_path(char *command, char **envp); //search for internal command (ls, cat, etc..)in envp(PATH) 
void    pipe_hundel(t_node *cmd,t_env *env); // handel one command and multi command like (ls -l) and (ls -l | grep "a" | wc -l) by using fork, pipe and ..etc!
int	    ft_redirect(t_redi *redir); // handel reirectins (<, >, <<, >>) like (ls -l >> test.txt| wc -l) by using dup2, pipe, open and ..etc!
int		get_num_commands(t_node *cmd); // count of nodes cause any node has one commnde
char    *get_env_value(const char *key, char **envp);
void    ft_sort(t_env *cmd);

/*--------------------------------------------_builtins_--------------------------------------*/

int ft_cd(t_node *cmd,t_env *env);
int	ft_echo(t_node *cmd);
int ft_env(t_env *cmd);
int ft_exit(t_node *cmd);
int ft_export(t_node *cmd,t_env **env);
int ft_pwd(t_node *cmd);
int ft_unset(t_node *cmd,t_env **env);
//helper :
int	is_builtin(t_node *cmd);
int exec_builtins(t_node *cmd,t_env *env);
char	**ft_split_a(char const *s, char const *delimiter);
void free_split(char **split);
// int init_export_info(t_node *cmd,t_export *info);
int init_export_info(char *arg, t_export *info,t_env *env);
void echo_has_new_line(t_node *cmd);
void join_args(t_node *cmd);
int valide_key(t_export *info);
int builtin_requires_parent(t_node *cmd);
void envp_dup(t_env *cmd, char **envp);
char **realloc_env(char **old_env, int old_size, int new_size);
void func_print(char **envp);
void    ft_all(t_node **all_cmd, char *line, char **s_line,t_env *info); //5aliha hna
void signal_setup();
void free_split(char **split);
void *ft_malloc(size_t size,char flag);
int	is_all_whitespace(const char *str);

#endif