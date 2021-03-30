/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:05:37 by sabra             #+#    #+#             */
/*   Updated: 2021/03/31 00:03:43 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**ft_exec_pipe(t_cmd *ar_cmd, char **env, int cmd_count)
{
	int 	i;
	pid_t	pid;

	i = 0;
	errno = 0;
	while (i < cmd_count)
	{
		if ((pid = fork()) == -1)
		{
			shell.status = errno;
			ft_putstr_fd(strerror(errno), ar_cmd[i].out);
			return (env);
		}
		if (pid == 0)
		{
			dup2(ar_cmd[i].out, 1);
			close(ar_cmd[i].in);
			execve(ar_cmd[i].args[0], NULL, env); // TODO передать первым аргументом строчку пайпа
			close(ar_cmd[i].out);
		}
		else if (pid > 0)
		{
			dup2(ar_cmd[i].in, 0);
			close(ar_cmd[i].out);
			wait(&shell.status);
			close(ar_cmd[i].in);
		}
		if (shell.status != 0)
			return (env);
		i++;
	}
	shell.status = 0;
	return (env);
}
