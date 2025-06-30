/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:24:28 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/29 10:31:33 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_env_string(char *key, char *value)
{
	char	*temp3;
	char	*result;

	if (value && *value != '\0')
	{
		temp3 = ft_strjoin(key, "=");
		result = ft_strjoin(temp3, value);
		free(temp3);
	}
	else
		result = ft_strdup(key);
	return (result);
}

char	*handle_value_update(t_export *info, char *old_value)
{
	char	*tmp1;

	if (info->append == 1)
		tmp1 = ft_strjoin1(old_value, info->value);
	else
	{
		if (info->value)
			tmp1 = ft_strdup(info->value);
		else
			tmp1 = NULL;
	}
	return (tmp1);
}

int	update_existing_env(t_export *info, t_env **env, int index)
{
	char	*old_value;
	char	*tmp1;
	char	*tmp2;

	old_value = get_env_value(info->key, (*env)->my_envp);
	tmp1 = handle_value_update(info, old_value);
	tmp2 = create_env_string(info->key, tmp1);
	free((*env)->my_envp[index]);
	(*env)->my_envp[index] = tmp2;
	if (tmp1)
		free(tmp1);
	if (old_value && info->append != 1)
		free(old_value);
	return (0);
}

int	add_new_env(t_export *info, t_env **env)
{
	char	*tmp2;

	(*env)->my_envp = realloc_env((*env)->my_envp, (*env)->env_len,
			(*env)->env_len + 1);
	if (info->value[0] == '\0')
		tmp2 = ft_strdup(info->key);
	else
		tmp2 = create_env_string(info->key, info->value);
	(*env)->my_envp[(*env)->env_len] = tmp2;
	(*env)->env_len++;
	(*env)->my_envp[(*env)->env_len] = NULL;
	return (0);
}
