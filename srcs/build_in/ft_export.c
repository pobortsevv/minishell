/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 01:17:24 by sabra             #+#    #+#             */
/*   Updated: 2021/04/07 15:22:24 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	env_sort(char **a)
{
	size_t	i;
	size_t	len;
	size_t	turn;
	char	*buf;

	i = 0;
	len = 0;
	while(a[len++])
		;
	len -= 2;
	turn = 0;
	while (a && turn == 0)
	{
		i = 0;
		turn = 1;
		while (i < len - 1)
		{
			if (ft_strncmp(a[i], a[i + 1], FILENAME_MAX) > 0)
			{
				turn = 0;
				buf = a[i];
				a[i] = a[i + 1];
				a[i + 1] = buf;
			}
			i++;
		}
		len--;
	}
}

static int	arg_check(char *arg)
{
	int i;
	int result;

	i = 0;
	result = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_printf("minishell: export: `%s': not a valid identifier'\n", arg);
		shell.status = 1;
		return (1);
	}
	return (0);
}

void	ft_print_export(char **ev, int out)
{
	char	**buf;
	size_t	i;
	size_t	j;

	buf = ft_copy_envp(ev);
	env_sort(buf);
	if (!buf)
		exit(1);
	i = 0;
	while(buf[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", out);
		while (buf[i][j] && buf[i][j] != '=')
			write(out, &buf[i][j++], 1);
		if (!buf[i][j])
		{
			write(out, "\n", 1);
			i++;
			continue;
		}
		else if (buf[i][j] == '=' && buf[i][j + 1] == '\0')
		{
			write(out, "=\"\"\n", 4);
			i++;
			continue;
		}
		ft_putchar_fd(buf[i][j++], out);
		write(out, "\"", 1);
		while (buf[i][j])
			write(out, &buf[i][j++], 1);
		write(out, "\"\n", 2);
		i++;
	}
	ft_free_mat(buf);
}

char		*find_value(char *key, char **ev)
{
	size_t	i;

	i = 0;
	while (ev[i])
	{
		if (ft_unstr(ev[i], key))
			return (ev[i]);
		i++;
	}
	return (NULL);
}

char		**change_value(char *var, char **ev)
{
	size_t	i;
	size_t	var_len;

	i= 0;
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
	evc = (char **)malloc(sizeof(char *) * env_count + 2);
	if (!evc)
	{
		shell.status = 1;
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

int		export_func(char *arg, char **ev)
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
	shell.status = 0;
	if (cmd->len_args == 1 || !cmd->args[1])
	{
		ft_print_export(ev, cmd->out);
		return (ev);
	}
	while(i < cmd->len_args)
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
