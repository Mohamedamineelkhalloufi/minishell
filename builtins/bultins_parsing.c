/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:59:29 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/08 15:49:02 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*----------------------_parsing_echo_---------------------------------*/
int echo_has_new_line(t_node *cmd)
{
    int j;

    cmd->echo_info->new_line = 0;
    if (!cmd->cmd[1])
        return (0);

    if (cmd->cmd[1][0] == '-' && cmd->cmd[1][1] == 'n')
    {
        j = 2;
        while (cmd->cmd[1][j] == 'n')
            j++;
        if (cmd->cmd[1][j] == '\0')
            cmd->echo_info->new_line = 1;
    }
    return (0);
}

void join_args(t_node *cmd)
{
    int i;
    char *str;
    char *tmp;

    str = ft_strdup("");
    i = 1;
    if (cmd->echo_info->new_line == 1)
        i = 2;
    while (cmd->cmd[i])
    {
        tmp = str;
        str = ft_strjoin(str, cmd->cmd[i]);
        free(tmp);
        if (cmd->cmd[i + 1])
        {
            tmp = str;
            str = ft_strjoin(str, " ");
            free(tmp);
        }
        i++;
    }
    cmd->echo_info->echo_str = str;
}

/*----------------------_parsing_export_---------------------------------*/


int init_export_info(t_node *cmd)
{
    char **split;
    char *key_part;
    char *value_part;
    int key_len;

    cmd->info->flag = 0;
    if (cmd->cmd[1] == NULL)
        cmd->info->flag = 1;
    split = ft_split_a(cmd->cmd[1], "=");
    if (!split)
        return (-1);
    key_part = split[0];
    value_part = split[1];
    if (!key_part)
        return (-1);
    key_len = ft_strlen(key_part);
    if (key_len > 0 && key_part[key_len - 1] == '+')
    {
        cmd->info->append = 1;
        key_part[key_len - 1] = '\0';
    }
    else
        cmd->info->append = 0;
    cmd->info->key = ft_strdup(key_part);
    if (!value_part)
        cmd->info->value = ft_strdup("");
    else
        cmd->info->value = ft_strdup(value_part);
    free_split(split);
    return (0);
}

int valide_key(t_node *cmd)
{
    size_t key_len= ft_strlen(cmd->info->key);
    if(isalpha(cmd->info->key[0]) || cmd->info->key[0] == '_')
    {
        if (cmd->info->key[key_len - 1] == ' ')
            return (-1);
        return (0);
    }
    return (-1);
}

