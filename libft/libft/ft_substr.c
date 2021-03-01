/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:52:26 by sabra             #+#    #+#             */
/*   Updated: 2020/11/09 16:01:35 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;
	char	*string;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = (char *)malloc(1);
		substr[0] = '\0';
		return (substr);
	}
	if (!(substr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	string = (char *)s;
	i = 0;
	while (len-- && string[start])
	{
		substr[i] = string[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
