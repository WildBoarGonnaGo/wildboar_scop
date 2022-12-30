/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 06:44:09 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/14 21:39:36 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		len;
	const char	*src_start;

	src_start = src;
	len = size;
	if (!src || !dst)
		return (0);
	if (len)
		while (--len)
			if ((*(dst++) = *(src++)) == '\0')
				break ;
	if (!len)
	{
		if (size)
			*dst = '\0';
		while (*(src++) != '\0')
			;
	}
	return (src - src_start - 1);
}
