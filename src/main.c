/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:39:07 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/07/01 17:56:17 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_es = 0;

void	free_all_commands(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head;
		if (head->cmd)
			free_split(head->cmd);
		if (head->file)
			free_redi_list(head->file);
		head = head->next;
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	free_split(env->my_envp);
	free(env);
}

static void	cleanup_and_exit(t_env *env, t_node *head)
{
	free_all_commands(head);
	if (env)
		free_env(env);
	exit(0);
}

static int	process_input(char *line, t_node **head, t_env *env)
{
	add_history(line);
	if (ft_all(head, line, NULL, env) == 1)
		return (1);
	if (*head)
	{
		free_heredoc(*head, env, NULL);
		pipe_hundel(*head, env);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_node	*head;
	char	*line;

	(void)av;
	if (ac != 1)
		return (1);
	env = NULL;
	signal_setup();
	while (1)
	{
		head = NULL;
		line = readline("\033[32mDash@Ameed$ \033[0m");
		if (!env)
			env = envp_dup(envp);
		if (!line)
			cleanup_and_exit(env, head);
		if (process_input(line, &head, env) == 1)
		{
			free(line);
			continue ;
		}
		free(line);
	}
	return (rl_clear_history(), 0);
}
