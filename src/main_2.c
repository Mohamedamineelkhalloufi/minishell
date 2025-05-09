/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:46:56 by mohben-t          #+#    #+#             */
/*   Updated: 2025/05/08 15:21:36 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
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
                {
                    free(test);
                    test = NULL;
                    break;
                }
                i++;
            }
            if(test)
                pipe_hundel(test,envp);
        } 
    }
    clear_history();
}