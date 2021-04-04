/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:05:37 by sabra             #+#    #+#             */
/*   Updated: 2021/04/04 15:23:33 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_cmd 	*close_files(t_cmd *ar_cmd, int i, int cmd_count)
{
	if (i > 0 && ar_cmd[i].in != 0 && ar_cmd[i - 1].out != 1)
		close(1);
	if (i != cmd_count - 1 && ar_cmd[i].out != 1 
				&& ar_cmd[i + 1].in != 0)
		close(0);
	return (ar_cmd);
}

int		init_cmd_pipe(t_cmd *cmd, char **env)
{
	if (!env)
		return (-1);
	if ((ft_strcmp(cmd->args[0], "pwd")) == 0)
		return (ft_pwd());
	if ((ft_strcmp(cmd->args[0], "env")) == 0)
		return (ft_env(env));
	if ((ft_strcmp(cmd->args[0], "echo")) == 0)
		return (ft_echo(cmd));
	if ((ft_strcmp(cmd->args[0], "exit")) == 0)
		return (ft_exit(cmd));
	if ((ft_strcmp(cmd->args[0], "unset")) == 0)
	{
		env = ft_unset(cmd, env);
		return (0);
	}
	else if ((ft_strcmp(cmd->args[0], "export")) == 0)
	{
		env = ft_export(cmd, env);
		return (0);
	}
	else if ((ft_strcmp(cmd->args[0], "cd")) == 0)
	{
		env = ft_cd(cmd, env);
		return (0);
	}
	return (127);
}

char	**ft_exec_pipe(t_cmd *ar_cmd, char **env, int cmd_count)
{
	int 	i;
	pid_t	pid;
	char 	*line;
	char	*path;

	i = 0;
	errno = 0;
	path = ft_var_find("PATH", env);
	shell.status = 0;
	while (i < cmd_count)
	{
		if (i == 0)
			dup2(shell.in_tmp, 0);
		if (ar_cmd[i].in != 0 && shell.status == 0)
		{
			dup2(ar_cmd[i].in, 0);
			close(ar_cmd[i].in);
		}
		if (ar_cmd[i].out != 1 && shell.status == 0)
		{
			dup2(ar_cmd[i].out, 1);
			close(ar_cmd[i].out);
		}
		if (ar_cmd[i].out == 1 && shell.status == 0)
			dup2(shell.out_tmp, 1);
		if ((pid = fork()) == -1)
		{
			shell.status = errno;
			ft_putstr_fd(strerror(errno), ar_cmd[i].out);
			return (env);
		}
		if (pid == 0)
		{
			sig_init();
			shell.status = init_cmd_pipe(&ar_cmd[i], env);
			if (shell.status != 127)
				exit(shell.status);
			line = ft_find_bin(ar_cmd[i].args[0], path);
			if (line)
			{
				//close_files(ar_cmd, i, cmd_count);
				shell.status = execve(line, &ar_cmd[i].args[0], env);
			}
			if (line)
				ft_free_line(&line);
			if (shell.status == 127)
			{
				handle_cmd_not_found(ar_cmd[i].args[0]);
				exit(127);
			}
		}
		close(0);
		close(1);
		i++;
	}
	while (cmd_count-- > 0)
		wait(&shell.status);
	dup2(shell.in_tmp, 0);
	dup2(shell.out_tmp, 1);
	return (env);
}
