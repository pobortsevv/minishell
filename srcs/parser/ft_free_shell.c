/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:49:54 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/23 11:38:05 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		free_array_shell(char **ar)
{
	int		i;

	i = 0;
	if (ar != NULL)
	{
		while (ar[i] != NULL)
		{
			free(ar[i]);
			ar[i] = NULL;
			i++;
		}
		free(ar);
		ar = NULL;
	}
	return ;
}

void		free_array_shell_2(char ***ar)
{
	int		i;

	i = 0;
	if (ar != NULL)
	{
		while (ar[i] != NULL)
		{
			free_array_shell(ar[i]);
			i++;
		}
		free(ar);
		ar = NULL;
	}
	return ;
}

void		free_t_cmd(t_cmd *ar_t_cmd, int len)
{
	int		u;
	int		j;

	u = 0;
	while (u < len)
	{
		j = 0;
		while (j < ar_t_cmd[u].len_args)
		{
			if (ar_t_cmd[u].args[j] != NULL)
			{
				free(ar_t_cmd[u].args[j]);
				ar_t_cmd[u].args[j] = NULL;
			}
			j++;
		}
		if (ar_t_cmd[u].args != NULL)
		{
			free(ar_t_cmd[u].args);
			ar_t_cmd[u].args = NULL;
		}
		u++;
	}
	free(ar_t_cmd);
	return ;
}
