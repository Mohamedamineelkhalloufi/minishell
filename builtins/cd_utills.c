/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utills.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:26:52 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/20 16:28:53 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int update_env_variable(const char *key, const char *value, char **envp)
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

int update_pwd_variables(char *oldpwd, char *pwd, t_env *env)
{
    update_env_variable("OLDPWD=", oldpwd, env->my_envp);
    update_env_variable("PWD=", pwd, env->my_envp);
    return (0);
}

int change_directory(const char *target_dir, t_env *env)
{
    char *oldpwd;
    char *pwd;
    
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
        return (perror("getcwd"),1);
    if (chdir(target_dir)!= 0)
    {
		if (target_dir)
		{
			if(ft_strcmp(target_dir ,""))
        	    ft_putendl_fd("cd: No such file or directory",2);
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
    return (free(oldpwd),free(pwd),0);
}
