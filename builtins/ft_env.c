/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:21:48 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/01 22:22:18 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *cmd, t_node *node)
{
	int	i;

	if (lenght_cmd(node->cmd) != 1)
		return (ft_putendl_fd("env : too many arguments", 2), 127);
	i = 0;
	while (cmd->my_envp[i])
	{
		if (strchr(cmd->my_envp[i], '='))
			printf("%s\n", cmd->my_envp[i]);
		i++;
	}
	return (0);
}
