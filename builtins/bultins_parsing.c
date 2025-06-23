/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:59:29 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/20 16:39:14 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo_has_new_line(t_node *cmd)
{
    int j;
    cmd->echo_info->new_line = 0;
    if (cmd->cmd[1] && cmd->cmd[1][0] == '-' && cmd->cmd[1][1] == 'n')
    {
        j = 2;
        while (cmd->cmd[1][j] == 'n')
            j++;
        if (cmd->cmd[1][j] == '\0')
            cmd->echo_info->new_line = 1;
    }
}

int join_args(t_node *cmd)
{
    int i;
    char *str;
    char *new_str;
    
    str = ft_strdup("");
    if (!str)
        return (-1);
    i = 1;
    if (cmd->echo_info->new_line == 1)
        i = 2;
    while (cmd->cmd[i])
    {
        new_str = ft_strjoin(str, cmd->cmd[i]);
        if (!new_str)
            return (free(str),-1);
        free(str);
        str = new_str;
        if (cmd->cmd[i + 1])
        {
            new_str = ft_strjoin(str, " ");
            if (!new_str)
                return (free(str),-1);
            free(str);
            str = new_str;
        }
        i++;
    }
    cmd->echo_info->echo_str = str;
    return (0);
}

void free_echo_info(t_echo *echo_info)
{
    if (!echo_info)
        return;
    if (echo_info->echo_str)
        free(echo_info->echo_str);
    free(echo_info);
}

int init_export_info(char *arg, t_export *info,t_env *env)
{
    char **split;
    char *key_part;
    char *value_part;
    int key_len;

    info->key = NULL;
    info->value = NULL;
    info->append = 0;
    info->fg = 0;
    (void)env;
    
    if (arg[0] == '=')
        info->fg = 1;
    else
    {
        split = ft_split_a(arg, "=");
        if (!split)
            return (-1);
        key_part = split[0];
        value_part = split[1];
        if (!key_part)
            return (free_split(split), -1);
        key_len = ft_strlen(key_part);
        if (key_len > 0 && key_part[key_len - 1] == '+')
        {
            info->append = 1;
            key_part[key_len - 1] = '\0';
        }
        info->key = ft_strdup(key_part);
        if (!info->key)
            return (free_split(split), -1);
        if (!value_part)
            info->value = ft_strdup("");
        else
            info->value = ft_strdup(value_part);
        if (!info->value)
        {
            free(info->key);
            info->key = NULL;
            return (free_split(split), -1);
        }
        free_split(split);
    }
    return (0);
}

int valide_key(t_export *info)
{
    if (info->fg == 1)
    {
        ft_putendl_fd("not a valid identifier\n",2);
        return(-1);
    }
    if(!info->key)
        return (0);
    size_t key_len= ft_strlen(info->key);
    if(isalpha(info->key[0]) || info->key[0] == '_')
    {
        if (info->key[key_len - 1] == ' ')
        {
            ft_putendl_fd("not a valid identifier\n",2);
            return (-1);
        }
        return (0);
    }
    ft_putendl_fd("not a valid identifier\n",2);
    return (-1);
}
