/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirctions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:20:30 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/03 16:01:29 by mohben-t         ###   ########.fr       */
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

int ft_heredoc(t_redi *redier)
{
    char    *line;
    static int count = 0;
    char *tmp;
    int     fd;

    tmp = ft_strjoin("file_",ft_itoa(count++));
    fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        return (perror("open"), -1);
    
    while (1)
    {
        line = readline("heredoc > ");
        if (!line)
            break;
        if (ft_strcmp(redier->file_num, line) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);

    redier->heredoc_file = strdup(tmp);
    return (0);
}
int ft_redirect(t_redi *redir)
{
    int res = 0;
    t_redi *last_heredoc = NULL;

    t_redi *tmp = redir;
    while (tmp)
    {
        if (tmp->type == 3)
        {
            res = ft_heredoc(tmp);
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
        close(fd);
    }

    return res;
}
