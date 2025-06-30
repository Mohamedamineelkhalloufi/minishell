/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:59:29 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/30 00:01:23 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_has_new_line(t_node *cmd)
{
	int	j;

	cmd->echo_info->new_line = 0;
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-' && cmd->cmd[1][1] == 'n')
	{
		j = 2;
		while (cmd->cmd[1][j] == 'n')
			j++;
		if (cmd->cmd[1][j] == '\0')
			cmd->echo_info->new_line = 1;
	}
}

int	join_args(t_node *cmd, int i)
{
	char	*str;
	char	*new_str;

	str = ft_strdup("");
	if (!str)
		return (-1);
	i = 1 + (cmd->echo_info->new_line == 1);
	while (cmd->cmd[i])
	{
		new_str = ft_strjoin(str, cmd->cmd[i]);
		if (!new_str)
			return (free(str), -1);
		free(str);
		str = new_str;
		if (cmd->cmd[i + 1])
		{
			new_str = ft_strjoin(str, " ");
			if (!new_str)
				return (free(str), -1);
			free(str);
			str = new_str;
		}
		i++;
	}
	return (cmd->echo_info->echo_str = str, 0);
}

void	free_echo_info(t_echo *echo_info)
{
	if (!echo_info)
		return ;
	if (echo_info->echo_str)
		free(echo_info->echo_str);
	free(echo_info);
}

int	init_export_info(char *arg, t_export *info, char **split, char *value_part)
{
	char	*key_part;

	init_export(info);
	if (arg[0] == '=')
		info->fg = 1;
	else
	{
		split = ft_split_a(arg, "=");
		if (!split)
			return (-1);
		key_part = split[0];
		value_part = split[1];
		if (!key_part)
			return (free_split(split), -1);
		if (process_key(info, key_part) == -1)
			return (free_split(split), -1);
		if (!value_part)
			info->value = ft_strdup("");
		else
			info->value = ft_strdup(value_part);
		if (!info->value)
			return (clean_export(info, split), -1);
		free_split(split);
	}
	return (0);
}

int	valide_key(t_export *info)
{
	size_t	key_len;

	if (info->fg == 1)
	{
		ft_putendl_fd("not a valid identifier\n", 2);
		return (-1);
	}
	if (!info->key)
		return (0);
	key_len = ft_strlen(info->key);
	if (isalpha(info->key[0]) || info->key[0] == '_')
	{
		if (info->key[key_len - 1] == ' ')
		{
			ft_putendl_fd("not a valid identifier\n", 2);
			return (-1);
		}
		return (0);
	}
	ft_putendl_fd("not a valid identifier\n", 2);
	return (-1);
}
