/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:40:10 by sabra             #+#    #+#             */
/*   Updated: 2020/11/04 13:22:15 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char			*sym1;
	unsigned char			*sym2;

	sym1 = (unsigned char *)s1;
	sym2 = (unsigned char *)s2;
	if (sym1 == sym2 || n == 0)
		return (0);
	while (n--)
	{
		if (*sym1 != *sym2)
			return (*sym1 - *sym2);
		sym1++;
		sym2++;
	}
	return (0);
}
