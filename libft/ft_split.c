/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:30:33 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/04/17 22:09:45 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	skip_quote(const char *s, int i)
{
	char	quote = s[i++];

	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

static int	get_word_len(const char *s, char sep)
{
	int	i = 0;

	while (s[i] && s[i] != sep)
	{
		if (is_quote(s[i]))
			i = skip_quote(s, i);
		else
			i++;
	}
	return (i);
}

static int	count_words(const char *s, char sep)
{
	int	i = 0;
	int	count = 0;

	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (!s[i])
			break;
		count++;
		i += get_word_len(&s[i], sep);
	}
	return (count);
}

static char	*copy_word(const char *s, int len)
{
	char	*word = (char *)malloc(len + 1);
	int		i = 0;
	int		j = 0;
	char	quote;

	if (!word)
		return (NULL);
	while (i < len)
	{
		if (is_quote(s[i]))
		{
			quote = s[i++];
			word[j++] = quote;
			while (s[i] && s[i] != quote)
				word[j++] = s[i++];
			if (s[i] == quote)
				word[j++] = s[i++];
		}
		else
			word[j++] = s[i++];
	}
	word[j] = '\0';
	return (word);
}

static void	*free_all(char **arr, int count)
{
	while (--count >= 0)
		free(arr[count]);
	free(arr);
	return (NULL);
}

char	**ft_split(const char *s, char sep)
{
	char	**res;
	int		i = 0;
	int		j = 0;
	int		len;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_words(s, sep) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (!s[i])
			break;
		len = get_word_len(&s[i], sep);
		res[j] = copy_word(&s[i], len);
		if (!res[j])
			return (free_all(res, j));
		i += len;
		j++;
	}
	res[j] = NULL;
	return (res);
}
