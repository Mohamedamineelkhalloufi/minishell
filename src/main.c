/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:39:07 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/06/02 14:06:23 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_es = 0;

int main(int ac,char **av,char **envp)
{

    (void)ac;
    (void)av;
    char *line;
    signal_setup();
    t_env *env = malloc(sizeof(t_env));
    if (!env)
        return 1;
    while (1)
    {
        t_node *head = NULL;
        line = readline("\033[32mDash@Ameed$ \033[0m");
        if (!line)
            return 0;
        add_history(line);
        if (!env->my_envp || !env->my_envp[0])
            envp_dup(env, envp);
        else
        {
            env->next = malloc(sizeof(t_env));
            if (env->next)
            {
                env->next->my_envp = env->my_envp;
                env->next->next = NULL;
            }
        }
        ft_all(&head ,line ,NULL ,env);
        if(head)
           pipe_hundel(head, env);

        
        t_node *test_test = head;
        while (test_test)
        {
            t_redi *lol = test_test->file;
            int i = 0;
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