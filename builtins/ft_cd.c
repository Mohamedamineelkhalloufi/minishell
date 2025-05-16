/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:35:34 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/16 15:25:58 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int get_first_index_of_value(const char *key, char **envp)
{
    int		i = 0;
	size_t	key_len = ft_strlen(key);

	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int ft_cd(t_node *cmd,t_env *env)
{
    char *oldpwd;
    char *pwd;
    int i;
    char *tmp;
    char *target_dir;

    if (!cmd->cmd[1]) // No argument: go to $HOME
    {
        int home_index = get_first_index_of_value("HOME", env->my_envp);
        if (home_index == -1)
        {
            printf("cd: HOME not set\n");
            //g_exit_status = 1;
            return (-1);
        }
        target_dir = ft_strdup(env->my_envp[home_index] + 5); // Skip "HOME="
    }
    else
    {
        target_dir = ft_strdup(cmd->cmd[1]);
    }

    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
    {
        perror("getcwd");
        free(target_dir);
        // g_exit_status = 1;
        return (-1); 
    }

    if (chdir(target_dir) == 0)
    {
        pwd = getcwd(NULL, 0);
        if (!pwd)
        {
            perror("getcwd");
            free(oldpwd);
            free(target_dir);
            // g_exit_status = 1;
            return (-1);
        }

        i = get_first_index_of_value("OLDPWD", env->my_envp);
        if (i != -1)
        {
            tmp = ft_strjoin("OLDPWD=", oldpwd);
            free(env->my_envp[i]);
            env->my_envp[i] = tmp;
        }

        i = get_first_index_of_value("PWD", env->my_envp);
        if (i != -1)
        {
            tmp = ft_strjoin("PWD=", pwd);
            free(env->my_envp[i]);
            env->my_envp[i] = tmp;
        }

        free(oldpwd);
        free(pwd);
        // g_exit_status = 0;
    }
    else
    {
        printf("cd: %s: No such file or directory\n", target_dir);
        free(oldpwd);
        // g_exit_status = 1;
        free(target_dir);
        return (-1);
    }

    free(target_dir);
    return (0);
}
