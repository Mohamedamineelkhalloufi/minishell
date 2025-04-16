#include "minishell.h"

int len_forma(char *line)
{
    int i = 0;
    int l = 0;
    while (line[i])
    {
        if (ft_strchr("<>",line[i]))
        {
            l += 2; 
            while (line[i] && ft_strchr("<>",line[i]))
                i++;
        }
        i++;
    }
    return (l + i);
}

char *fix_line(char *line)
{
    char *new_line = NULL;
    int i = 0;
    int l = 0;

    new_line = malloc((len_forma(line) * sizeof(char)) + 1);
    if(!new_line)
        return(NULL);
    while (line[i])
    {
        if (ft_strchr("<>",line[i]))
        {
            new_line[l++] = ' ';
            while (line[i] && ft_strchr("<>",line[i]))
                new_line[l++] = line[i++];
            new_line[l++] = ' ';
        }
        new_line[l++] = line[i++];
    }
    new_line[l] = '\0';
    return (new_line);
}


int main()
{
    char *line;
    char **s_line = NULL;

    while (1)
    {
        t_node *test = NULL;
        line = readline("\033[32m Dash@Ameed$ \033[0m");
        if (!line)
            return 0;
        add_history(line);
        int i = 0;
        if (d_quote(line, 0, 0, 0) == 0 || check_pipe(line) == 0)
            printf(" Dash@Ameed: syntax error near unexpected\n");
        else
        {
            s_line = ft_split(line, '|');
            while (s_line[i])
            {
                lexer(&test, s_line[i], NULL);
                i++;
            }
        } 

        t_node *test_test = test;
        while (test_test)
        {
            t_redi *lol = test_test->file;
            i = 0;
            while (test_test->cmd[i])
            {
                printf("cmd[ %s ]   ", test_test->cmd[i]);
                i++;
            }
            printf("\n");
            while (lol)
            {
                printf("file_num[ %s ]\n", lol->file_num);
                printf("in_out_app[ %d ]\n", lol->type);
                lol = lol->next;
            }
            printf("-------------------------------------------\n");
            test_test = test_test->next;
        }
    }
    clear_history();
}