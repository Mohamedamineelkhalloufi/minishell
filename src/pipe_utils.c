/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:16:25 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/30 10:01:25 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_command(t_node **cmd, t_env *env, pid_t pid_2, int status)
{
	t_node	*cmd2;

	(void)pid_2;
	(void)status;
	if (is_builtin(*cmd) && builtin_requires_parent(*cmd))
		handle_single_builtin(*cmd, env);
	else
		handle_fork_and_wait(*cmd, env);
	if (*cmd)
	{
		cmd2 = (*cmd)->next;
		free_redi_list((*cmd)->file);
		free_split((*cmd)->cmd);
		free(*cmd);
		*cmd = cmd2;
	}
}

void	setup_parent_process(t_exec_ctx *new, t_node *cmd)
{
	if (new->prev_pipe)
		close(new->prev_pipe);
	if (new->i < new->num_commands - 1)
	{
		close(new->pipefds[1]);
		new->prev_pipe = new->pipefds[0];
	}
	new->last_pid = new->pid;
	free_split(cmd->cmd);
}

int	prepare_heredoc(t_node *temp_cmd, t_env *env)
{
	t_redi	*tmp;

	while (temp_cmd)
	{
		if (temp_cmd->file)
		{
			tmp = temp_cmd->file;
			while (tmp)
			{
				if (tmp->type == 3)
				{
					if (ft_heredoc(tmp, env) == -1)
						return (-1);
				}
				tmp = tmp->next;
			}
		}
		temp_cmd = temp_cmd->next;
	}
	return (0);
}

void	cleanup_heredoc_files(t_node *cmd_list)
{
	t_node	*current;
	t_redi	*redir;

	current = cmd_list;
	while (current)
	{
		if (current->file)
		{
			redir = current->file;
			while (redir)
			{
				if (redir->type == 3)
				{
					if (redir->heredoc_file)
						unlink(redir->heredoc_file);
				}
				redir = redir->next;
			}
		}
		current = current->next;
	}
}

t_redi	*find_last_heredoc(t_redi *redir)
{
	t_redi	*last_heredoc;
	t_redi	*tmp;

	tmp = redir;
	last_heredoc = NULL;
	while (tmp)
	{
		if (tmp->type == 3)
			last_heredoc = tmp;
		tmp = tmp->next;
	}
	return (last_heredoc);
}
