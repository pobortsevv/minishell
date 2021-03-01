/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:06:42 by sabra             #+#    #+#             */
/*   Updated: 2020/11/05 15:37:45 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;

	if (!s1 || !set)
		return (0);
	end = ft_strlen(s1);
	start = 0;
	while (ft_strchr(set, s1[start]) && s1)
		start++;
	while (ft_strchr(set, s1[end - 1]) && start < end)
		end--;
	return (ft_substr(s1, start, end - start));
}
