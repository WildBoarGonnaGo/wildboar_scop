/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:01:37 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/07 07:46:22 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	bound;

	bound = ft_strlen(s);
	while (bound >= 0)
	{
		if (*(s + bound) == (unsigned char)c)
			return ((char *)s + bound);
		--bound;
	}
	return (NULL);
}
