/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:05:37 by sabra             #+#    #+#             */
/*   Updated: 2021/04/01 16:56:33 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_cmd 	*close_files(t_cmd *ar_cmd, int i, int cmd_count)
{
	if (i > 0 && ar_cmd[i].in != 0 && ar_cmd[i - 1].out != 1)
		close(ar_cmd[i - 1].out);
	if (i != cmd_count - 1 && ar_cmd[i].out != 1 
				&& ar_cmd[i + 1].in != 0)
		close(ar_cmd[i + 1].in);
	return (ar_cmd);
}

char	**ft_exec_pipe(t_cmd *ar_cmd, char **env, int cmd_count)
{
	int 	i;
	pid_t	pid;
	char 	*line;
	char	*path;
	//char	tmp[512];

	i = 0;
	errno = 0;
	path = ft_var_find("PATH", env);
	close(0);
	close(1);
	while (i < cmd_count)
	{
		if (i == 0)
			dup2(shell.in_tmp, 0);
		if (ar_cmd[i].in != 0)
			dup2(ar_cmd[i].in, 0);
		if (i == cmd_count - 1)
			dup2(shell.out_tmp, 1);
		if (ar_cmd[i].out != 1)
			dup2(ar_cmd[i].out, 1);
		//dup2(ar_cmd[i].in, 0);
		//dup2(ar_cmd[i].out, 1);
		if ((pid = fork()) == -1)
		{
			shell.status = errno;
			ft_putstr_fd(strerror(errno), ar_cmd[i].out);
			return (env);
		}
		if (pid == 0)
		{
			//if(i != 0)
				//close(0);
			shell.status = init_command(&ar_cmd[i], env);
			if (shell.status != 127)
				exit(shell.status);
			line = ft_find_bin(ar_cmd[i].args[0], path);
			if (line)
			{
				//close_files(ar_cmd, i, cmd_count);
				execve(line, &ar_cmd[i].args[0], env);
			}
			if (line)
				ft_free_line(&line);
		}
		close(ar_cmd[i].in);
		close(ar_cmd[i].out);
		//close_files(ar_cmd, i, cmd_count);
		i++;
	}
	while (cmd_count-- > 0)
		wait(&shell.status);
	dup2(shell.in_tmp, 0);
	dup2(shell.out_tmp, 1);
	return (env);
}
