/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 05:06:53 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/14 21:41:36 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*pos;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (!(pos = (char *)malloc(len + 1)) || start > ft_strlen(s))
		return (NULL);
	while (len-- > 0)
		*(pos + i++) = *(s + start++);
	*(pos + i) = '\0';
	return (pos);
}
