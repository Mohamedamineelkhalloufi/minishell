/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:29:29 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/02 14:04:39 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int get_key(const char *key, char **envp)
{
    int        i = 0;
    size_t    key_len = ft_strlen(key);

    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
            return (i);
        i++;
    }
    return (-1);
}

void func_print(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        printf("%s\n", envp[i++]);
}

int process_single_export(char *arg, t_env **env)
{
    t_export info;
    char *old_value;
    int i;
    char *tmp1;
    char *tmp2;
    char *temp3;

    if (init_export_info(arg, &info,*env) == -1)
        return (1);
    
    if (valide_key(&info) == -1)
    {
        free(info.key);
        free(info.value);
        return (1);
    }

    old_value = get_env_value(info.key, (*env)->my_envp);
    i = get_key(info.key, (*env)->my_envp);
    
    if (i > -1)
    {
        // printf("sd\n");
        if (info.append == 1)
            tmp1 = ft_strjoin(old_value, info.value);
        else
            tmp1 = ft_strdup(info.value);
        
        temp3 = ft_strjoin(info.key, "=");
        tmp2 = ft_strjoin(temp3, tmp1);
        
        free((*env)->my_envp[i]);
        (*env)->my_envp[i] = tmp2;
        free(tmp1);
        free(temp3);
    }
    else
    {
        (*env)->my_envp = realloc_env((*env)->my_envp, (*env)->env_len, (*env)->env_len + 1);
        if (info.value[0] == '\0')
            tmp2 = ft_strdup(info.key);
        else
        {
            temp3 = ft_strjoin(info.key, "=");
            tmp2 = ft_strjoin(temp3, info.value);
            free(temp3);
        }
        
        (*env)->my_envp[(*env)->env_len] = tmp2;
        (*env)->env_len++;
        (*env)->my_envp[(*env)->env_len] = NULL;
    }
    free(info.key);
    free(info.value);
    return (0);
}

int ft_export(t_node *cmd, t_env **env)
{
    int i;
    int ret;

    if (cmd->cmd[1] == NULL)
        return (ft_sort(*env), func_print((*env)->my_envp), 0);
    i = 1;
    ret = 0;
    while (cmd->cmd[i])
    {
        if (process_single_export(cmd->cmd[i], env) != 0)
            ret = 1;
        i++;
    }
    return (ret);
}