/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:29:29 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/15 18:14:00 by mohben-t         ###   ########.fr       */
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
int ft_export(t_node *cmd,t_env *env)
{
    int envp_len;
    char *old_value;
    int i;
    char *tmp1;
    char *tmp2;

    t_export *info = malloc(sizeof(t_export));
    if (!info)
        return (-1);
    (info)->flag = 0;
    (info)->append = 0;
    (info)->key = NULL;
    (info)->value = NULL;
    if (init_export_info(cmd,info) == -1)
        return (-1);
    if (!info->key && !cmd->cmd[0] && valide_key(info) == -1 )
        return (-1);
    printf("dibug\n");
    tmp2 = ft_strdup("");
    envp_len = get_len_env(env->my_envp);
    if (info->flag == 1)
        return(ft_sort(env),func_print(env->my_envp),0);
    else
    {

        old_value = get_env_value(info->key, env->my_envp);
        i = get_key(info->key,env->my_envp);
        if (i > -1)
        {
            if (info->append == 1)
                tmp1 = ft_strjoin(old_value, info->value);
            else
                tmp1 = ft_strdup(info->value);
            tmp2 = ft_strjoin(info->key, tmp1);
    
            free(env->my_envp[i]);
            env->my_envp[i] = tmp2;
        }
        else
        {
            tmp1 = ft_strjoin(info->key, info->value);
            env->my_envp[envp_len] = tmp1;
            env->my_envp[envp_len + 1] = NULL;
        }
    }
    return (free(tmp1), free(tmp2), 0);
}
