/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:56:02 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/23 18:03:00 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_end(char *start)
{
	int	i;

	i = 1;
	if (start[i] && start[i] == '?')
		return (ft_substr(start + 1, 0, i));
	if (start[i] && ft_isdigit(start[i]))
		return (ft_substr(start + 1, 0, i));
	while (start[i] && ft_isalnum(start[i]))
		i++;
	return (ft_substr(start + 1, 0, i - 1));
}

void free_redi_list(t_redi *r)
{
    t_redi *tmp;
    while (r)
    {
        tmp = r;
        if (r->file_num)
            free(r->file_num);
        if (r->heredoc_file)
            free(r->heredoc_file);
        r = r->next;
        free(tmp);
    }
}
void free_node(t_node *node)
{
    int i;
    
    if (!node)
        return;
    if (node->cmd)
    {
        i = 0;
        while (node->cmd[i])
        {
            free(node->cmd[i]);
            i++;
        }
        free(node->cmd);
    }
    
    free(node);
}