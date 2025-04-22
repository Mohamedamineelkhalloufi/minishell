/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:29:29 by mohben-t          #+#    #+#             */
/*   Updated: 2025/04/21 19:07:35 by mohben-t         ###   ########.fr       */
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
static int get_len_env(char **envp)
{
    int		i = 0;

	while (envp[i])
		i++;
	return (i);
}
static void func_print(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        printf("%s\n",envp[i++]);
}
int ft_export(t_node *cmd)
{
    int envp_len;
    char *old_value;
    char i;
    char *tmp1;
    char *tmp2;

    envp_len = get_len_env(cmd->my_envp);
    old_value = get_env_value(cmd->info->key, cmd->my_envp);
    if (cmd->info->flag == 1)
        return(func_print(cmd->my_envp),0);
    i = get_key(cmd->info->key,cmd->my_envp);
    if (i > -1)
    {
        tmp1 = ft_strjoin(old_value,cmd->info->value);
        tmp2 = ft_strjoin(cmd->info->key, tmp1);
        free(cmd->my_envp[i]);
        cmd->my_envp[i] = tmp2;
    }
    else
    {
        tmp1 = ft_strjoin(cmd->info->key, cmd->info->value);
        cmd->my_envp[envp_len] = tmp1;
    }
    return (free(tmp1), free(tmp2), 0);
}
