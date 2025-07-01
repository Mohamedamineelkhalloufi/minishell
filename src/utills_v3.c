/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:51:57 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/01 22:23:15 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_num_commands(t_node *cmd)
{
	int	count;

	count = 0;
	while (cmd != NULL)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	ft_sort(t_env *cmd)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (cmd->my_envp[i])
	{
		j = 0;
		while (cmd->my_envp[j + 1])
		{
			if (strcmp(cmd->my_envp[j], cmd->my_envp[j + 1]) > 0)
			{
				temp = cmd->my_envp[j];
				cmd->my_envp[j] = cmd->my_envp[j + 1];
				cmd->my_envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	is_builtin(t_node *cmd)
{
	int			i;
	const char	*builtins[] = {"cd", "echo", "env", "export", "pwd", "exit",
		"unset", NULL};

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd->cmd[0], builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	builtin_requires_parent(t_node *cmd)
{
	int			i;
	const char	*parent_builtins[] = {"cd", "export", "unset", "exit", NULL};

	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (0);
	i = 0;
	while (parent_builtins[i])
	{
		if (ft_strcmp(cmd->cmd[0], parent_builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtins(t_node *cmd, t_env *env)
{
	int	res;

	res = 1;
	if (is_builtin(cmd) == 1)
	{
		if (ft_strcmp(cmd->cmd[0], "cd") == 0)
			res = ft_cd(cmd, env);
		else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
			res = ft_echo(cmd);
		else if (ft_strcmp(cmd->cmd[0], "env") == 0)
			res = ft_env(env, cmd);
		else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
			res = ft_exit(cmd, env);
		else if (ft_strcmp(cmd->cmd[0], "export") == 0)
			res = ft_export(cmd, &env);
		else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
			res = ft_pwd(cmd);
		else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
			res = ft_unset(cmd, &env);
	}
	return (res);
}
