/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 10:33:26 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/07 05:50:11 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*(s1) != *(s2++))
			return (*(unsigned char *)s1 - *(unsigned char *)--s2);
		if (!*(s1++))
			return (0);
	}
	return (0);
}
