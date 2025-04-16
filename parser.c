#include "minishell.h"

t_node *init_node(int num_cmd)
{
    t_node *new_node;

    // (void)num_cmd;
    new_node = malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
    new_node->cmd = (char **)malloc((sizeof(char *) * num_cmd) + 1);
    if (!new_node->cmd)
        return NULL;
    new_node->file = NULL;
    new_node->next = NULL;
    return (new_node);
}

#include "minishell.h"

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
			new_node->file = creat_file(new_node->file, cmd[i + 1], cmd[i]);
			i += 2;
		}
		else
		{
			new_node->cmd[l] = cmd[i];
			l++;
			i++;
		}
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
