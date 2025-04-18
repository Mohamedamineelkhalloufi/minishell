#include "../minishell.h"

static char *get_env_value(const char *key, char **envp)
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
    exit(EXIT_FAILURE);
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