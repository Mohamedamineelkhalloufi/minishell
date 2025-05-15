/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:25:49 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/15 14:50:48 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_node *cmd)
{
    printf("------------\n");
    int i;

    i = 0;
    echo_has_new_line(cmd);
    join_args(cmd);
    if (cmd->echo_info->new_line == 1) // we have option , must be display string without "\n"
        ft_putstr(cmd->echo_info->echo_str);
    else
        ft_putendl_fd(cmd->echo_info->echo_str,1); //display with "\n"
    printf("valid!!\n");
    return (0);
}
