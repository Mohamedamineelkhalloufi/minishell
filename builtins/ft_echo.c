/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:25:49 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/26 12:02:00 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_node *cmd)
{
    int i;
    
    i = 0;
    cmd->echo_info = malloc(sizeof(t_echo));
    if (!cmd->echo_info)
        return(1);
    echo_has_new_line(cmd);
    join_args(cmd);
    if (cmd->echo_info->new_line == 1)
        ft_putstr(cmd->echo_info->echo_str);
    else
        ft_putendl_fd(cmd->echo_info->echo_str,1);
    return (0);
}
