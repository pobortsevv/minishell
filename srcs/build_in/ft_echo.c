/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:06:48 by sabra             #+#    #+#             */
/*   Updated: 2021/04/01 16:43:30 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int i;
	int status;

	status = 0;
	i = 1;
	if (!ft_strcmp(cmd->args[1], "-n"))
	{
			status = 1;
			i++;
	}
	while (i < cmd->len_args)
	{
		ft_putstr_fd(cmd->args[i], STDOUT);
		ft_putstr_fd(" ", STDOUT);
		i++;
	}
	if (!status)
		write(STDOUT, "\n", 1);
	return (0);
}
