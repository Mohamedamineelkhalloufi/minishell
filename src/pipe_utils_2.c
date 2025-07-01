/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:19:57 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/01 18:58:35 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_output_redirection(t_redi *redir)
{
	t_redi	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == 1 || tmp->type == 2)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	setup_child_process(t_node *cmd, t_exec_ctx *new)
{
	if (new->i == 0)
		handle_heredoc_input(cmd);
	else
		handle_pipe_input(new->prev_pipe);
	if (new->i < new->num_commands - 1)
	{
		if (!has_output_redirection(cmd->file))
		{
			if (dup2(new->pipefds[1], STDOUT_FILENO) == -1)
			{
				perror("dup2 pipe output");
				exit(1);
			}
		}
	}
	if (new->i < new->num_commands - 1)
		return (close(new->pipefds[0]),
			close(new->pipefds[1]), (void)0);
}

void	handle_child_process(t_node *cmd, t_env *env)
{
	execute_command(cmd, env);
}

void	handle_parent_process(int *prev_pipe, int pipefds[2],
	pid_t pid, pid_t *last_pid)
{
	*last_pid = pid;
	close(pipefds[1]);
	if (*prev_pipe)
		close(*prev_pipe);
	*prev_pipe = pipefds[0];
}

void	wait_for_children(pid_t last_pid)
{
	pid_t	wpid;
	int		status;

	status = 0;
	while (1)
	{
		wpid = wait(&status);
		if (wpid == -1)
			break ;
		if (wpid == last_pid && WIFEXITED(status))
			g_es = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
}
