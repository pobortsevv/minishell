/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:05:37 by sabra             #+#    #+#             */
/*   Updated: 2021/03/31 18:59:08 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**ft_exec_pipe(t_cmd *ar_cmd, char **env, int cmd_count)
{
	int 	i;
	pid_t	pid;
	char 	*line;
	char	*path;

	i = 0;
	errno = 0;
	path = ft_var_find("PATH", env);
	while (i < cmd_count)
	{
		if (ar_cmd[i].out != 1)
			dup2(ar_cmd[i].out, 1);
		if (ar_cmd[i].in != 0)
			dup2(ar_cmd[i].in, 0);
		if ((pid = fork()) == -1)
		{
			shell.status = errno;
			ft_putstr_fd(strerror(errno), ar_cmd[i].out);
			return (env);
		}
		if (pid == 0)
		{
			if (i > 0 && ar_cmd[i].in != 0)
				close(ar_cmd[i - 1].out);
			if (i < cmd_count - 1 && ar_cmd[i].out != 1)
				close(ar_cmd[i + 1].in);
			line = ft_find_bin(ar_cmd[i].args[0], path);
			if (line)
				execve(line, &ar_cmd[i].args[0], env);
			ft_free_line(&line);
		}
		else
		{
			wait(&shell.status);
			if (ar_cmd[i].in != 0)
				close(ar_cmd[i].in);
			if (ar_cmd[i].out != 1)
				close(ar_cmd[i].out);
		}
		if (shell.status != 0)
			return (env);
		i++;
	}
	dup2(shell.in_tmp, 0);
	return (env);
}
