/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:29:29 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/30 00:00:37 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_key(const char *key, char **envp)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	func_print(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

int	process_single_export(char *arg, t_env **env)
{
	t_export	info;
	int			i;

	if (init_export_info(arg, &info, NULL, NULL) == -1)
		return (1);
	if (valide_key(&info) == -1)
	{
		free(info.key);
		free(info.value);
		return (1);
	}
	i = get_key(info.key, (*env)->my_envp);
	if (i > -1)
		update_existing_env(&info, env, i);
	else
		add_new_env(&info, env);
	free(info.key);
	free(info.value);
	return (0);
}

int	ft_export(t_node *cmd, t_env **env)
{
	int	i;
	int	ret;

	if (cmd->cmd[1] == NULL)
		return (ft_sort(*env), func_print((*env)->my_envp), 0);
	i = 1;
	ret = 0;
	while (cmd->cmd[i])
	{
		if (process_single_export(cmd->cmd[i], env) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
