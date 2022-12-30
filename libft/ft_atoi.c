/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 11:28:01 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/14 19:27:39 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long long	res[2];

	res[0] = 0;
	res[1] = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		++nptr;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			res[1] = -1;
		++nptr;
	}
	while (ft_isdigit(*nptr))
	{
		res[0] *= 10;
		res[0] += *nptr - '0';
		++nptr;
	}
	return (res[0] * res[1]);
}
