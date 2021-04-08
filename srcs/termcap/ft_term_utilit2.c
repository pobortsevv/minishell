/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_utilit2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 07:53:01 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 19:40:44 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_term_exit(void)
{
	ft_putendl_fd("\nexit", STDOUT);
	exit(0);
	return ;
}

void	ft_term_print(char **s, t_hstr **el)
{
	write(1, (*s), 1);
	(*s)[1] = '\0';
	if (g_shell.sig_flag == 1)
	{
		g_shell.sig_flag = 0;
		(*el)->cmd[0] = '\0';
	}
	if ((*s)[0] != '\n')
		ft_strlchar((*el)->cmd, (*s)[0], 1024);
}
