/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:37:59 by sabra             #+#    #+#             */
/*   Updated: 2021/03/24 00:25:12 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	sig_int(int signal)
{
	(void)signal;
	ft_putstr_fd("\b\b  ", STDERR);
	ft_putstr_fd("\nminishell> ", STDERR);
}

void	sig_quit(int signal)
{
	ft_putstr_fd("quit: code: ", STDERR);
	ft_putnbr_fd(signal, STDERR);
	ft_putstr_fd("\b\b  ", STDERR);
}

void	sig_init(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}
