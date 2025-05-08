#include "../minishell.h"


static int ft_output(t_redi *redier)
{
    int fd = open(redier->file_num, O_CREAT | O_WRONLY | O_TRUNC,0644);
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
static int ft_input(t_redi *redier)
{
    int fd = open(redier->file_num,O_RDONLY,0644);
    if (fd == -1)
    {
        perror("minishell\n");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("minishell: dup2 error\n");
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
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return -1;
    }
    while (1)
    {
        char *line = readline("heredoc > ");
        if (!line || !strcmp(redier->file_num, line))
        {
            free(line);
            break;
        }
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(pipefd[0]);
        return -1;
    }
    close(pipefd[0]);
    return 0;
}

void ft_redirect(t_redi *redir)
{
    while (redir)
    {
        if (redir->type == 1)
            ft_output(redir);
        else if (redir->type == 0)
            ft_input(redir);
        else if (redir->type == 2)
            ft_append(redir);
        else if (redir->type == 3)
            ft_heredoc(redir);
        redir = redir->next;
    }
}
