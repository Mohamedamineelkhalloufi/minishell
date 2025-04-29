/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:52:26 by mohben-t          #+#    #+#             */
/*   Updated: 2025/04/25 16:40:15 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_exit(t_node *cmd)
{
    if (cmd->exit_info->pid == 0)
        exit(cmd->exit_info->status);
    else
    {
        /*
            * free_all_of_things split ...!
            * close all files
        */
       exit(cmd->exit_info->status);
    }
    return (0);
}

