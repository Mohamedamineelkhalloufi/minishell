/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:12:05 by mohben-t          #+#    #+#             */
/*   Updated: 2025/04/21 17:43:38 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void create_pipe(int pipefds[2])
{
    if (pipe(pipefds) == -1) {
        error_exit("Pipe creation failed");
    }
}
static void setup_child_process(t_node *cmd, int prev_pipe, int pipefds[2], int i, int num_commands)
{
    if (prev_pipe) {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }
    if (i < num_commands - 1)
        dup2(pipefds[1], STDOUT_FILENO);
    if (cmd->file)
        ft_redirect(cmd->file);
    close(pipefds[0]);
    close(pipefds[1]);
}
void pipe_hundel(t_node *cmd,char **envp)
{
    int pipefds[2];
    pid_t pid;
    int num_commands = get_num_commands(cmd);
    int i = 0;
    int prev_pipe = 0;
    int status;

/*----------------------------------  one command  ---------------------------------------*/

    if (num_commands == 1)
    {
        pid = fork();
        if (pid == 0)
        {
            if (cmd->file)
                ft_redirect(cmd->file);
            char *full_path = resolve_path(cmd->cmd[0], envp);
            if (!full_path)
                error_exit("Command not found");
            execve(full_path, cmd->cmd, envp);
            error_exit("execve failed");
        }
        else if(pid < 0)
            perror("fork failed");
        else
        {
            waitpid(pid, &status, 0); // parent  Wait child to finish
        }
        return;
    }

/*----------------------------------  multti_command  ---------------------------------------*/
    // num_commands += 1;
    while (i < num_commands)
    {
        create_pipe(pipefds);
        pid = fork();
        if (pid == 0) {
            setup_child_process(cmd,prev_pipe, pipefds, i, num_commands);
            char *full_path = resolve_path(cmd->cmd[0],envp);
            if (!full_path)
                error_exit("Command not found");
            execve(full_path, cmd->cmd, envp);
            error_exit("execve failed");
        }
        else {
            close(pipefds[1]);
            if (prev_pipe)
                close(prev_pipe);
            prev_pipe = pipefds[0];
        }
        i++;
        cmd = cmd->next;
    }
    if (prev_pipe)
        close(prev_pipe);
    while (wait(NULL) > 0);
}
