/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:34:52 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/07/01 18:25:50 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_all(t_node **all_cmd, char *line, char **s_line, t_env *info)
{
	char	*plus;
	int		i;

	plus = NULL;
	i = 0;
	if (!d_quote(line, 0, 0, 0) || !check_pipe(line))
	{
		g_es = 2;
		ft_putendl_fd("Dash@Ameed: syntax error near unexpected", 2);
		return (1);
	}
	else
	{
		s_line = expand_and_split(line, info);
		if (!s_line)
			return (1);
		while (s_line[i])
		{
			if (!lexer(all_cmd, s_line[i++], NULL))
				return (free_all_commands(*all_cmd), free_split(s_line), 1);
		}
		free_split(s_line);
		return (0);
	}
}

t_node	*init_node(int num_cmd)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->cmd = (char **)malloc((sizeof(char *) * (num_cmd + 1)));
	if (!new_node->cmd)
		return (free_node(new_node), NULL);
	new_node->file = NULL;
	new_node->next = NULL;
	return (new_node);
}

int	handle_quotes(char *line, char *new_line, int *i, int *l)
{
	char	q;

	q = line[*i];
	new_line[(*l)++] = line[(*i)++];
	while (line[*i] && line[*i] != q)
		new_line[(*l)++] = line[(*i)++];
	if (line[*i])
		new_line[(*l)++] = line[(*i)++];
	return (1);
}

int	handle_redirects(char *line, char *new_line, int *i, int *l)
{
	new_line[(*l)++] = ' ';
	while (line[*i] && (line[*i] == '<' || line[*i] == '>'))
		new_line[(*l)++] = line[(*i)++];
	new_line[(*l)++] = ' ';
	return (1);
}

char	*handle_dollar_case(char *start)
{
	int	i;

	i = 0;
	while (start[i] && start[i] == '$')
		i++;
	return (ft_substr(start, 0, i - 1));
}
