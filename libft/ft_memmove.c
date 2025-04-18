/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:04:50 by mohel-kh          #+#    #+#             */
/*   Updated: 2024/11/08 12:19:27 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdest;
	char	*csrc;

	cdest = (char *)dst;
	csrc = (char *)src;
	if (!dst && !src)
		return (0);
	if (dst <= src)
	{
		while (len--)
		{
			*cdest++ = *csrc++;
		}
	}
	else if (dst > src)
	{
		cdest += len - 1;
		csrc += len - 1;
		while (len--)
		{
			*cdest-- = *csrc--;
		}
	}
	return (dst);
}
