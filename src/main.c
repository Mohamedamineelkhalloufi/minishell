/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:39:07 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/06/17 16:36:01 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_es = 0;

void free_all_commands(t_node *head) {
    t_node *tmp;
    while (head) {
        tmp = head;
        if (head->cmd)
            free_split(head->cmd);
        if (head->file)
            free_redi_list(head->file);
        // if (head->echo_info)
        //     free_echo_info(head->echo_info);
        // if (head->info)
        //     free(head->info);
        head = head->next;
        free(tmp);
    }
}

int main(int ac,char **av,char **envp)
{

    (void)ac;
    (void)av;
    char *line;
    signal_setup();
    t_env *env;

    env = NULL;
    while (1)
    {
        t_node *head = NULL;
        line = readline("\033[32mDash@Ameed$ \033[0m");
        if (!line)
            return 0;
        add_history(line);
        if (!env)
            env = envp_dup(envp);
        ft_all(&head ,line ,NULL ,env);
        if(head)
            pipe_hundel(head, env);
        free_all_commands(head);
        //head = NULL;
    }
    clear_history();
}
