/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 00:04:37 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/14 16:11:39 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	buf;

	buf = n;
	if (n < 0)
	{
		buf *= -1;
		ft_putchar_fd('-', fd);
	}
	if (buf >= 10)
		ft_putnbr_fd(buf / 10, fd);
	ft_putchar_fd(buf % 10 + 48, fd);
}
