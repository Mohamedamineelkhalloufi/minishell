/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:25:49 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/09 12:45:18 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_node *cmd)
{
    int i;

    i = 0;
    if (!(echo_has_new_line(cmd)))
        return (0);
    join_args(cmd);
    if (cmd->echo_info->new_line == 1) // we have option , must be display string without "\n"
        ft_putstr(cmd->echo_info->echo_str);
    else
        ft_putendl_fd(cmd->echo_info->echo_str,1); //display with "\n"
    printf("valid!!\n");
    return (0);
}
