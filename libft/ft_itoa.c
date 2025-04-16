/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:29:57 by mohel-kh          #+#    #+#             */
/*   Updated: 2024/11/04 15:49:18 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	long_len(long nb)
{
	long	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	num;
	long	len;
	char	*tmp;

	num = (long)n;
	len = long_len(num);
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	tmp[len] = '\0';
	if (num == 0)
		tmp[0] = '0';
	if (num < 0)
	{
		tmp[0] = '-';
		num = -num;
	}
	while (num)
	{
		tmp[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (tmp);
}
