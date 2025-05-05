/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:12:05 by mohben-t          #+#    #+#             */
/*   Updated: 2025/04/29 22:25:30 by mohben-t         ###   ########.fr       */
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

void one_com(t_node *cmd,int num_commands,pid_t pid,int status)
{
	if (num_commands == 1)
    {
        pid = fork();
        if (pid == 0)
        {
            if (cmd->file)
                ft_redirect(cmd->file);
			if (is_builtin(cmd) != -1)
		   		exec_builtins(cmd);
			else
			{
				
            	char *full_path = resolve_path(cmd->cmd[0], cmd->my_envp);
            	if (!full_path)
				{
            	    printf("minishell: %s: Command not found\n",cmd->cmd[0]);
					exit (-1);
				}
            	if (execve(full_path, cmd->cmd, cmd->my_envp) == -1)
					error_exit("execve error");
			}
        }
        else if(pid < 0)
            perror("fork failed");
        else
        {
            waitpid(pid, &status, 0); // parent  Wait child to finish
        }
        return;
    }
}

void multi_com(t_node *cmd,int num_commands,pid_t pid, int prev_pipe,int *pipefds,int i)
{
	while (i < num_commands)
    {
        create_pipe(pipefds);
        pid = fork();
        if (pid == 0) {
            setup_child_process(cmd,prev_pipe, pipefds, i, num_commands);
		   if (is_builtin(cmd) != -1)
		   		exec_builtins(cmd);
		   else
		   {
            	char *full_path = resolve_path(cmd->cmd[0],cmd->my_envp);
            	if (!full_path)
				{
            	    printf("minishell: %s: Command not found\n",cmd->cmd[0]);
					exit (-1);
				}
            	if (execve(full_path, cmd->cmd, cmd->my_envp) == -1)
					error_exit("execve error");
		   }
        }
        else
        {
            close(pipefds[1]);
            if (prev_pipe)
                close(prev_pipe);
            prev_pipe = pipefds[0];
        }
        i++;
        cmd = cmd->next;
	}
}

void pipe_hundel(t_node *cmd,char **envp)
{
    int pipefds[2];
    pid_t pid;
    int num_commands = get_num_commands(cmd);
    int i = 0;
    int prev_pipe = 0;
    int status;
    
    one_com(cmd,num_commands,pid,status);
    multi_com(cmd,num_commands, pid,  prev_pipe, pipefds, i);
    if (prev_pipe)
        close(prev_pipe);
    while (wait(NULL) > 0);
}
