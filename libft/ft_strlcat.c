/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 07:48:45 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/02 15:26:52 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dst_len;
	size_t		check;
	size_t		dst_src;
	const char	*start_dst;
	const char	*start_src;

	start_dst = dst;
	start_src = src;
	check = size;
	dst_src = ft_strlen(src);
	while (check-- != 0 && *dst != '\0')
		++dst;
	dst_len = dst - start_dst;
	check = size - dst_len;
	if (!check--)
		return (dst_len + dst_src);
	while (*src && check--)
		*(dst++) = (*src++);
	*dst = '\0';
	if (*src != '\0')
		return (dst_len + dst_src);
	return (dst_len + (src - start_src));
}
