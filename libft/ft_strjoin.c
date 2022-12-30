/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 10:57:25 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/14 21:42:09 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size[2];

	if (!s1 || !s2)
		return (NULL);
	size[0] = ft_strlen(s1) + 1;
	size[1] = ft_strlen(s2) + 1;
	if (!(str = (char *)malloc(size[0] + size[1])))
		return (NULL);
	if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	ft_strlcpy(str, s1, size[0]);
	ft_strlcat(str, s2, size[1] + size[0]);
	return (str);
}
