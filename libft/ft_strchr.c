/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 15:29:35 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/07 07:57:13 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		bound;
	size_t		i;

	bound = ft_strlen(s);
	i = -1;
	while (++i <= bound)
		if (*(s + i) == (unsigned char)c)
			return ((char *)s + i);
	return (NULL);
}
