/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:12:05 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/30 10:43:54 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_input_redirection(t_redi *file)
{
	t_redi	*tmp;

	tmp = file;
	while (tmp)
	{
		if (tmp->type == 0 || tmp->type == 3)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	creat_pipe(int pipefds[2])
{
	if (pipe(pipefds) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	init_exec_ctx(t_exec_ctx *ctx, int num_commands, t_node *cmd)
{
	ctx->i = 0;
	ctx->temp_cmd = cmd;
	ctx->prev_pipe = 0;
	ctx->num_commands = num_commands;
	ctx->pipefds[0] = -1;
	ctx->pipefds[1] = -1;
	ctx->pid = -1;
	ctx->last_pid = -1;
}

void	handle_mc(t_node *cmd, t_env *env, int num_commands, t_exec_ctx *ctx)
{
	if (prepare_heredoc(ctx->temp_cmd, env) == -1)
		return (cleanup_heredoc_files(ctx->temp_cmd), (void)0);
	while (cmd && ctx->i < num_commands)
	{
		if (ctx->i < num_commands - 1)
			creat_pipe(ctx->pipefds);
		if (is_builtin(cmd) && num_commands == 1)
			single_command(&cmd, env, 0, 0);
		else
		{
			signal(SIGINT, SIG_IGN);
			ctx->pid = fork();
			if (ctx->pid == 0)
				exec_child_block(cmd, env, ctx);
			else
			{
				waitpid(ctx->pid, NULL, 0);
				exec_parent_block(ctx, cmd);
			}
			advance_command(&cmd, ctx);
		}
	}
	cleanup_after_commands(ctx);
}

void	pipe_hundel(t_node *cmd, t_env *env)
{
	int			num_commands;
	t_exec_ctx	ctx;

	num_commands = get_num_commands(cmd);
	init_exec_ctx(&ctx, num_commands, cmd);
	handle_mc(cmd, env, num_commands, &ctx);
}
