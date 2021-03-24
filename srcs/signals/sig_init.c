/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:37:59 by sabra             #+#    #+#             */
/*   Updated: 2021/03/24 22:36:52 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	sig_int(int id)
{
	ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_putstr_fd("\nminishell> ", STDOUT);
	(void)id;
}

void	sig_quit(int id)
{
	ft_putstr_fd("\b\b  \b\b", STDERR);
	(void)id;
}

/*
 * Устанавливается перехватчик сигнала, если сигнал не игнорируется
 */

void	sig_init(void)
{
	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, sig_int);
	if (signal(SIGQUIT, SIG_IGN) != SIG_IGN)
		signal(SIGQUIT, sig_quit);
}
