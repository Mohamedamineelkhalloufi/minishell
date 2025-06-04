/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:12:05 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/03 16:06:47 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void create_pipe(int pipefds[2]) {
    if (pipe(pipefds) == -1)
        error_exit("Pipe creation failed");
}

static void setup_child_process(t_node *cmd, int prev_pipe, int pipefds[2], int i, int num_commands) {
    if (prev_pipe)
        dup2(prev_pipe, STDIN_FILENO);
    if (i < num_commands - 1)
        dup2(pipefds[1], STDOUT_FILENO);
    if (cmd->file)
        ft_redirect(cmd->file);
    close(pipefds[0]);
    close(pipefds[1]);
}

static void handle_single_builtin(t_node *cmd, t_env *env) {
    int ret;

    if (cmd->file && ft_redirect(cmd->file) == -1)
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

static void execute_command(t_node *cmd, t_env *env)
{
    char *full_path;
    int ret;

    if (is_builtin(cmd)) {
        ret = exec_builtins(cmd, env);
        exit(ret);
    }
    else
    {
        if (cmd->cmd[0] && !is_all_whitespace(cmd->cmd[0]))
        {
            full_path = resolve_path(cmd->cmd[0], env->my_envp);
            if (!full_path)
            {
                dprintf(2, "Dash@Ameed: %s: command not found\n", cmd->cmd[0]);
                exit(127);
            }
            execve(full_path, cmd->cmd, env->my_envp);
            perror("execve");
            free(full_path);
            exit(126);
        }
        else
            exit(0);
    }
}
static void handle_single_command(t_node *cmd, t_env *env) {
    pid_t pid;
    int status;

    if (is_builtin(cmd) && builtin_requires_parent(cmd))
        return( handle_single_builtin(cmd, env));
    pid = fork();
    if (pid == 0)
    {
        if (cmd->file && ft_redirect(cmd->file) == -1)
            return;
        if(cmd)
            execute_command(cmd, env);
    }
    else if (pid < 0)
        perror("fork failed");
    else 
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            g_es = WEXITSTATUS(status);
    }
}

static void handle_child_process(t_node *cmd, int prev_pipe, int pipefds[2], int i, int num_commands, t_env *env) {
    setup_child_process(cmd, prev_pipe, pipefds, i, num_commands);
    execute_command(cmd, env);
}

static void handle_parent_process(int *prev_pipe, int pipefds[2], pid_t pid, pid_t *last_pid) {
    *last_pid = pid;
    close(pipefds[1]);
    if (*prev_pipe)
        close(*prev_pipe);
    *prev_pipe = pipefds[0];
}

static void wait_for_children(pid_t last_pid) {
    pid_t wpid;
    int status;

    while ((wpid = wait(&status)) > 0) {
        if (wpid == last_pid && WIFEXITED(status))
            g_es = WEXITSTATUS(status);
    }
}

static void handle_multiple_commands(t_node *cmd, t_env *env, int num_commands) {
    int pipefds[2];
    pid_t pid;
    pid_t last_pid = -1;
    int i = 0;
    int prev_pipe = 0;

    while (i < num_commands)
    {
        create_pipe(pipefds);
        pid = fork();
        if (pid == 0)
            handle_child_process(cmd, prev_pipe, pipefds, i, num_commands, env);
        else if (pid > 0)
            handle_parent_process(&prev_pipe, pipefds, pid, &last_pid);
        else
            perror("fork failed");

        i++;
        cmd = cmd->next;
    }
    if (prev_pipe)
        close(prev_pipe);
    wait_for_children(last_pid);
}

void pipe_hundel(t_node *cmd, t_env *env) {
    int num_commands = get_num_commands(cmd);

    if (num_commands == 1)
        handle_single_command(cmd, env);
    else
        handle_multiple_commands(cmd, env, num_commands);
}
