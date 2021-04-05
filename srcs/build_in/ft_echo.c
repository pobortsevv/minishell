/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:06:48 by sabra             #+#    #+#             */
/*   Updated: 2021/04/05 11:53:18 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	check_flag(char *arg)
{
	size_t i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i] && arg[i] == 'n')
		i++;
	if (ft_strlen(&arg[1]) != (i - 1))
		return (0);
	return (1);
}

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
		if (!check_flag(cmd->args[i]))
		{
			ft_putstr_fd(cmd->args[i], STDOUT);
			if(i != cmd->len_args - 1)
				ft_putstr_fd(" ", STDOUT);
		}
		i++;
	}
	if (!status)
		write(STDOUT, "\n", 1);
	return (0);
}
