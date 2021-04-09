/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:14:30 by sabra             #+#    #+#             */
/*   Updated: 2021/04/09 01:29:59 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

t_sh			g_shell;

int				init_command(t_cmd *cmd, char **envp)
{
	char	*path;
	char	*filename;
	int		result;

	result = 127;
	if ((ft_strcmp(cmd->args[0], "pwd")) == 0)
		return (ft_pwd(cmd->out));
	if ((ft_strcmp(cmd->args[0], "env")) == 0)
		return (ft_env(envp, cmd->out));
	if ((ft_strcmp(cmd->args[0], "echo")) == 0)
		return (ft_echo(cmd));
	if ((ft_strcmp(cmd->args[0], "exit")) == 0)
		return (ft_exit(cmd));
	path = ft_var_find("PATH", envp);
	if ((filename = ft_find_bin(cmd->args[0], path)))
		result = ft_exec_bin(cmd, filename, envp);
	if (path)
		ft_free_line(&path);
	return (result);
}

int				handle_cmd_not_found(char *name)
{
	ft_putstr_fd("minishell: ", g_shell.out_tmp);
	ft_putstr_fd(name, g_shell.out_tmp);
	ft_putendl_fd(": command not found", g_shell.out_tmp);
	return (127);
}

char			**init_main(char **evc, char **envp)
{
	ft_bzero(&g_shell, sizeof(t_sh));
	evc = ft_copy_envp(envp);
	evc = ft_init_envp(evc, 0);
	if (!evc)
	{
		ft_putstr_fd("Problems with env\n", STDERR);
		exit(1);
	}
	g_shell.in_tmp = dup(0);
	g_shell.out_tmp = dup(1);
	g_shell.term = ft_var_find("TERM", evc);
	g_shell.home = ft_var_find("HOME", evc);
	g_shell.sig_flag = 0;
	return (evc);
}

char			**helper_main(char *str, char **evc, int gnl)
{
	int			res;

	if ((res = ft_check_str(str)) != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		g_shell.status = 258;
		if (str)
			ft_free_line(&str);
	}
	else
	{
		if (gnl == 0 && *str == '\0')
			ft_exit(NULL);
		evc = ft_parser_shell(evc, str);
		if (!evc)
		{
			printf("Error with shell\n");
			return (NULL);
		}
		if (str)
			ft_free_line(&str);
	}
	return (evc);
}

int				main(int argc, char **argv, char **envp)
{
	char		*str;
	char		**evc;
	int			gnl;
	t_hstr		*el;

	str = NULL;
	evc = NULL;
	evc = init_main(evc, envp);
	(void)argv;
	(void)argc;
	el = ft_make_el();
	g_shell.start = el;
	while (1)
	{
		sig_init();
		gnl = ft_give_str(&str);
		if (!(evc = helper_main(str, evc, gnl)))
			break ;
	}
	ft_free_mat(evc);
	if (str)
		free(str);
	return (0);
}
