/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:34:33 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/29 10:38:29 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_key(t_export *info, char *key_part)
{
	int	key_len;

	key_len = ft_strlen(key_part);
	if (key_len > 0 && key_part[key_len - 1] == '+')
	{
		info->append = 1;
		key_part[key_len - 1] = '\0';
	}
	info->key = ft_strdup(key_part);
	if (!info->key)
		return (-1);
	return (0);
}

void	init_export(t_export *info)
{
	info->key = NULL;
	info->value = NULL;
	info->append = 0;
	info->fg = 0;
}

void	clean_export(t_export *info, char **split)
{
	free(info->key);
	info->key = NULL;
	free_split(split);
}
