/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:35:34 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/03 16:17:42 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int get_first_index_of_value(const char *key, char **envp)
{
    int     i = 0;
    size_t  key_len = ft_strlen(key);

    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
            return (i);
        i++;
    }
    return (-1);
}

static char *get_target_directory(char **cmd_args, char **envp)
{
    int home_index;
    char *target_dir;

    if (!cmd_args[1])
    {
        home_index = get_first_index_of_value("HOME", envp);
        if (home_index == -1)
        {
            printf("cd: HOME not set\n");
            return (NULL);
        }
        target_dir = ft_strdup(envp[home_index] + 5);
    }
    else
    {
        target_dir = ft_strdup(cmd_args[1]);
    }
    return (target_dir);
}

static int update_env_variable(const char *key, const char *value, char **envp)
{
    int i;
    char *tmp;

    i = get_first_index_of_value(key, envp);
    if (i != -1)
    {
        tmp = ft_strjoin(key, value);
        free(envp[i]);
        envp[i] = tmp;
        return (0);
    }
    return (1);
}

static int update_pwd_variables(char *oldpwd, char *pwd, t_env *env)
{
    update_env_variable("OLDPWD=", oldpwd, env->my_envp);
    update_env_variable("PWD=", pwd, env->my_envp);
    return (0);
}

static int change_directory(const char *target_dir, t_env *env)
{
    char *oldpwd;
    char *pwd;
    
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
	{
        return (perror("getcwd"),1);
	}
    if (chdir(target_dir) != 0)
    {
		if (target_dir)
		{
			printf("debug\n");
        	dprintf(2,"cd: %s: No such file or directory\n", target_dir);
		}
        free(oldpwd);
        return (1);
    }
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        perror("getcwd");
        free(oldpwd);
        return (1);
    }
    update_pwd_variables(oldpwd, pwd, env);
    free(oldpwd);
    free(pwd);
    return (0);
}

int ft_cd(t_node *cmd, t_env *env)
{
    char *target_dir;
    int result;
    
    target_dir = get_target_directory(cmd->cmd, env->my_envp);
    if (!target_dir)
        return (1);
    result = change_directory(target_dir, env);
    free(target_dir);
    return (result);
}
