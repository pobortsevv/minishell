/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 01:17:24 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 18:33:41 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_print_export(char **ev, int out)
{
	char	**buf;
	size_t	i;

	buf = ft_copy_envp(ev);
	env_sort(buf, env_len(ev));
	if (!buf)
		exit(1);
	i = 0;
	while (buf[i])
	{
		print_export_until(buf[i], out);
		i++;
	}
	ft_free_mat(buf);
}

char		**change_value(char *var, char **ev)
{
	size_t	i;
	size_t	var_len;

	i = 0;
	var_len = 0;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	while (ev[i])
	{
		if (!ft_strncmp(var, ev[i], var_len))
		{
			ft_free_line(&ev[i]);
			ev[i] = ft_strdup(var);
			return (ev);
		}
		i++;
	}
	return (ev);
}

char		**add_value(char *var, char **ev)
{
	size_t	env_count;
	size_t	i;
	char	**evc;

	if (!ev)
		return (NULL);
	env_count = 0;
	i = 0;
	while (ev[env_count])
		env_count++;
	evc = (char **)malloc(sizeof(char *) * (env_count + 2));
	if (!evc)
	{
		g_shell.status = 1;
		return (NULL);
	}
	while (i < env_count)
	{
		evc[i] = ft_strdup(ev[i]);
		i++;
	}
	evc[i] = ft_strdup(var);
	evc[i + 1] = NULL;
	ft_free_mat(ev);
	return (evc);
}

int			export_func(char *arg, char **ev)
{
	size_t	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if ((!arg[i] || arg[i] == '=') && !find_value(arg, ev))
		return (ADD_VALUE);
	if (arg[i] == '=' && find_value(arg, ev))
		return (CHANGE_VALUE);
	return (0);
}

char		**ft_export(t_cmd *cmd, char **ev)
{
	int	i;
	int	find;

	i = 1;
	g_shell.status = 0;
	if (cmd->len_args == 1 || !cmd->args[1])
	{
		ft_print_export(ev, cmd->out);
		return (ev);
	}
	while (i < cmd->len_args)
	{
		if (arg_check(cmd->args[i]))
		{
			i++;
			continue;
		}
		find = export_func(cmd->args[i], ev);
		if (find == ADD_VALUE)
			ev = add_value(cmd->args[i], ev);
		else if (find == CHANGE_VALUE)
			change_value(cmd->args[i], ev);
		i++;
	}
	return (ev);
}
