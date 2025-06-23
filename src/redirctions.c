/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirctions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:20:30 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/20 18:35:03 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_output(t_redi *redier)
{
    int fd = open(redier->file_num, O_CREAT | O_WRONLY | O_TRUNC,0644);
    if (fd == -1)
    {
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("minishell: dup2 error\n");
        close(fd);
        return (-1);
    }
    close(fd);
    return 0;
}

static int ft_input(t_redi *redier)
{
    int fd = open(redier->file_num, O_RDONLY);
    if (fd == -1)
    {
        perror("Dash@Ameed:");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("minishell: dup2 error");
        close(fd);
        return (-1);
    }

    close(fd);
    return 0;
}

static int ft_append(t_redi *redier)
{
    int fd = open(redier->file_num, O_CREAT | O_WRONLY | O_APPEND,0644);
    if (fd == -1)
    {
        perror("minishell\n");
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("minishell: dup2 error\n");
        close(fd);
        return (-1);
    }
    close(fd);
    return 0;
}

int ft_heredoc(t_redi *redier,t_env *env)
{
    char    *line;
    static int count = 0;
    char *tmp;
    char *temp;
    char *id;
    int     fd;

    id = ft_itoa(count++);
    if (!id)
        return (-1);
    tmp = ft_strjoin(".file_", id);
    free(id);
    if (!tmp)
        return (-1);
    free_heredoc(NULL,NULL,tmp);
    fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        return (perror("open"), free(tmp), -1);
    signal(SIGINT, SIG_DFL);
    signal(SIGINT, g_handler);
    while (1)
    {
        line = readline("heredoc > ");
        temp = expand_line1(line, "", env);
        if (!line)
            break;
        if (ft_strcmp(redier->file_num, line) == 0)
        {
            free(temp);
            temp = NULL;
            free(line);
            break;
        }
        write(fd, temp, ft_strlen(temp));
        write(fd, "\n", 1);
        free(line);
        free(temp);
        temp = NULL;
    }
    close(fd);
    redier->heredoc_file = strdup(tmp);
    free(tmp);
    return (0);
}


int ft_redirect(t_redi *redir,t_env *env)
{
    int res = 0;
    t_redi *last_heredoc = NULL;

    t_redi *tmp = redir;
    while (tmp)
    {
        if (tmp->type == 3)
        {
            res = ft_heredoc(tmp,env);
            if (res == -1)
                return -1;
            last_heredoc = tmp;
        }
        tmp = tmp->next;
    }
    while (redir)
    {
        if (redir->type == 1)
            res = ft_output(redir);
        else if (redir->type == 0)
            res = ft_input(redir);
        else if (redir->type == 2)
            res = ft_append(redir);
        redir = redir->next;
    }
    if (last_heredoc)
    {
        int fd = open(last_heredoc->heredoc_file, O_RDONLY);
        if (fd < 0)
            return (perror("open heredoc"), -1);
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            close(fd);
            return -1;
        }
        unlink(last_heredoc->heredoc_file);
        close(fd);
    }
    return res;
}
