#include "../minishell.h"

 //--> int out int in
static int ft_output(t_redi *redier)
{
    int fd = open(redier->file_num, O_CREAT | O_WRONLY | O_TRUNC,0644);
    if (fd == -1)
    {
        printf("minishell\n");
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        printf("minishell: dup2 error\n");
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
        printf("minishell\n");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        printf("minishell: dup2 error\n");
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
        printf("minishell\n");
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        printf("minishell: dup2 error\n");
        close(fd);
        return (-1);
    }
    close(fd);
    return 0;
}

// int ft_heredoc(t_redi *redier)
// {
//     int fd = open(redier->file_num, O_CREAT | O_RDWR, 0644);
//     while(1)
//     {
//         char *line = readline(">");
//         if(!line || !strcmp(redier->limiter, line))
//         {
//             free(line);
//             break;
//         }
//     }
//     if (dup2(fd, STDIN_FILENO) == -1)
//     {
//         printf("minishell: dup2 error\n");
//         close(fd);
//         return (-1);
//     }
//     close(fd);
//     return 0;
// }

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
        // else if (redir->type == 3)
        //     ft_heredoc(redir);
        redir = redir->next;
    }
}
