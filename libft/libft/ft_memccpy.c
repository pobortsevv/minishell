/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 22:24:26 by sabra             #+#    #+#             */
/*   Updated: 2020/11/04 11:22:26 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	char			stop;
	char			*destination;
	char			*source;

	destination = (char*)dest;
	source = (char*)src;
	stop = (char)c;
	i = 0;
	while (i < n)
	{
		if (source[i] != stop)
		{
			destination[i] = source[i];
		}
		else
		{
			destination[i] = source[i];
			return (&destination[i + 1]);
		}
		i++;
	}
	return (NULL);
}
