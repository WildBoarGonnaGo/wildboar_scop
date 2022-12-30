/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 10:26:53 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/16 12:21:25 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getnumsize(long n)
{
	int size;

	size = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		n *= -1;
		++size;
	}
	while (n /= 10)
		++size;
	return (++size);
}

char		*ft_itoa(int n)
{
	long	val;
	int		size;
	char	*res;

	val = n;
	size = ft_getnumsize(val);
	if (!(res = (char *)malloc(size + 1)))
		return (0);
	val *= (n < 0) ? -1 : 1;
	*(res + size--) = '\0';
	while (size >= 0)
	{
		if (!size && n < 0)
		{
			*(res + size) = '-';
			break ;
		}
		*(res + size) = val % 10 + 48;
		val /= 10;
		--size;
	}
	return (res);
}
