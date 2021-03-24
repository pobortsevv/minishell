/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:32:23 by sabra             #+#    #+#             */
/*   Updated: 2021/03/24 09:44:40 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_strjoin_mod(char const *s1, char const *s2, size_t len)
{
	char	*result;
	int		end_1;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1 + len);
	if (!result)
		return (NULL);
	end_1 = 0;
	i = 0;
	while (s1[end_1])
	{
		result[end_1] = s1[end_1];
		end_1++;
	}
	while (s2[i])
	{
		result[end_1] = s2[i];
		i++;
		end_1++;
	}
	result[end_1] = '\0';
	return (result);
}
