/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:56:21 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/20 16:36:54 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_key_a(const char *key, char **envp)
{
	int		i;
	size_t	key_len;

	if (!key)
		return (-1);
	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_unset(t_node *cmd, t_env **env)
{
	int	i;
	int	idx;

	i = 1;
	if (!cmd || !cmd->cmd || !cmd->cmd[1])
		return (-1);
	while (cmd->cmd[i])
	{
		idx = get_key_a(cmd->cmd[i], (*env)->my_envp);
		if (idx > -1)
		{
			free((*env)->my_envp[idx]);
			while ((*env)->my_envp[idx + 1])
			{
				(*env)->my_envp[idx] = (*env)->my_envp[idx + 1];
				idx++;
			}
			(*env)->my_envp[idx] = NULL;
			(*env)->env_len--;
		}
		i++;
	}
	return (0);
}
