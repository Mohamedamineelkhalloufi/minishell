#include "minishell.h"

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
            s_line = ft_split(line, '|');
            while (s_line[i])
            {
                if (!lexer(&test, s_line[i], NULL))
                    break;
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