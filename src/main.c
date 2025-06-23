/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:39:07 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/06/21 01:49:08 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_es = 0;

void free_all_commands(t_node *head) {
    t_node *tmp;
    while (head) 
    {
        tmp = head;
        if (head->cmd)
        {
            free_split(head->cmd);
        }
        if (head->file)
            free_redi_list(head->file);
        head = head->next;
        free(tmp);
    }
}
void free_env(t_env *env)
{
    free_split(env->my_envp);
    free(env);
}
int main(int ac,char **av,char **envp)
{

    (void)ac;
    (void)av;
    char *line;
    t_env *env;

    env = NULL;
    signal_setup();
    while (1)
    {
        t_node *head = NULL;
        line = readline("\033[32mDash@Ameed$ \033[0m");
        if (!env)
            env = envp_dup(envp);
        if(!line)
        {
            free_all_commands(head);
            if(env)
                free_env(env);
            return 0;
        }
        add_history(line);
        ft_all(&head ,line ,NULL ,env);
        if(head)
        {
            free_heredoc(head, env,NULL);
            pipe_hundel(head, env);
        }
        // free_all_commands(head);
    }
    clear_history();
}
