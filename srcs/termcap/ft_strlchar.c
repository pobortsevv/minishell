/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:28:13 by sabra             #+#    #+#             */
/*   Updated: 2021/04/06 13:36:31 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlchar(char *dst, const char src, size_t dstsize)
{
	size_t			i;

	i = 0;
	i = strlen(dst);
	if (!dst)
		return (-1);
	if (dstsize == 0)
		return (strlen(dst));
	if (i < dstsize - 1)
	{
		dst[i] = src;
		i++;
	}
	dst[i] = '\0';
	return (strlen(dst));
}
