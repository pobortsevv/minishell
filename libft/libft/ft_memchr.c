/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 23:22:03 by sabra             #+#    #+#             */
/*   Updated: 2020/11/04 11:23:08 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	char			sought;
	char			*source;

	sought = (char)c;
	source = (char *)s;
	i = 0;
	while (i < n)
	{
		if (source[i] == sought)
		{
			return (&source[i]);
		}
		i++;
	}
	return (NULL);
}
