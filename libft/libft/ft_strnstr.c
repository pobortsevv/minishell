/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:25:08 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 20:26:12 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str1, char *str2, size_t size)
{
	size_t		j;
	size_t		i;

	i = 0;
	if (!(*str2))
		return (str1);
	while (str1[i] != '\0' && i < size)
	{
		j = 0;
		while (str2[j] == str1[i + j] && (i + j) < size)
		{
			if (str2[j + 1] == '\0')
				return (str1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
