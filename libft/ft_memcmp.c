/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 13:12:50 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/02 04:16:17 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*buf_addr_1;
	unsigned char	*buf_addr_2;

	buf_addr_1 = (unsigned char *)s1;
	buf_addr_2 = (unsigned char *)s2;
	while (n)
	{
		if (*buf_addr_1 != *buf_addr_2)
			return (*buf_addr_1 - *buf_addr_2);
		++buf_addr_1;
		++buf_addr_2;
		--n;
	}
	return (0);
}
