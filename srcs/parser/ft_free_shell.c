/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:49:54 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/26 14:19:50 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

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

void		free_close_fd(t_cmd *ar_t_cmd, int len)
{
	int		u;

	u = 0;
	while (u < len)
	{
		//printf("close fd = %d, if fd != 0\n", ar_t_cmd[u].in);
		if (ar_t_cmd[u].in != 0)
			close(ar_t_cmd[u].in);
		//printf("close fd =%d, if fd != 1\n", ar_t_cmd[u].out);
		if (ar_t_cmd[u].out != 1)
			close(ar_t_cmd[u].out);
		u++;
	}
	return ;
}
