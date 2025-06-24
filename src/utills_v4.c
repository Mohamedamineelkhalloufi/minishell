/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:55:50 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/23 17:59:09 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_single_builtin(t_node *cmd, t_env *env)
{
    int ret = 0;

    if (cmd->file && ft_redirect(cmd->file,env) == -1)
    {
        g_es = 1;
        return;
    }
    if (cmd)
    {
        ret = exec_builtins(cmd, env);
        g_es = ret;
    }
}

int has_heredoc(t_redi *r)
{
    while (r)
    {
        if (r->type == 3)
            return (1);
        r = r->next;
    }
    return (0);
}

void create_pipe(int pipefds[2])
{
    if (pipe(pipefds) == -1)
        error_exit("Pipe creation failed");
}

void setup_child_process(t_node *cmd, int prev_pipe, int pipefds[2], int i, int num_commands)
{
    if (prev_pipe && !has_heredoc(cmd->file))
        dup2(prev_pipe, STDIN_FILENO);
    if (i < num_commands - 1)
        dup2(pipefds[1], STDOUT_FILENO);
    close(pipefds[0]);
    close(pipefds[1]);
}

void execute_command(t_node *cmd, t_env *env)
{
    char *full_path;

    if (is_builtin(cmd))
    {
        g_es = exec_builtins(cmd, env);
        free_all_commands(cmd);
        free_env(env);
        exit(g_es);
    }
    else if (cmd->cmd[0] && !is_all_whitespace(cmd->cmd[0]))
    {
        signal(SIGINT,SIG_DFL);
        full_path = resolve_path(cmd->cmd[0], env->my_envp,0);
        if (!full_path)
        {
            ft_putendl_fd("Dash@Ameed: command not found",2);
            free_env(env);
            free_all_commands(cmd);
            exit (127);
        }
        if(execve(full_path, cmd->cmd, env->my_envp) == -1)
        {
            ft_putendl_fd("execve error\n",2);
            free_all_commands(cmd);
            free_env(env);
            exit(2);
        }
        return (free(full_path), free_env(env), \
            free_all_commands(cmd),exit(126),(void)0);  
    }
    else
        return(free_env(env),free_all_commands(cmd),exit(0),(void)0);
}
