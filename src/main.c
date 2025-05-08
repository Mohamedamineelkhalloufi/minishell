#include "../minishell.h"

char *qoute_remov(char *line)
{
    char *new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
    char q;
    int i = 0;
    int l = 0;

    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            q = line[i++];
            while (line[i] && line[i] != q)
                new_line[l++] = line[i++];
            if (line[i])
                i++;
        }
        else
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
        if (d_quote(line, 0, 0, 0) == 0 || !check_pipe(line))
            printf(" Dash@Ameed: syntax error near unexpected\n");
        else
        {
            char *plus = expand_line(line, 0, ft_strdup(""));
            s_line = ft_split(plus, '|');
            while (s_line[i])
            {
                if (!lexer(&test, s_line[i], NULL))
                {
                    free(test);
                    test = NULL;
                    break;
                }
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
                printf("file_num[ %s ] --> ", lol->file_num);
                if (lol->type == 0)
                    printf("type_file [ FILE_IN ]\n");
                else if (lol->type == 1)
                    printf("type_file [ FILE_OUT \n]");
                else if (lol->type == 2)
                    printf("type_file [ FILE_APPEND ]\n");
                else
                    printf("type_file [ FILE_HEREDOC ]\n");
                lol = lol->next;
            }
            printf("-------------------------------------------\n");
            test_test = test_test->next;
        }
    }
    clear_history();
}