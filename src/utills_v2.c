/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:26:56 by mohben-t          #+#    #+#             */
/*   Updated: 2025/06/21 02:32:54 by mohben-t         ###   ########.fr       */
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

char	**ft_split_a(char const *s, char const *delimiter)
{
	char	**lst;
	size_t	word_len;
	size_t	delimiter_len;
	int		i;

	if (!s || !delimiter)
		return (NULL);
	delimiter_len = ft_strlen(delimiter);
	lst = (char **)malloc((ft_countword(s, delimiter) + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_strncmp(s, delimiter, delimiter_len) == 0)
			s += delimiter_len;
		if (*s)
		{
			char *next_delim = ft_strnstr(s, delimiter, ft_strlen(s));
			if (!next_delim)
				word_len = ft_strlen(s);
			else
				word_len = next_delim - s;
			lst[i++] = ft_substr(s, 0, word_len);
			s += word_len;
		}
	}
	lst[i] = NULL;
	return (lst);
}
void	free_split(char **split)
{
	int	i = 0;

	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void *ft_malloc(size_t size, char flag)
{
	static t_list *head;
	void *set;

	set = NULL;
	if (flag == 'A')
	{
		set = malloc(size);
		if (!set)
			return (NULL);
		ft_lstadd_back(&head, ft_lstnew(set));
	}
	else
	{
		t_list *tmp;
		while (head)
		{
			tmp = head->next;
			free(head->content);
			free(head);
			head = tmp;
		}
	}
	return set;
}

int	is_all_whitespace(const char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (ft_putendl_fd("command mot found",2),1);
}
