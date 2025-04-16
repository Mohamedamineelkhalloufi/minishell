/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:20:48 by mohel-kh          #+#    #+#             */
/*   Updated: 2024/11/11 18:12:15 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*buff;
	int		len;
	int		i;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s) + 1;
	buff = malloc(len);
	if (!buff)
		return (NULL);
	while (s[i])
	{
		buff[i] = (f)(i, s[i]);
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
