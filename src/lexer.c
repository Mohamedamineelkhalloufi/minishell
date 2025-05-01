#include "../minishell.h"

int lexer(t_node **test, char *s_line ,char **p_line)
{
    int cmd_num;

    cmd_num = 0;
    p_line = ft_split(fix_line(s_line), ' ');
    if (check_redirections(p_line) == 0)
    {
        printf(" Dash@Ameed: syntax error near unexpected\n");
        return (0);
    }
    else
    {
        cmd_num = num_cmd(p_line);
        *test = creat_node(*test, p_line, cmd_num);
    }
    return (1);
}

int num_cmd(char **p_line)
{
    int num_cmd;
    int l;

    num_cmd = 0;
    l = 0;
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
    return (num_cmd);
}

int check_redirections(char **p_line)
{
    int i;

    i = 0;
    if(p_line[0] && ft_strchr("<>", p_line[0][0]) && !p_line[1])
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
    if(i > 0 && p_line[i - 1] && ft_strchr("<>", p_line[i - 1][0]))
        return (0);
    return (1);
}

int len_forma(char *line, int i, int l)
{
    char q;

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
        else if (ft_strchr("<>", line[i]))
        {
            l += 2;
            while (line[i] && ft_strchr("<>", line[i]))
                i++;
        }
        else
            i++;
    }
    return (l + i + 1);
}

char *fix_line(char *line)
{
    char *new_line = NULL;
    char q;
    int i = 0;
    int l = 0;

    new_line = malloc(len_forma(line, 0, 0) * sizeof(char));
    if (!new_line)
        return NULL;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            q = line[i];
            new_line[l++] = line[i++];
            while (line[i] && line[i] != q)
                new_line[l++] = line[i++];
            if (line[i])
                new_line[l++] = line[i++];
        }
        else if (ft_strchr("<>", line[i]))
        {
            new_line[l++] = ' ';
            while (line[i] && ft_strchr("<>", line[i]))
                new_line[l++] = line[i++];
            new_line[l++] = ' ';
        }
        else
            new_line[l++] = line[i++];
    }
    new_line[l] = '\0';
    return new_line;
}
