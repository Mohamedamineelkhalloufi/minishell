/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:58:23 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/23 17:53:49 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *envp_dup(char **envp)
{
	int i;
	int env_len;

	env_len = 0;
	 t_env *cmd = malloc(sizeof(t_env));
	while (envp[env_len])
		env_len++;
	cmd->my_envp = (char **)malloc((env_len + 1) * sizeof(char *));
	if (!cmd->my_envp)
		return(NULL);
	i = 0;
	while (envp[i])
	{
		cmd->my_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	cmd->my_envp[i] = NULL;
	cmd->env_len = env_len;
	
	return (cmd);
}

char **realloc_env(char **old_env, int old_size, int new_size)
{
	char **new_env = malloc((new_size + 1) * sizeof(char *));
	int i = 0;

	if (!new_env)
		return NULL;
	while (i < old_size)
	{
		new_env[i] = ft_strdup(old_env[i]);
		free(old_env[i]);
		i++;
	}
	new_env[i] = NULL;
	free(old_env);
	return (new_env);
}


char *get_env_value(const char *key, char **envp)
{
	int		i = 0;
	size_t	key_len = ft_strlen(key);

	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (ft_strdup(envp[i] + key_len + 1));
		i++;
	}
	return (NULL);
}

void error_exit(const char *msg)
{
    perror(msg);
    exit(-1);
}

char *resolve_path(char *command, char **envp, int i)
{ 
	char	*path_env;
	char	**paths;
	char	*full_path;

	if(access(command,X_OK|F_OK) != -1)
		return (command);
	path_env = get_env_value("PATH",envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		char *temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (free_split(paths),full_path);
		free(full_path);
		i++;
	}
	return (free_split(paths), NULL);
}
