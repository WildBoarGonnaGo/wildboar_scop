/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 03:10:18 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/13 14:09:11 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	unsigned char	*func_dest;
	unsigned char	*func_orig;

	if (!n || s1 == s2)
		return (NULL);
	func_dest = (unsigned char *)s1;
	func_orig = (unsigned char *)s2;
	while (n-- > 0)
		if ((*(func_dest++) = *(func_orig++)) == (unsigned char)c)
			return (func_dest);
	return (NULL);
}
