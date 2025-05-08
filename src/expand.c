#include "../minishell.h"

char *find_end(char *start)
{
    int i;

    i = 1;
    if (start[i] && start[i] == '?')
        return (ft_substr(start + 1, 0, i));
    if (start[i] && ft_isdigit(start[i]))
        return (ft_substr(start + 1, 0, i));
    while (start[i] && ft_isalnum(start[i]))
        i++;
    return (ft_substr(start + 1, 0, i - 1));
}

char *expand_val(char *s)
{
    char *start;
    char *dollar = NULL;
    char *temp;
    int i = 0;

    if ((start = ft_strnstr(s, "$", ft_strlen(s))))
    {
        if (!start[1])
            return (ft_strdup("$"));
        if (start[1] && start[1] == '$')
        {
            while (start[i] && start[i] == '$')
                i++;
            return (ft_substr(start, 0, i - 1));
        }
        dollar = find_end(start);
        if (!dollar)
        return NULL;
        temp = dollar;
        dollar = getenv(temp);
        free(temp);
        if (dollar)
            return (dollar);
        else if (start[1] && !ft_isalnum(start[1]))
            return ("$");
        else
            return ("");
    }
    return NULL;
}

char *expand_line(char *line, int dquote , char *plus)
{
    while (line && *line)
        {
            size_t i = 0;
            while (line[i] && line[i] != '$')
            {
                if (line[i] == '\"')
                {
                    if (!dquote)
                        dquote = 1;
                    else
                        dquote = 0;
                    i++;
                }
                else if (line[i] == '\'' && !dquote)
                {
                    i++;
                    while (line[i] && line[i] != '\'')
                        i++;
                    if (line[i])
                        i++;
                }
                else
                    i++;
            }
            char *line_plus = ft_substr(line, 0, i);
            plus = ft_strjoin(plus, line_plus);
            if (line[i] == '$')
            {
                line += i;
                i = 1;
                char *expanded = expand_val(line);
                plus = ft_strjoin(plus, expanded);
                if (line[i] && (line[i] == '?' || ft_isdigit(line[i])))
                    i++;
                else if (line[i] && line[i] == '$')
                {
                    while (line[i] && line[i] == '$')
                        i++;
                    i--;
                }
                else
                {
                    while (line[i] && ft_isalnum(line[i]))
                        i++;
                }
            }
            line += i;
        }
        return (plus);
    }