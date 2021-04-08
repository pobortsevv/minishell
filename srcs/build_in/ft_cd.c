/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:31:12 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 19:06:17 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char		**change_dir_env(char *value, char **ev)
{
	char *var;

	var = ft_strjoin("PWD=", value);
	ev = change_value(var, ev);
	ft_free_line(&var);
	return (ev);
}

char		**add_oldpwd(char **ev)
{
	char	*tmp;
	char	*old_pwd;

	tmp = ft_find_env("OLDPWD", ev);
	if (tmp)
	{
		old_pwd = getcwd(NULL, 0);
		tmp = ft_strjoin("OLDPWD=", old_pwd);
		ev = change_value(tmp, ev);
		ft_free_line(&tmp);
		if (old_pwd)
			ft_free_line(&old_pwd);
	}
	else
	{
		old_pwd = getcwd(NULL, 0);
		tmp = ft_strjoin("OLDPWD=", old_pwd);
		ev = add_value(tmp, ev);
		if (tmp)
			ft_free_line(&tmp);
		if (old_pwd)
			ft_free_line(&old_pwd);
	}
	return (ev);
}

char		**change_arg_dir(t_cmd *cmd, char **ev)
{
	int		res;
	char	*tmp;

	res = 0;
	res = chdir(cmd->args[1]);
	if (res == -1)
	{
		g_shell.status = errno;
		ft_putendl_fd(strerror(errno), STDERR);
		return (ev);
	}
	if (cmd->len_args > 1)
	{
		tmp = getcwd(NULL, 0);
		if (!tmp)
			return (ev);
		ev = change_dir_env(tmp, ev);
		ft_free_line(&tmp);
	}
	return (ev);
}

char		**ft_cd(t_cmd *cmd, char **ev)
{
	int		res;
	char	*root;

	errno = 0;
	res = 0;
	ev = add_oldpwd(ev);
	if (cmd->len_args == 1 || !ft_strcmp(cmd->args[1], "~"))
	{
		root = ft_var_find("HOME", ev);
		if (!root)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDOUT);
			return (ev);
		}
		res = chdir(root);
		ev = change_dir_env(root, ev);
		ft_free_line(&root);
	}
	else if (cmd->len_args >= 2)
		ev = change_arg_dir(cmd, ev);
	return (ev);
}
