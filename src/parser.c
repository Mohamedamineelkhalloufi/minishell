/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:39:14 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/05/26 12:00:31 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*creat_node(t_node *head, char **cmd, int num_cmd)
{
	t_node	*new_node;
	t_node	*tmp;

	if (!cmd)
		return (NULL);
	new_node = init_node(num_cmd);
	if (!new_node)
		return (NULL);
	process_cmd(new_node, cmd);
	if (!head)
		return (new_node);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (head);
}

void	process_cmd(t_node *new_node, char **cmd)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (cmd[i])
	{
		if (ft_strchr("<>", cmd[i][0]) && cmd[i + 1])
		{
			new_node->file = creat_file(new_node->file, qoute_remov(cmd[i + 1],
						0, 0, 0), cmd[i]);
			i += 2;
		}
		else
			new_node->cmd[l++] = qoute_remov(cmd[i++], 0, 0, 0);
	}
	new_node->cmd[l] = NULL;
}

t_redi	*creat_file(t_redi *head, char *file_num, char *check)
{
	t_redi	*new_redi;

	if (!file_num)
		return (NULL);
	new_redi = malloc(sizeof(t_redi));
	if (!new_redi)
		return (NULL);
	set_redi_type(new_redi, check);
	new_redi->file_num = file_num;
	new_redi->next = NULL;
	if (!head)
		return (new_redi);
	add_redi_to_list(head, new_redi);
	return (head);
}

void	set_redi_type(t_redi *new_redi, char *check)
{
	int	check_result;

	check_result = check_split(check, 0, '\0');
	if (check_result == 1)
		new_redi->type = 1;
	else if (check_result == 2)
		new_redi->type = 2;
	else if (check_result == 3)
		new_redi->type = 0;
	else if (check_result == 4)
		new_redi->type = 3;
}

void	add_redi_to_list(t_redi *head, t_redi *new_redi)
{
	t_redi	*stor_head;

	stor_head = head;
	while (stor_head->next)
		stor_head = stor_head->next;
	stor_head->next = new_redi;
}
