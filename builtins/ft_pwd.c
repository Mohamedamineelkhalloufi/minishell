/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:01:47 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/11 16:36:11 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(t_node *cmd)
{
    char *pwd;
    
    (void)cmd;
    pwd = getcwd(NULL, 0);
    if (!pwd)
        return (dprintf(2,"getcwd error\n"),-1);
    ft_putendl_fd(pwd, 1);
    free(pwd);
    return (0);
}
