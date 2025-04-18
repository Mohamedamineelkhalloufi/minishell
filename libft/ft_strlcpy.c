/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:30:55 by mohel-kh          #+#    #+#             */
/*   Updated: 2024/11/08 12:38:12 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(const char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	l;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	l = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	while (s[l] != '\0')
	{
		l++;
	}
	if (dstsize != '\0')
	{
		while (s[i] != '\0' && i < dstsize - 1)
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
	}
	return (l);
}
