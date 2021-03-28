/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:06:48 by sabra             #+#    #+#             */
/*   Updated: 2021/03/28 12:32:54 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int i;
	int status;

	status = 0;
	i = 1;
	if (cmd->len_args > 1 && !ft_strncmp(cmd->args[1], "-n", ft_strlen(cmd->args[1])))
	{
			status = 1;
			i++;
	}
	while (i < cmd->len_args)
	{
		ft_putstr_fd(cmd->args[i], cmd->out);
		i++;
	}
	if (!status)
		write(cmd->out, "\n", 1);
	return (1);
}
