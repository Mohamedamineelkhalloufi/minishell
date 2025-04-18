/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:27:54 by mohel-kh          #+#    #+#             */
/*   Updated: 2024/11/08 12:40:00 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	lensrc;
	unsigned int	lendest;

	lendest = 0;
	lensrc = 0;
	i = 0;
	j = 0;
	while (src[lensrc])
		lensrc++;
	if (!dstsize)
		return (lensrc);
	while (dst[lendest])
		lendest++;
	if (dstsize <= lendest)
		return (dstsize + lensrc);
	while (dst[i])
		i++;
	while (src[j] && i < dstsize - 1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (lendest + lensrc);
}
