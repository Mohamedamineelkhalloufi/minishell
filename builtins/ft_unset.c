/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:56:21 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/14 17:27:12 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int get_key(const char *key, char **envp)
{
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

int ft_unset(t_node *cmd,t_env *env)
{
    int i;

    i = get_key(cmd->unset_info->key,env->my_envp);
    if (i == -1)
        return (-1);
    free(env->my_envp[i]);
    while (env->my_envp[i + 1])
    {
        env->my_envp[i] = env->my_envp[i + 1];
        i++;
    }
    env->my_envp[i] = NULL;
    return(0);
}
