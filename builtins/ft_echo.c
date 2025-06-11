/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:25:49 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/11 16:34:58 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_node *cmd)
{
    cmd->echo_info = malloc(sizeof(t_echo));
    if (!cmd->echo_info)
        return (1);
    echo_has_new_line(cmd);
    if (join_args(cmd) != 0)
    {
        free_echo_info(cmd->echo_info);
        cmd->echo_info = NULL;
        return (1);
    }
    if (cmd->echo_info->new_line == 1)
        ft_putstr(cmd->echo_info->echo_str);
    else
        ft_putendl_fd(cmd->echo_info->echo_str, 1);
    free_echo_info(cmd->echo_info);
    cmd->echo_info = NULL;
    return (0);
}
