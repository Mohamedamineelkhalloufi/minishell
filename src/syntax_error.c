/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:38:37 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/05/26 12:00:20 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// had lft tatchof lina dak line wash fih << >> < > bash nsplitiw bih
int	check_split(char *line, int i, char q)
{
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i];
			i++;
			while (line[i] && line[i] != q)
				i++;
			i++;
		}
		if (line[i] == '>')
		{
			if (line[i + 1] && line[i + 1] == '>')
				return (2);
			return (1);
		}
		if (line[i] == '<')
		{
			if (line[i + 1] && line[i + 1] == '<')
				return (4);
			return (3);
		}
		i++;
	}
	return (0);
}

// had lft tatchof lina wash line fih chi " oula ' mamsdodch
int	d_quote(char *line, int dquote, int quote, int i)
{
	char	q;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i++];
			if (q == '\"')
				dquote++;
			else
				quote++;
			while (line[i] && line[i] != q)
				i++;
			if (line[i] == '\0')
				break ;
			if (line[i] == '\"')
				dquote++;
			if (line[i] == '\'')
				quote++;
		}
		i++;
	}
	if (dquote % 2 != 0 || quote % 2 != 0)
		return (0);
	return (1);
}

// had lft tatchof lina wash line tibda oula tisali b | oula fih joj dyal | mtab3in

int	check_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && line[i] == '|')
		return (0);
	i = if_check_pipe(line, i, '\0');
	if (i == -1)
		return (0);
	i--;
	while (i >= 0 && line[i] == ' ')
		i--;
	if (i >= 0 && line[i] == '|')
		return (0);
	return (1);
}

int	if_check_pipe(char *line, int i, char q)
{
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i++];
			while (line[i] && line[i] != q)
				i++;
			if (line[i])
				i++;
		}
		else if (line[i] == '|')
		{
			i++;
			if (line[i] && line[i] == '|')
				return (-1);
			while (line[i] && line[i] == ' ')
			{
				i++;
				if (line[i] && line[i] == '|')
					return (-1);
			}
		}
		else
			i++;
	}
	return (i);
}

char	*qoute_remov(char *line, char q, int i, int l)
{
	char *new_line;

	new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			q = line[i++];
			while (line[i] && line[i] != q)
				new_line[l++] = line[i++];
			if (line[i])
				i++;
		}
		else
			new_line[l++] = line[i++];
	}
	new_line[l] = '\0';
	return (new_line);
}