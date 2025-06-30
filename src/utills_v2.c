/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:26:56 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/28 11:26:27 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_countword(char const *s, char const *delimiter)
{
	size_t	count;
	size_t	delimiter_len;

	if (!*s)
		return (0);
	count = 0;
	delimiter_len = ft_strlen(delimiter);
	while (*s)
	{
		while (ft_strncmp(s, delimiter, delimiter_len) == 0)
			s += delimiter_len;
		if (*s)
			count++;
		while (*s && ft_strncmp(s, delimiter, delimiter_len) != 0)
			s++;
	}
	return (count);
}

static char	*get_next_token(char const **s_ptr, char const *delimiter,
		size_t delim_len)
{
	char	*next_delim;
	size_t	len;
	char	*token;

	while (**s_ptr && ft_strncmp(*s_ptr, delimiter, delim_len) == 0)
		*s_ptr += delim_len;
	if (!**s_ptr)
		return (NULL);
	next_delim = ft_strnstr(*s_ptr, delimiter, ft_strlen(*s_ptr));
	if (next_delim == NULL)
		len = ft_strlen(*s_ptr);
	else
		len = (size_t)(next_delim - *s_ptr);
	token = ft_substr(*s_ptr, 0, len);
	if (next_delim)
		*s_ptr = next_delim;
	else
		*s_ptr += len;
	return (token);
}

char	**ft_split_a(char const *s, char const *delimiter)
{
	char	**lst;
	size_t	delim_len;
	int		i;
	int		word_count;
	char	*token;

	if (!s || !delimiter)
		return (NULL);
	delim_len = ft_strlen(delimiter);
	word_count = ft_countword(s, delimiter);
	lst = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		token = get_next_token(&s, delimiter, delim_len);
		lst[i] = token;
		i++;
	}
	lst[i] = NULL;
	return (lst);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	is_all_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (ft_putendl_fd("command mot found", 2), 1);
}
