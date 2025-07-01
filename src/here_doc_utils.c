/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:14:17 by mohben-t          #+#    #+#             */
/*   Updated: 2025/07/01 18:18:16 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_heredoc_file(char **tmp, int *fd, int count)
{
	char	*id;

	id = ft_itoa(count);
	if (!id)
		return (-1);
	*tmp = ft_strjoin(".file_", id);
	free(id);
	if (!*tmp)
		return (-1);
	free_heredoc(NULL, NULL, *tmp);
	*fd = open(*tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), free(tmp), -1);
	return (0);
}

int	write_heredoc_loop(t_redi *redi, t_env *env, int fd)
{
	char	*line;
	char	*temp;

	while (1)
	{
		line = readline("heredoc > ");
		if (!line || ft_strcmp(redi->file_num, line) == 0)
		{
			return (free(line), 0);
		}
		temp = expand_line1(line, "", env);
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		free(line);
		free(temp);
	}
}
