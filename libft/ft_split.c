/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchantel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 02:20:00 by lchantel          #+#    #+#             */
/*   Updated: 2020/05/14 21:43:41 by lchantel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_addstr(const char *end_pos, const char *init_pos, char c)
{
	char	*st_pos;
	char	*res;
	size_t	len;

	st_pos = (char *)(end_pos - 1);
	while (*st_pos != c && st_pos > init_pos)
		--st_pos;
	if (*st_pos == (char)c)
		++st_pos;
	len = end_pos - st_pos + 1;
	if (!(res = (char *)malloc(len)))
		return (NULL);
	ft_strlcpy(res, st_pos, len);
	return (res);
}

static size_t	ft_countrow(const char *s, char c)
{
	char	*iter;
	size_t	row_size;

	iter = (char *)s;
	row_size = 0;
	while (*iter)
	{
		while (*iter == c && *iter)
			++iter;
		if (*iter && *iter != c)
			++row_size;
		while (*iter != c && *iter)
			++iter;
	}
	return (++row_size);
}

char			**ft_split(char const *s, char c)
{
	char	*pos;
	size_t	size;
	char	**res;
	size_t	i;

	if (!s)
		return (NULL);
	size = ft_countrow(s, c);
	if (!(res = (char **)malloc(size * sizeof(char *))))
		return (NULL);
	pos = (char *)s;
	i = 0;
	while (--size)
	{
		while (*pos == (char)c && *pos)
			++pos;
		while (*pos != (char)c && *pos)
			++pos;
		*(res + i++) = ft_addstr(pos, s, (unsigned char)c);
	}
	*(res + i) = NULL;
	return (res);
}
