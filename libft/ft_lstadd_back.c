/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:44:06 by lchantel          #+#    #+#             */
/*   Updated: 2022/09/17 20:42:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*roll;

	if (!*lst)
		*lst = new;
	else
	{
		roll = *lst;
                while (roll->next != NULL)
			roll = roll->next;
		roll->next = new;
	}
}
