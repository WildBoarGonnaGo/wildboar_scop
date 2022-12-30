/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 15:42:21 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/12 02:19:32 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char	*func_dest;
	unsigned char	*func_orig;
	size_t			i;

	if (!n || s1 == s2)
		return (s1);
	func_dest = (unsigned char *)s1;
	func_orig = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		*(func_dest + i) = *(func_orig + i);
		++i;
	}
	return (s1);
}
