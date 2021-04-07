/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_utilit1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 08:29:17 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/07 09:24:30 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_term_nl(char **s)
{
	ft_bzero((*s), 256);
	write(1, "\n", 1);
	ft_putstr_fd("\033[0;35m\033[1mminishell> \033[0m", STDOUT);
	return ;
}

void	ft_term_bs(char **s, t_hstr **el)
{
	int		len;
	char	buf[100];
	char	*buffer;

	ft_bzero((*s), 256);
	buffer = buf;
	ft_bzero(buffer, 100);
	len = ft_strlen((*el)->cmd);
	if (len > 0)
	{
		(*el)->cmd[len - 1] = '\0';
		tputs(tgetstr("kb", &buffer), 1, ft_putint);
	}
	buffer = buf;
	ft_bzero(buffer, 100);
	tputs(tgetstr("cd", &buffer), 1, ft_putint);
	return ;
}
