/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:34:52 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/05/19 18:34:22 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_all(t_node **all_cmd, char *line, char **s_line,t_env *info)
{
    char *plus;
    int i;

    plus = NULL;
    i = 0;
    if (d_quote(line, 0, 0, 0) == 0 || !check_pipe(line))
        ft_putendl_fd(" Dash@Ameed: syntax error near unexpected", 2);
    else
    {
        plus = expand_line(line, 0, ft_strdup(""),info);
        s_line = ft_split(plus, '|');
        while (s_line[i])
        {
            if (!lexer(all_cmd, s_line[i], NULL))
            {
                free(all_cmd);
                all_cmd = NULL;
                break;
            }
            i++;
        }
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
		return (NULL);
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
