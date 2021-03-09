/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 01:17:24 by sabra             #+#    #+#             */
/*   Updated: 2021/03/09 12:37:58 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	env_sort(char **a)
{
	size_t	i;
	size_t	len;
	size_t	turn;
	char	*buf;

	i = 0;
	len = 0;
	while(a[len++])
		;
	len -= 2;
	turn = 0;
	while (a && turn == 0)
	{
		i = 0;
		turn = 1;
		while (i < len - 1)
		{
			if (ft_strncmp(a[i], a[i + 1], FILENAME_MAX) > 0)
			{
				turn = 0;
				buf = a[i];
				a[i] = a[i + 1];
				a[i + 1] = buf;
			}
			i++;
		}
		len--;
	}
}

int		ft_export(t_cmd *cmd, char **ev)
{
	size_t i;
	
	i = 0;
	(void)cmd;
	env_sort(ev);
	if (!ev)
		return (0);
	while(ev[i])
	{
		ft_printf("declare -x %s\n", ev[i]);
		i++;
	}
	return (1);
}
