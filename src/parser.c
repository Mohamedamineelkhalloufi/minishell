#include "../minishell.h"

t_node *init_node(int num_cmd)
{
    t_node *new_node;

    new_node = malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
    new_node->cmd = (char **)malloc((sizeof(char *) * (num_cmd + 1)));
    if (!new_node->cmd)
        return NULL;
    new_node->file = NULL;
    new_node->next = NULL;
    return (new_node);
}
t_node	*creat_node(t_node *head, char **cmd, int num_cmd)
{
	t_node	*new_node;
	t_node	*tmp;
	int		i;
	int		l;

	if (!cmd)
		return (NULL);
	new_node = init_node(num_cmd);
	if (!new_node)
		return (NULL);
	i = 0;
	l = 0;
	while (cmd[i])
	{
		if (ft_strchr("<>", cmd[i][0]) && cmd[i + 1])
		{
			new_node->file = creat_file(new_node->file, qoute_remov(cmd[i + 1]), cmd[i]);
			i += 2;
		}
		else
			new_node->cmd[l++] = qoute_remov(cmd[i++]);
	}
	new_node->cmd[l] = NULL;
	if (!head)
		return (new_node);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (head);
}

t_redi *creat_file(t_redi *head, char *file_num, char *check)
{
    t_redi *new_redi;
    t_redi *stor_head;
    if (!file_num)
        return NULL;
    new_redi = malloc(sizeof(t_redi));
    if (!new_redi)
        return NULL;
    if (check_split(check, 0, '\0') == 1)
    {
        new_redi->file_num = file_num;
        new_redi->type = FILE_OUT;
    }
    if (check_split(check, 0, '\0') == 2)
    {
        new_redi->file_num = file_num;
        new_redi->type = FILE_APPEND;
    }
    if (check_split(check, 0, '\0') == 3)
    {
        new_redi->file_num = file_num;
        new_redi->type = FILE_IN;
    }
    if (check_split(check, 0, '\0') == 4)
    {
        new_redi->file_num = file_num;
        new_redi->type = FILE_HEREDOC;
    }
    new_redi->next = NULL;
    if (!head)
        return (new_redi);
    stor_head = head;
    while (stor_head->next)
        stor_head = stor_head->next;
    stor_head->next = new_redi;
    return head;
}