/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:35:34 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/01 22:28:36 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lenght_cmd(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int	get_first_index_of_value(const char *key, char **envp)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_target_directory(char **cmd_args, char **envp)
{
	int		home_index;
	char	*target_dir;

	if (!cmd_args[1])
	{
		home_index = get_first_index_of_value("HOME", envp);
		if (home_index == -1)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (NULL);
		}
		target_dir = ft_strdup(envp[home_index] + 5);
	}
	else
	{
		target_dir = ft_strdup(cmd_args[1]);
	}
	return (target_dir);
}

int	ft_cd(t_node *cmd, t_env *env)
{
	char	*target_dir;
	int		result;

	if (lenght_cmd(cmd->cmd) > 2)
		return (ft_putendl_fd("cd : too many arguments", 2), 1);
	target_dir = get_target_directory(cmd->cmd, env->my_envp);
	if (!target_dir)
		return (1);
	result = change_directory(target_dir, env);
	free(target_dir);
	return (result);
}
