/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 08:25:38 by sabra             #+#    #+#             */
/*   Updated: 2021/03/29 08:33:41 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char 	*ft_dup_join(char *dup, char *join)
{
	char *res;
	char *tmp;

	if (!dup || !join)
		return (NULL);
	tmp = ft_strdup(dup);
	res = ft_strjoin(tmp, join);
	if (tmp)
		ft_free_line(&tmp);
	return (res);
}
