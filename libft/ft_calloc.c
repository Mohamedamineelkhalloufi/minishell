/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:42:55 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/02/25 20:21:56 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned int	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
	{
		ptr = NULL;
		return (ptr);
	}
	ft_bzero(ptr, count * size);
	return (ptr);
}
