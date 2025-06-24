/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:12:05 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/24 05:23:28 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_child_process(t_node *cmd, int prev_pipe, int pipefds[2], int i, int num_commands, t_env *env)
{
    setup_child_process(cmd, prev_pipe, pipefds, i, num_commands);
    execute_command(cmd, env);
}

void handle_parent_process(int *prev_pipe, int pipefds[2], pid_t pid, pid_t *last_pid) {
    *last_pid = pid;
    close(pipefds[1]);
    if (*prev_pipe)
        close(*prev_pipe);
    *prev_pipe = pipefds[0];
}

void wait_for_children(pid_t last_pid)
{
    pid_t wpid;

    while ((wpid = wait(&g_es)) > 0)
    {
        if (wpid == last_pid && WIFEXITED(g_es))
            g_es = WEXITSTATUS(g_es);
    }
    if (WIFSIGNALED(g_es) && WTERMSIG(g_es) == SIGINT)
        return (write(1,"\n",1), (void)0);
}

static void handle_multiple_commands(t_node *cmd, t_env *env, int num_commands)
{
    int pipefds[2];
    int status;
    pid_t pid;
    pid_t pid_2;
    pid_t last_pid = -1;
    int i = 0;
    int prev_pipe = 0;
    t_node *cmd2 = NULL;
    while (cmd && i < num_commands)
    {
        create_pipe(pipefds);
        if (is_builtin(cmd) && num_commands == 1)
        {
            if (is_builtin(cmd) && builtin_requires_parent(cmd))
                handle_single_builtin(cmd, env);
            else
            {
                
                pid_2 = fork();
                if (pid_2 == -1)
                {
                    perror("fork");
                    exit(0);
                }
                else if (pid_2 == 0 && !builtin_requires_parent(cmd))
                {
                    handle_single_builtin(cmd, env);
                    free_all_commands(cmd);
                    free_env(env);
                    exit(g_es);
                }
                else
                {
                    waitpid(pid_2, &status, 0);
                    if (WIFEXITED(status))
                        g_es = WEXITSTATUS(status);
                    else if (WIFSIGNALED(status))
                        g_es = 128 + WTERMSIG(status);
                }
            }
            if(cmd)
            {
                cmd2 = cmd->next;
                free_redi_list(cmd->file);
                free_split(cmd->cmd);
                free(cmd);
                cmd = cmd2;
            }
        }
        else
        {
            signal(SIGINT, SIG_IGN);
            pid = fork();
            if (pid == 0)
            {
                if (cmd->file)
                    ft_redirect(cmd->file,env);
                handle_child_process(cmd, prev_pipe, pipefds, i, num_commands, env);
            }
            else if (pid > 0)
            {
                // signal_setup();
                handle_parent_process(&prev_pipe, pipefds, pid, &last_pid);
                free_split(cmd->cmd);
            }
            else
                perror("fork failed");
            i++;
            cmd2 = cmd->next;
            free_redi_list(cmd->file);
            free(cmd);
            cmd = cmd2;
        }
    }
    if (prev_pipe)
        close(prev_pipe);
    wait_for_children(last_pid);
    signal_setup();
}

void pipe_hundel(t_node *cmd, t_env *env) 
{
    int num_commands;

    num_commands = get_num_commands(cmd);
    handle_multiple_commands(cmd, env, num_commands);
}

