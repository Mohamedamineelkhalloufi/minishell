#include "minishell.h"

void lexer(t_node **test, char *s_line ,char **p_line)
{
    int l = 0;
    int num_cmd = 0;

    p_line = ft_split(fix_line(s_line), ' ');
    if (check_redirections(p_line) == 0)
    {
        printf(" Dash@Ameed: syntax error near unexpected\n");
        return ;
    }
    else
    {
        while (p_line[l])
        {
            if(ft_strchr("<>", p_line[l][0]))
            {
                num_cmd--;
                l++;
            }
            else
            {
                num_cmd++;
                l++;
            }
        }
        *test = creat_node(*test, p_line, num_cmd);
    }
}

int check_redirections(char **p_line)
{
    int i;

    i = 0;
    if(p_line[0] && ft_strchr("<>", p_line[0][0]))
        return (0);
    while(p_line[i])
    {
        if (ft_strchr("<>", p_line[i][0]))
        {
            if (p_line[i][1] && ft_strchr("<>", p_line[i][1]))
            {
                if (p_line[i][1] != p_line[i][0])
                    return (0);
                else if (p_line[i][2])
                    return (0);
            }
            else if (p_line[i + 1] && ft_strchr("<>", p_line[i + 1][0]))
                return (0);
        }
        i++;
    }
    if(p_line[i - 1] && ft_strchr("<>", p_line[i - 1][0]))
        return (0);
    return (1);
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
        new_redi->type = 1;
        new_redi->next = NULL;
    }
    if (check_split(check, 0, '\0') == 2)
    {
        new_redi->file_num = file_num;
        new_redi->type = 2;
        new_redi->next = NULL;
    }
    if (check_split(check, 0, '\0') == 3)
    {
        new_redi->file_num = file_num;
        new_redi->type = 3;
        new_redi->next = NULL;
    }
    if (check_split(check, 0, '\0') == 4)
    {
        new_redi->file_num = file_num;
        new_redi->type = 4;
        new_redi->next = NULL;
    }
    if (!head)
        return (new_redi);
    stor_head = head;
    while (stor_head->next)
        stor_head = stor_head->next;
    stor_head->next = new_redi;
    return head;
}