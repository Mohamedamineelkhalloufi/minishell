/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:39:07 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/05/16 17:39:09 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int ac,char **av,char **envp)
{

    (void)ac;
    (void)av;
    // (void)envp;
    char *line;

    while (1)
    {
        t_node *head = NULL;
        // head->echo_info = malloc(sizeof(head->echo_info));
        t_env *env = malloc(sizeof(t_env));
        if (!env)
        return 1;
        line = readline("\033[32mDash@Ameed$ \033[0m");
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