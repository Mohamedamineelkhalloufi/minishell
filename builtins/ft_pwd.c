/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:01:47 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/01 22:23:36 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_node *cmd)
{
	char	*pwd;

	if (cmd)
	{
		if (cmd->cmd[1])
		{
			if (cmd->cmd[1][0] == '-' && cmd->cmd[1][1])
				return (ft_putendl_fd("filed arg!", 2), 2);
		}
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_putendl_fd("getcwd error", 2), -1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
