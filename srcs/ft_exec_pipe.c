/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:05:37 by sabra             #+#    #+#             */
/*   Updated: 2021/04/01 00:00:09 by sabra            ###   ########.fr       */
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
		if ((pid = fork()) == -1)
		{
			shell.status = errno;
			ft_putstr_fd(strerror(errno), ar_cmd[i].out);
			return (env);
		}
		if (pid == 0)
		{
			if (i != 0)
				dup2(ar_cmd[i - 1].out, 0);
			if (i != cmd_count - 2)
				dup2(ar_cmd[i + 1].in, 1);
			line = ft_find_bin(ar_cmd[i].args[0], path);
			if (line)
				execve(line, &ar_cmd[i].args[0], env);
			else 
			{
				shell.status = init_command(&ar_cmd[i], env);
				exit(shell.status);
			}
			close(ar_cmd[i].in);
			close(ar_cmd[i].out);
			dup2(shell.in_tmp, 0);
			ft_free_line(&line);
		}
		i++;
	}
	while (cmd_count-- > 0)
		wait(&shell.status);	
	dup2(shell.in_tmp, 0);
	return (env);
}
