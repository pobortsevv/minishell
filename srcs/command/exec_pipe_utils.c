/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:43:05 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 18:30:23 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_cmd	*close_files(t_cmd *ar_cmd, int i, int cmd_count)
{
	if (i > 0 && ar_cmd[i].in != 0 && ar_cmd[i - 1].out != 1)
		close(ar_cmd[i - 1].out);
	if (i + 1 < cmd_count && ar_cmd[i].out != 1
				&& ar_cmd[i + 1].in != 0)
		close(ar_cmd[i + 1].in);
	return (ar_cmd);
}

void	dup_start(t_cmd *ar_cmd)
{
	if (ar_cmd->in != 0 && g_shell.status == 0)
		dup2(ar_cmd->in, 0);
	if (ar_cmd->out != 1 && g_shell.status == 0)
		dup2(ar_cmd->out, 1);
}

void	dup_end(t_cmd *ar_cmd)
{
	if (ar_cmd->in != 0)
	{
		close(ar_cmd->in);
		dup2(g_shell.in_tmp, 0);
	}
	if (ar_cmd->in != 1)
	{
		close(ar_cmd->out);
		dup2(g_shell.out_tmp, 1);
	}
}

void	exec_pipe_init(char **path, char **env)
{
	errno = 0;
	*path = ft_var_find("PATH", env);
	g_shell.status = 0;
	signal(SIGINT, sig_stub);
}
