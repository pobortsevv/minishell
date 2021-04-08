/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:53:39 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 19:15:19 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_exec_bin(t_cmd *cmd, char *filename, char **ev)
{
	pid_t	pid;

	signal(SIGINT, sig_stub);
	if (cmd->in != 0)
		dup2(cmd->in, 0);
	if (cmd->out != 1)
		dup2(cmd->out, 1);
	pid = fork();
	if (pid < 0)
		((g_shell.status = -1));
	if (pid == 0)
		g_shell.status = execve(filename, &cmd->args[0], ev);
	else
		wait(&g_shell.status);
	if (cmd->in != 0)
		dup2(g_shell.in_tmp, 0);
	if (cmd->out != 1)
		dup2(g_shell.out_tmp, 1);
	if (g_shell.status != 0)
		g_shell.status = 1;
	return (g_shell.status);
}
