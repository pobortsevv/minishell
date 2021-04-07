/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:40:57 by sabra             #+#    #+#             */
/*   Updated: 2021/04/07 14:29:18 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	is_num_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", str);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_cmd *cmd)
{
	size_t	len;

	len = 0;
	if (!cmd)
	{
		ft_putendl_fd("\nexit", STDOUT);
		exit(0);
		return (0);
	}
	while (cmd->args[len])
		len++;
	if (len == 2)
	{
		if (!is_num_arg(cmd->args[1]))
			shell.status = ft_atoi(cmd->args[1]);
	}
	if (len > 2)
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
	// TODO почистить копию массива
	// TODO почистить полный лист
	ft_free_mat(cmd->args);
	ft_putstr_fd("exit\n", STDOUT);
	exit(shell.status);
	return (shell.status);
}
