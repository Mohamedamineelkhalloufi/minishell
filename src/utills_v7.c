/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 01:49:29 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/01 16:59:58 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_child_block(t_node *cmd, t_env *env, t_exec_ctx *ctx)
{
	setup_child_process(cmd, ctx);
	if (cmd->file)
		ft_redirect(cmd->file, env);
	handle_child_process(cmd, env);
	free_all_commands(cmd);
	free_env(env);
	exit(g_es);
}

void	exec_parent_block(t_exec_ctx *ctx, t_node *cmd)
{
	if (ctx->pid > 0)
	{
		setup_parent_process(ctx, cmd);
		if (cmd->file)
			cleanup_command_heredoc_files(cmd);
	}
	else
		perror("fork failed");
}

void	advance_command(t_node **cmd, t_exec_ctx *ctx)
{
	t_node	*next;

	next = (*cmd)->next;
	free_redi_list((*cmd)->file);
	free(*cmd);
	*cmd = next;
	ctx->i++;
}

void	cleanup_command_heredoc_files(t_node *cmd)
{
	t_redi	*redir;

	if (!cmd || !cmd->file)
		return ;
	redir = cmd->file;
	while (redir)
	{
		if (redir->type == 3 && redir->heredoc_file)
			unlink(redir->heredoc_file);
		redir = redir->next;
	}
}

void	cleanup_after_commands(t_exec_ctx *ctx)
{
	if (ctx->prev_pipe)
		close(ctx->prev_pipe);
	wait_for_children(ctx->last_pid);
	signal_setup();
}
