/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirctions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:20:30 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/01 17:45:24 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_output(t_redi *redier)
{
	int	fd;

	fd = open(redier->file_num, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 error\n");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	ft_input(t_redi *redier)
{
	int	fd;

	fd = open(redier->file_num, O_RDONLY);
	if (fd == -1)
	{
		perror("Dash@Ameed:");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	ft_append(t_redi *redier)
{
	int	fd;

	fd = open(redier->file_num, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell\n");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 error\n");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	ft_heredoc(t_redi *redi, t_env *env)
{
	static int	count;
	int			fd;
	char		*tmp;

	if (open_heredoc_file(&tmp, &fd, count++) == -1)
		return (-1);
	if (write_heredoc_loop(redi, env, fd) == -1)
		return (close(fd), free(tmp), -1);
	close(fd);
	redi->heredoc_file = strdup(tmp);
	free(tmp);
	return (0);
}

int	ft_redirect(t_redi *redir, t_env *env)
{
	int	res;

	(void)env;
	res = 0;
	while (redir)
	{
		if (redir->type == 1)
			res = ft_output(redir);
		else if (redir->type == 0)
			res = ft_input(redir);
		else if (redir->type == 2)
			res = ft_append(redir);
		redir = redir->next;
	}
	return (res);
}
