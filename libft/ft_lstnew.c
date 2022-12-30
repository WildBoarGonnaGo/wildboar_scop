/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:42:18 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/11 11:10:29 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	if (!(new_elem = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}
