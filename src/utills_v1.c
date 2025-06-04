/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:58:23 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/03 16:09:38 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void envp_dup(t_env *cmd, char **envp)
{
	int i;
	int env_len;
	char **str_env;

	env_len = 0;
	while (envp[env_len])
		env_len++;
	str_env = (char **)malloc((env_len + 1) * sizeof(char *));
	if (!str_env)
		return;
	i = 0;
	while (i < env_len)
	{
		str_env[i] = ft_strdup(envp[i]);
		i++;
	}
	str_env[i] = NULL;
	cmd->my_envp = str_env;
	cmd->env_len = env_len;
	// free(str_env);
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
			return (envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

void error_exit(const char *msg)
{
    perror(msg);
    exit(-1);
}

char *resolve_path(char *command, char **envp)
{ 
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i = 0;

	path_env = get_env_value("PATH",envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		char *temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			// printf("here\n");
			//ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	//ft_free_split(paths);
	return (NULL);
}
int get_num_commands(t_node *cmd)
{
    int count = 0;
    while (cmd != NULL)
    {
        count++;
        cmd = cmd->next;
    }
    return count;
}

void ft_sort(t_env *cmd)
{
	int i;
	int j;
	char *temp;

	i = 0;
	while (cmd->my_envp[i])
	{
		j = 0;
		while (cmd->my_envp[j + 1])
		{
			if (strcmp(cmd->my_envp[j], cmd->my_envp[j + 1]) > 0)
			{
				temp = cmd->my_envp[j];
				cmd->my_envp[j] = cmd->my_envp[j + 1];
				cmd->my_envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}



int is_builtin(t_node *cmd)
{
	int i;

    if (!cmd || !cmd->cmd || !cmd->cmd[0])
        return 0;

    const char *builtins[] = {"cd", "echo", "env", "export", "pwd", "exit", "unset", NULL};
    i = 0;
	while (builtins[i])
	{
        if (ft_strcmp(cmd->cmd[0], builtins[i]) == 0)
            return 1;
		i++;
    }
    return 0;
}

int builtin_requires_parent(t_node *cmd)
{
	int i;

    if (!cmd || !cmd->cmd || !cmd->cmd[0])
        return 0;

    const char *parent_builtins[] = {"cd", "export", "unset", "exit", NULL};
	i = 0;
    while (parent_builtins[i])
	{
        if (ft_strcmp(cmd->cmd[0], parent_builtins[i]) == 0)
            return 1;
		i++;
    }
    return 0;
}


int exec_builtins(t_node *cmd,t_env *env)
{
	int res;

	res = 1;
	if (is_builtin(cmd) == 1)
	{
		if (ft_strcmp(cmd->cmd[0], "cd") == 0)
				res = ft_cd(cmd,env);
		else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
			res = ft_echo(cmd);
		else if (ft_strcmp(cmd->cmd[0], "env") == 0)
			res = ft_env(env);
		else if (ft_strcmp(cmd->cmd[ 0], "exit") == 0)
			res = ft_exit(cmd);
		else if (ft_strcmp(cmd->cmd[0], "export") == 0)
			res = ft_export(cmd,&env);
		else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
			res = ft_pwd(cmd);
		else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
			res = ft_unset(cmd,&env);
	}
	return (res);
}