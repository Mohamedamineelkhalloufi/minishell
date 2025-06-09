/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:08:49 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/06/09 16:26:26 by mohel-kh         ###   ########.fr       */
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

void	signal_setup(void)
{
	signal(SIGINT, h_handler);
	signal(SIGQUIT, SIG_IGN);
}
