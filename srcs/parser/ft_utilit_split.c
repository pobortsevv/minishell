/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilit_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:23:55 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/16 13:33:41 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

int			ft_isntend_split(char const *s, int *flag)
{
	int		ret;

	ret = 1;
	if ((checkbit(*flag, SLASH_1) && checkbit(*flag, SLASH_2)) ||
			!checkbit(*flag, SLASH_1))
	{
		if (checkbit(*flag, SLASH_2))
		{
			*flag = switchbit(*flag, SLASH_1);
			*flag = switchbit(*flag, SLASH_2);
		}
		if (!(checkbit(*flag, SINGLE_Q)) && s[0] == '\\')
			*flag = setbit(*flag, SLASH_1);
		else if (s[0] == 39)
			*flag = switchbit(*flag, SINGLE_Q);
		else if (!(checkbit(*flag, SINGLE_Q)) && s[0] == '"')
			*flag = switchbit(*flag, DOUBLE_Q);
	}
	else if (checkbit(*flag, SLASH_1))
		*flag = setbit(*flag, SLASH_2);
	return (ret);
}

void		ft_free_split(char **result, size_t last)
{
	size_t	i;

	i = 0;
	while (i < last)
	{
		free(result[i]);
		i++;
	}
	free(result);
}
