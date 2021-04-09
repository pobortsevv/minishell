/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:06:48 by sabra             #+#    #+#             */
/*   Updated: 2021/04/09 17:29:52 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*check_tilda(char *arg)
{
	int		i;
	char	*new;

	i = 0;
	if (arg[1] && !ft_strncmp("~", arg, 1) && arg[1] == '/')
	{
		new = ft_strjoin(g_shell.home, &arg[1]);
		ft_free_line(&arg);
		return (new);
	}
	else if (!arg[1] && !ft_strncmp("~", arg, 1))
	{
		new = ft_strdup(g_shell.home);
		ft_free_line(&arg);
		return (new);
	}
	return (arg);
}

int		check_flag(char *arg)
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

int		ft_echo(t_cmd *cmd)
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
	while (cmd->args[i] && i < cmd->len_args)
	{
		if (!check_flag(cmd->args[i]))
		{
			cmd->args[i] = check_tilda(cmd->args[i]);
			ft_putstr_fd(cmd->args[i], cmd->out);
			if (i != cmd->len_args - 1 && cmd->args[i + 1])
				ft_putstr_fd(" ", cmd->out);
		}
		i++;
	}
	if (!status)
		write(cmd->out, "\n", 1);
	return (0);
}
