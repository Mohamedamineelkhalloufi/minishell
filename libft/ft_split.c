/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:30:33 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/04/16 13:08:24 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	char q;
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c && s[i] != '\'' && s[i] != '\"')
				i++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			q = s[i];
			i++;
			while (s[i] && s[i] != q)
				i++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_create_word(char const *str, char c, int i)
{
	char	*dest;
	char	q;
	int		l;

	l = i;
	while (str[l] && str[l] != c && str[l] != '\'' && str[l] != '\"')
		l++;
	if (str[l] == '\'' || str[l] == '\"')
	{
		q = str[l];
		l++;
		while (str[l] && str[l] != q)
			l++;	
		while (str[l] && str[l] != c)
			l++;
	}
	dest = (char *)malloc(sizeof(char) * (l - i)+ 1);
	if (!dest)
		return (NULL);
	l = 0;
	while (str[i] && str[i] != c && str[i] != '\'' && str[i] != '\"')
		dest[l++] = str[i++];
	if (str[i] == '\'' || str[i] == '\"')
	{
		q = str[i];
		dest[l++] = str[i];
		i++;
		while (str[i] && str[i] != q)
			dest[l++] = str[i++];
		while (str[i] && str[i] != c)
			dest[l++] = str[i++];
	}
	dest[l] = '\0';
	return (dest);
}

static void	*ft_free(char **split, int i)
{
	while (--i)
	free(split[i]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	char	q;
	int		i;
	int		l = 0;

	if (!s)
	return (NULL);
	i = 0;
	dest = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!dest)
	return (NULL);
	while (s[l])
	{
		while (s[l] && s[l] == c)
			l++;
		if (s[l])
		{
			dest[i++] = ft_create_word(s, c, l);
			if (dest[i - 1] == NULL)
				return (ft_free(dest, i));
			while (s[l] && s[l] != c && s[l] != '\'' && s[l] != '\"')
				l++;
			if (s[l] && (s[l] == '\'' || s[l] == '\"'))
			{
				q = s[l];
				l++;
				while (s[l] && s[l] != q)
					l++;
				while (s[l] && s[l] != c)
					l++;
			}	
		}
	}
	dest[i] = NULL;
	return (dest);
}