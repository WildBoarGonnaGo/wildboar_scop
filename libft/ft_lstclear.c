/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:33:18 by lchantel          #+#    #+#             */
/*   Updated: 2022/09/18 21:37:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*roll;
	t_list	*kill;

	if (!*lst)
		return ;
	roll = (*lst);
	while (roll)
	{
		kill = roll;
		roll = roll->next;
		ft_lstdelone(kill, del);
	}
	*lst = NULL;
}
