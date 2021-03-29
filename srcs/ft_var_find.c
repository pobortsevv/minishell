/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:36:31 by sabra             #+#    #+#             */
/*   Updated: 2021/03/29 15:37:00 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_var_find(char *var, char **ev)
{
	size_t	i;
	char	*value;
	char	*res;

	if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(shell.status));
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
			res = ft_strdup(value);
			return (res);
		}
		i++;
	}
	return (NULL);
}
