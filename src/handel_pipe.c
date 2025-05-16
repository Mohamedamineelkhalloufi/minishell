/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:12:05 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/16 13:55:40 by mohel-kh         ###   ########.fr       */
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
void pipe_hundel(t_node *cmd,t_env *env)
{
    int pipefds[2];
    pid_t pid;
    int num_commands = get_num_commands(cmd);
    int i = 0;
    int prev_pipe = 0;
    int status;
    int ret;

/*----------------------------------  one command  ---------------------------------------*/

if (num_commands == 1)
{
	if (is_builtin(cmd) && builtin_requires_parent(cmd))
	{
		if (cmd->file)
			ft_redirect(cmd->file);
		exec_builtins(cmd, env);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (cmd->file)
			ft_redirect(cmd->file);
		if (is_builtin(cmd))
        {
            ret = exec_builtins(cmd, env);
            exit(ret);  
        }
		else
		{
			char *full_path = resolve_path(cmd->cmd[0], env->my_envp);
			if (!full_path)
            {
				printf("minishell: %s: command not found\n", cmd->cmd[0]);
                exit(127); // Bash exit for "command not found"
            }
			execve(full_path, cmd->cmd, env->my_envp);
			perror("execve");
			free(full_path);
            exit(126); // Bash exit for "executable cannot run"
		}
	}
	else if (pid < 0)
		perror("fork failed");
	else
		waitpid(pid, &status, 0);
	return;
}

/*----------------------------------  multti_command  ---------------------------------------*/

    while (i < num_commands)
    {
        create_pipe(pipefds);
        
        pid = fork();
        if (is_builtin(cmd) && builtin_requires_parent(cmd))
        {
            if (cmd->file)
                ft_redirect(cmd->file);
            exec_builtins(cmd,env);
        return;
        }
        if (pid == 0) {
            setup_child_process(cmd,prev_pipe, pipefds, i, num_commands);
            if (is_builtin(cmd))
            {
                ret = exec_builtins(cmd, env);
                exit(ret);  
            }
		   else
		   {
            	char *full_path = resolve_path(cmd->cmd[0], env->my_envp);
            	if (!full_path)
				{
            	    printf("minishell: %s: Command not found\n",cmd->cmd[0]);
					exit (127);
				}
            	if (execve(full_path, cmd->cmd, env->my_envp) == -1)
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
    if (prev_pipe)
        close(prev_pipe);
    while (wait(NULL) > 0);
}
