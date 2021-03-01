/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 11:18:33 by sabra             #+#    #+#             */
/*   Updated: 2021/01/11 18:49:25 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t			i;
	size_t			end;

	i = 0;
	end = ft_strlen(dest);
	if (size <= end)
		return (size + ft_strlen(src));
	while (src[i] && i + end < (size - 1))
	{
		dest[i + end] = src[i];
		i++;
	}
	dest[i + end] = '\0';
	return (ft_strlen(src) + end);
}
