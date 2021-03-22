/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ /*   ft_exit.c                                          :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */ /*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */ /*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:33:40 by sabra             #+#    #+#             */
/*   Updated: 2021/03/09 15:04:09 by sabra            ###   ########.fr       */
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
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	size_t	len;
	int	error_code;

	len = 0;
	error_code = 0;
	while (cmd->args[len])
		len++;
	if (len == 2)
	{
		if (is_num_arg(cmd->args[1]))
			error_code = ft_atoi(cmd->args[1]);
	}
	if (len > 2)
		ft_printf("minishell: exit: too many arguments\n");
	// TODO почистить копию массива
	// TODO почистить полный лист
	//ft_lstclear(&list, free);
	ft_free_mat(cmd->args);
	ft_printf("exit\n");
	exit(error_code);
	return (1);
}
