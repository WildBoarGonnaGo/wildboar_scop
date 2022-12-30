/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:35:06 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/07 04:27:13 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*buf_addr;

	buf_addr = (unsigned char *)s;
	while (n--)
		if (*(buf_addr++) == (unsigned char)c)
			return ((void *)(buf_addr - 1));
	return (NULL);
}
