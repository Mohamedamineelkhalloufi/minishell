/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:16:24 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/30 11:17:04 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <time.h>
# define RESET " \e[00m"

# ifndef GLOBALS_H
#  define GLOBALS_H

extern int			g_es;
# endif

typedef struct s_redi
{
	char			*file_num;
	char			*heredoc_file;
	int				type;
	struct s_redi	*next;
}					t_redi;

typedef struct s_exit
{
	int				status;
	int				pid;
}					t_exit;

typedef struct s_export
{
	int				i_postion;
	int				fg;
	int				flag;
	int				append;
	char			*key;
	char			*value;
}					t_export;

typedef struct s_echo
{
	int				new_line;
	char			*echo_str;
}					t_echo;
typedef struct s_env
{
	char			**my_envp;
	int				env_len;
	struct s_env	*next;
}					t_env;

typedef struct s_node
{
	char			**cmd;
	t_redi			*file;
	t_export		*info;
	t_echo			*echo_info;
	t_exit			*exit_info;
	struct s_node	*next;
}					t_node;

typedef struct s_exec_ctx
{
	int				i;
	int				num_commands;
	int				prev_pipe;
	int				pipefds[2];
	pid_t			pid;
	pid_t			last_pid;
	t_node			*temp_cmd;
}					t_exec_ctx;

void				free_redi_list(t_redi *r);
int					check_split(char *line, int i, char q);
int					d_quote(char *line, int dquote, int quote, int i);
int					check_pipe(char *line);
int					if_check_pipe(char *line, int i, char q);
char				*qoute_remov(char *line, char q, int i, int l);
void				free_all_commands(t_node *head);
int					lexer(t_node **test, char *s_line, char **p_line);
int					len_forma(char *line, int i, int l);
char				*fix_line(char *line);
int					check_redirections(char **p_line);
int					num_cmd(char **p_line);
int					handle_quotes(char *line, char *new_line, int *i, int *l);
int					handle_redirects(char *line, char *new_line, int *i,
						int *l);
t_redi				*creat_file(t_redi *head, char *file_num, char *check);
void				free_node(t_node *node);
t_node				*init_node(int num_cmd);
t_node				*creat_node(t_node *head, char **cmd, int num_cmd);
int					process_cmd(t_node *new_node, char **cmd, int i, int l);
void				set_redi_type(t_redi *new_redi, char *check);
void				add_redi_to_list(t_redi *head, t_redi *new_redi);
char				*expand_line(char *line, int dquote, char *plus,
						t_env *info);
int					skip_quotes(char *line, int i, int *dquote);
int					handle_dollar(char **plus, char *line, t_env *info);
char				*expand_val(char *s, t_env *info);
char				*find_end(char *start);
char				*handle_dollar_case(char *start);
void				error_exit(const char *msg);
char				*resolve_path(char *command, char **envp, int i);
void				pipe_hundel(t_node *cmd, t_env *env);
int					ft_redirect(t_redi *redir, t_env *env);
int					get_num_commands(t_node *cmd);
char				*get_env_value(const char *key, char **envp);
void				ft_sort(t_env *cmd);
int					ft_cd(t_node *cmd, t_env *env);
int					ft_echo(t_node *cmd);
int					ft_env(t_env *cmd);
int					ft_exit(t_node *cmd, t_env *env);
int					ft_export(t_node *cmd, t_env **env);
int					ft_pwd(t_node *cmd);
int					ft_unset(t_node *cmd, t_env **env);
int					get_key(const char *key, char **envp);
int					get_first_index_of_value(const char *key, char **envp);
int					is_builtin(t_node *cmd);
int					exec_builtins(t_node *cmd, t_env *env);
char				**ft_split_a(char const *s, char const *delimiter);
void				free_split(char **split);
int					init_export_info(char *arg, t_export *info, char **split,
						char *value_part);
void				echo_has_new_line(t_node *cmd);
int					join_args(t_node *cmd, int i);
void				free_echo_info(t_echo *echo_info);
int					valide_key(t_export *info);
int					builtin_requires_parent(t_node *cmd);
t_env				*envp_dup(char **envp);
char				**realloc_env(char **old_env, int old_size, int new_size);
void				func_print(char **envp);
void				ft_all(t_node **all_cmd, char *line, char **s_line,
						t_env *info);
void				signal_setup(void);
void				free_split(char **split);
int					is_all_whitespace(const char *str);
void				g_handler(int sig);
void				free_heredoc(t_node *cmd, t_env *env, char *tmp);
int					add_new_env(t_export *info, t_env **env);
int					update_existing_env(t_export *info, t_env **env, int index);
char				*handle_value_update(t_export *info, char *old_value);
char				*create_env_string(char *key, char *value);
int					update_env_variable(const char *key, const char *value,
						char **envp);
int					update_pwd_variables(char *oldpwd, char *pwd, t_env *env);
int					change_directory(const char *target_dir, t_env *env);
char				*expand_line1(char *line, char *plus, t_env *info);
int					ft_heredoc(t_redi *redier, t_env *env);
void				handle_single_builtin(t_node *cmd, t_env *env);
int					has_heredoc(t_redi *r);
void				create_pipe(int pipefds[2]);
void				execute_command(t_node *cmd, t_env *env);
char				*find_end(char *start);
void				free_redi_list(t_redi *r);
void				free_node(t_node *node);
void				single_command(t_node **cmd, t_env *env, pid_t pid_2,
						int status);
void				setup_parent_process(t_exec_ctx *ctx, t_node *cmd);
int					prepare_heredoc(t_node *temp_cmd, t_env *env);
t_redi				*find_last_heredoc(t_redi *redir);
void				cleanup_heredoc_files(t_node *cmd_list);
void				handle_child_process(t_node *cmd, t_env *env);
void				wait_for_children(pid_t last_pid);
void				handle_parent_process(int *prev_pipe, int pipefds[2],
						pid_t pid, pid_t *last_pid);
void				setup_child_process(t_node *cmd, t_exec_ctx *ctx);
int					has_output_redirection(t_redi *redir);
int					open_heredoc_file(char **tmp, int *fd, int count);
int					write_heredoc_loop(t_redi *redi, t_env *env, int fd);
void				init_exec_ctx(t_exec_ctx *ctx, int num_commands,
						t_node *cmd);
void				handle_heredoc_input(t_node *cmd);
void				handle_pipe_input(int prev_pipe);
void				clean_export(t_export *info, char **split);
void				init_export(t_export *info);
int					process_key(t_export *info, char *key_part);
void				handle_builtin(t_node *cmd, t_env *env);
void				handle_command_not_found(t_node *cmd, t_env *env);
void				handle_execve_failure(t_node *cmd, t_env *env);
void				exec_child_process(t_node *cmd, t_env *env);
void				handle_fork_and_wait(t_node *cmd, t_env *env);
void				exec_child_block(t_node *cmd, t_env *env, t_exec_ctx *ctx);
void				exec_parent_block(t_exec_ctx *ctx, t_node *cmd);
void				advance_command(t_node **cmd, t_exec_ctx *ctx);
void				cleanup_command_heredoc_files(t_node *cmd);
void				cleanup_after_commands(t_exec_ctx *ctx);
void				handle_mc(t_node *cmd, t_env *env, int num_commands,
						t_exec_ctx *ctx);
void				free_env(t_env *env);

#endif
