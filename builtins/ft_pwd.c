/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:01:47 by mohben-t          #+#    #+#             */
/*   Updated: 2025/04/29 17:42:56 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(char **envp)
{
    char *pwd;

    pwd = getcwd(NULL,0);
    if (!pwd)
            return (perror("getcwd"), -1);
    ft_putstr_n(pwd);
    free(pwd);
    return (0);
}
