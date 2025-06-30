/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:11:46 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/30 00:23:33 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtin(t_node *cmd, t_env *env)
{
	g_es = exec_builtins(cmd, env);
	free_all_commands(cmd);
	free_env(env);
	exit(g_es);
}

void	handle_command_not_found(t_node *cmd, t_env *env)
{
	ft_putendl_fd("Dash@Ameed: command not found", 2);
	free_env(env);
	free_all_commands(cmd);
	exit(127);
}

void	handle_execve_failure(t_node *cmd, t_env *env)
{
	ft_putendl_fd("execve error\n", 2);
	free_all_commands(cmd);
	free_env(env);
	exit(2);
}

void	exec_child_process(t_node *cmd, t_env *env)
{
	handle_single_builtin(cmd, env);
	free_all_commands(cmd);
	free_env(env);
	exit(g_es);
}

void	handle_fork_and_wait(t_node *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0 && !builtin_requires_parent(cmd))
		exec_child_process(cmd, env);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_es = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_es = 128 + WTERMSIG(status);
	}
}
