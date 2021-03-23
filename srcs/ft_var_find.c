/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:36:31 by sabra             #+#    #+#             */
/*   Updated: 2021/03/23 21:51:19 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_var_find(char *var, char **ev)
{
	size_t	i;
	char	*value;

	i = 0;
	if (!var || !ev)
		return (NULL);
	while (ev[i])
	{
		if (!ft_strncmp(var, ev[i], ft_strlen(var)))
		{
			value =	ft_strchr(ev[i], '=');
			if (!value)
				return (NULL);
			value++;
			return (value);
		}
		i++;
	}
	return (NULL);
}
