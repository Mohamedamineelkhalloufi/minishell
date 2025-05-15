#include "../minishell.h"
void    ft_all(t_node **all_cmd, char *line, char **s_line)
{
    char *plus;
    int i;

    plus = NULL;
    i = 0;
    if (d_quote(line, 0, 0, 0) == 0 || !check_pipe(line))
        ft_putendl_fd(" Dash@Ameed: syntax error near unexpected", 2);
    else
    {
        plus = expand_line(line, 0, ft_strdup(""));
        s_line = ft_split(plus, '|');
        while (s_line[i])
        {
            if (!lexer(all_cmd, s_line[i], NULL))
            {
                free(all_cmd);
                all_cmd = NULL;
                break;
            }
            i++;
        }
    }
}
int main(int ac,char **av,char **envp)
{

    (void)ac;
    (void)av;
    char *line;

    while (1)
    {
        t_node *head = NULL;
        // head->echo_info = malloc(sizeof(head->echo_info));
        t_env *env = malloc(sizeof(t_env));
        if (!env)
        return 1;
        line = readline("\033[32m Dash@Ameed$ \033[0m");
        if (!line)
            return 0;
        add_history(line);
        ft_all(&head ,line ,NULL);
        if(head)
        {
            envp_dup(env,envp);
            pipe_hundel(head,env);
        }
        // if (test)
        // {
            //     t_node *tmp = test;
            //     while (tmp)
            //     {
                //         envp_dup(tmp, envp);
                //         tmp = tmp->next;
                //     }
                //     pipe_hundel(test, test->my_envp);
                // }
                
        // t_node *test_test = head;
        // while (test_test)
        // {
        //     t_redi *lol = test_test->file;
        //     int i = 0;
        //     while (test_test->cmd[i])
        //     {
        //         printf("cmd[ %s ]   ", test_test->cmd[i]);
        //         i++;
        //     }
        //     printf("\n");
        //     while (lol)
        //     {
        //         printf("file_num[ %s ] --> ", lol->file_num);
        //         if (lol->type == 0)
        //             printf("type_file [ FILE_IN ]\n");
        //         else if (lol->type == 1)
        //             printf("type_file [ FILE_OUT \n]");
        //         else if (lol->type == 2)
        //             printf("type_file [ FILE_APPEND ]\n");
        //         else
        //             printf("type_file [ FILE_HEREDOC ]\n");
        //         lol = lol->next;
        //     }
        //     printf("-------------------------------------------\n");
        //     test_test = test_test->next;
        // }
    }
    clear_history();
}