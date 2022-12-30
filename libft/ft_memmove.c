/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 09:31:27 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/14 16:00:39 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	*func_dest;
	unsigned char	*func_orig;
	size_t			i;

	func_dest = (unsigned char *)s1;
	func_orig = (unsigned char *)s2;
	if (!s1 && !s2 && n)
		return (NULL);
	if (s1 > s2)
	{
		i = 0;
		while (++i <= n)
			*(func_dest + n - i) = *(func_orig + n - i);
	}
	else
	{
		i = -1;
		while (++i < n)
			*(func_dest + i) = *(func_orig + i);
	}
	return (func_dest);
}
