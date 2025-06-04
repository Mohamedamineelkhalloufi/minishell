/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:56:21 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/26 11:46:49 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int get_key(const char *key, char **envp)
{
    if (!key)
        return (-1);
    int		i = 0;
	size_t	key_len = ft_strlen(key);

	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int ft_unset(t_node *cmd, t_env **env)
{
    int i;
    int idx;
    
    i = 1;
    if (!cmd || !cmd->cmd || !cmd->cmd[1])
        return (-1);
    while (cmd->cmd[i])
    {
        idx = get_key(cmd->cmd[i], (*env)->my_envp);
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
