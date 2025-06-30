/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:55:50 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/30 00:12:30 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_single_builtin(t_node *cmd, t_env *env)
{
	int	ret;

	ret = 0;
	if (cmd->file && ft_redirect(cmd->file, env) == -1)
	{
		g_es = 1;
		return ;
	}
	if (cmd)
	{
		ret = exec_builtins(cmd, env);
		g_es = ret;
	}
}

int	has_heredoc(t_redi *r)
{
	while (r)
	{
		if (r->type == 3)
			return (1);
		r = r->next;
	}
	return (0);
}

void	create_pipe(int pipefds[2])
{
	if (pipe(pipefds) == -1)
		error_exit("Pipe creation failed");
}

void	execute_command(t_node *cmd, t_env *env)
{
	char	*full_path;

	if (is_builtin(cmd))
		return (handle_builtin(cmd, env));
	if (!cmd->cmd[0] || is_all_whitespace(cmd->cmd[0]))
		return (free_env(env), free_all_commands(cmd), exit(0), (void)0);
	signal(SIGINT, SIG_DFL);
	full_path = resolve_path(cmd->cmd[0], env->my_envp, 0);
	if (!full_path)
		return (handle_command_not_found(cmd, env));
	if (execve(full_path, cmd->cmd, env->my_envp) == -1)
		return (handle_execve_failure(cmd, env));
	free(full_path);
	free_env(env);
	free_all_commands(cmd);
	exit(126);
}
