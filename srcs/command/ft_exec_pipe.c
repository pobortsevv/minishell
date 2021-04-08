/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:05:37 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 14:44:33 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		init_cmd_pipe(t_cmd *cmd, char **env)
{
	if ((ft_strcmp(cmd->args[0], "pwd")) == 0)
		return (ft_pwd(cmd->out));
	if ((ft_strcmp(cmd->args[0], "env")) == 0)
		return (ft_env(env, cmd->out));
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

void	child_pro(t_cmd *ar_cmd, char **env, char *path)
{
	char *line;

	shell.status = init_cmd_pipe(ar_cmd, env);
	if (shell.status != 127)
		exit(shell.status);
	line = ft_find_bin(ar_cmd->args[0], path);
	if (line)
		shell.status = execve(line, &ar_cmd->args[0], env);
	if (line)
		ft_free_line(&line);
	if (shell.status == 127)
	{
		handle_cmd_not_found(ar_cmd->args[0]);
		exit(127);
	}
}

void	wait_pros(pid_t pid)
{
	while (waitpid(pid, &shell.status, 0) > 0)
		;
	while (wait(NULL) > 0)
		;
}

char	**ft_exec_pipe(t_cmd *ar_cmd, char **env, int cmd_count)
{
	int		i;
	pid_t	pid;
	char	*path;

	i = 0;
	exec_pipe_init(&path, env);
	while (i < cmd_count)
	{
		dup_start(&ar_cmd[i]);
		if ((pid = fork()) == -1)
		{
			shell.status = errno;
			ft_putstr_fd(strerror(errno), ar_cmd[i].out);
			return (env);
		}
		if (pid == 0)
		{
			close_files(ar_cmd, i, cmd_count);
			child_pro(&ar_cmd[i], env, path);
		}
		dup_end(&ar_cmd[i]);
		i++;
	}
	wait_pros(pid);
	return (env);
}
