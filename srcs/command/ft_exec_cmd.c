/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:09:44 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 18:30:50 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char			**ft_exec_cmd(t_cmd *ar_cmd, char **env, int cmd_count)
{
	if (cmd_count > 1)
		return (ft_exec_pipe(ar_cmd, env, cmd_count));
	if (cmd_count == 1)
	{
		ft_stolower(ar_cmd[0].args[0]);
		if ((ft_strcmp(ar_cmd[0].args[0], "unset")) == 0)
			return (ft_unset(&ar_cmd[0], env));
		else if ((ft_strcmp(ar_cmd[0].args[0], "export")) == 0)
			return (ft_export(&ar_cmd[0], env));
		else if ((ft_strcmp(ar_cmd[0].args[0], "cd")) == 0)
			return (ft_cd(&ar_cmd[0], env));
		else
		{
			g_shell.status = init_command(&ar_cmd[0], env);
			if (g_shell.status == 127)
				handle_cmd_not_found(ar_cmd[0].args[0]);
		}
	}
	return (env);
}
