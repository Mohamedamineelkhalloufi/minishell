/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:08:49 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/06/19 01:12:38 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	h_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_es = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
void free_heredoc(t_node *cmd, t_env *env, char *tmp)
{
	static t_node *node;
	static t_env *env_plus;
	static char *tmp_plus;
	if(cmd && env)
	{
		env_plus = env;
		node = cmd;
	}
	else if (tmp)
		tmp_plus = tmp;
	else
	{
		free(tmp_plus);
		free_env(env_plus);
		free_all_commands(node);	
	}
}
void	g_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_es = 130;
		write(1, "\n", 1);
		free_heredoc(NULL, NULL, NULL);
	}
	exit(g_es); 
}

void	signal_setup(void)
{
	signal(SIGINT, h_handler);
	signal(SIGQUIT, SIG_IGN);
}
