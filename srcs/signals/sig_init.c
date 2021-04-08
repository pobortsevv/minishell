/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:37:59 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 18:35:47 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	sig_stub(int id)
{
	(void)id;
}

void	sig_int(int id)
{
	g_shell.sig_flag = 1;
	ft_putstr_fd("\n\033[0;35m\033[1mminishell> \033[0m", STDOUT);
	(void)id;
}

void	sig_quit(int id)
{
	(void)id;
}

void	sig_init(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}
