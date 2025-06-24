/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:52:26 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/24 04:25:04 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_numeric(const char *str)
{
    int i = 0;

    if (!str)
        return (0);
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}


int ft_exit(t_node *cmd, t_env *env)
{
    int exit_code = g_es;

    if (cmd->cmd[1])
    {
        if (!is_numeric(cmd->cmd[1]))
        {
            ft_putstr_fd("exit: numeric argument required\n", 2);
            free_all_commands(cmd);
            free_env(env);
            exit(255);
        }
        if (cmd->cmd[2])
        {
            ft_putstr_fd("exit: too many arguments\n", 2);
            return (1);
        }
        exit_code = ft_atoi(cmd->cmd[1]) % 256;
        if (exit_code < 0)
            exit_code += 256;
    }
    free_all_commands(cmd);
    free_env(env);
    write(1,"exit\n",5);
    exit(exit_code);
}
