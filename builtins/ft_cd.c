/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:35:34 by mohben-t          #+#    #+#             */
/*   Updated: 2025/04/21 11:02:29 by mohben-t         ###   ########.fr       */
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
int ft_cd(t_node *cmd,char **envp)
{
    char *oldpwd;
    char *pwd;
    int i;
    char *tmp;

    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
            return (perror("getcwd"), -1);
    if (chdir(cmd->cmd[1]) == 0)
    {
        pwd = getcwd(NULL, 0);
        if (!pwd)
            return (free(oldpwd), perror("getcwd"), -1);
        i = get_first_index_of_value("OLDPWD", envp);
        if (i != -1)
        {
            tmp = ft_strjoin("OLDPWD=", oldpwd);
            free(envp[i]);
            envp[i] = tmp;
        }
        i = get_first_index_of_value("PWD", envp);
        if (i != -1)
        {
            tmp = ft_strjoin("PWD=", pwd);
            free(envp[i]);
            envp[i] = tmp;
        }
        
    }
    else
        error_exit("cd: not_exist: No such file or directory\n");
    return (0);
}
