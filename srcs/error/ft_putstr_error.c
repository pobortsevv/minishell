/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 06:56:30 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 18:37:10 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_putstr_error(char *str, int er)
{
	ft_putstr_fd("minishell: ", g_shell.out_tmp);
	ft_putstr_fd(str, g_shell.out_tmp);
	ft_putstr_fd("\n", g_shell.out_tmp);
	g_shell.status = er;
	return ;
}

int		ft_check_er_args(t_cmd *ar_t_cmd, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if (ar_t_cmd[j].args == NULL)
		{
			ft_putstr_error("command not found", 127);
			free_close_fd(ar_t_cmd, len);
			free(ar_t_cmd);
			return (-1);
		}
		if (ar_t_cmd[j].in < 0 || ar_t_cmd[j].out < 0)
		{
			g_shell.status = 1;
			free_close_fd(ar_t_cmd, len);
			free_t_cmd(ar_t_cmd, len);
			return (-1);
		}
		j++;
	}
	return (0);
}
