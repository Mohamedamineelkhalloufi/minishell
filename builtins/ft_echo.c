/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:25:49 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/01 17:58:31 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pipe_syntax_error(char *line, int i)
{
	if (line[i] && line[i] == '|')
		return (-1);
	while (line[i] && line[i] == ' ')
	{
		i++;
		if (line[i] && line[i] == '|')
			return (-1);
	}
	return (i);
}

char	**expand_and_split(char *line, t_env *info)
{
	char	*expanded;
	char	**split_line;

	expanded = expand_line(line, 0, ft_strdup(""), info);
	if (!expanded)
		return (NULL);
	split_line = ft_split(expanded, '|');
	free(expanded);
	return (split_line);
}

int	ft_echo(t_node *cmd)
{
	cmd->echo_info = malloc(sizeof(t_echo));
	if (!cmd->echo_info)
		return (1);
	echo_has_new_line(cmd);
	if (join_args(cmd, 0) != 0)
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
