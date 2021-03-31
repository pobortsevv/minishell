/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:20:07 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/31 14:46:21 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_array_to_str(char **array)
{
	char	*res;
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	res = (char *)malloc(sizeof(char) * 1);
	res[0] = '\0';
//	printf ("22222\n");
//	printf("ibefore %s\n", array[i]);
	if (array[i] != NULL)
	{
		temp = res;
//		printf("in cycle %s\n", array[i]);
		res = ft_strjoin(res, array[i]);
		free(temp);
		i++;
	}
//	printf("111\n");
	while (array[i] != NULL)
	{
		temp = res;
		res = ft_strjoin(res, " ");
		free(temp);
		temp = res;
		res = ft_strjoin(res, array[i++]);
		free(temp);
	}
	return (res);
}
