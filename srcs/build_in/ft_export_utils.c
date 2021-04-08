/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:54:15 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 18:34:05 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		print_export_until(char *buf, int out)
{
	size_t j;

	j = 0;
	ft_putstr_fd("declare -x ", out);
	while (buf[j] && buf[j] != '=')
		write(out, &buf[j++], 1);
	if (!buf[j])
	{
		write(out, "\n", 1);
		return ;
	}
	else if (buf[j] == '=' && buf[j + 1] == '\0')
	{
		write(out, "=\"\"\n", 4);
		return ;
	}
	ft_putchar_fd(buf[j++], out);
	write(out, "\"", 1);
	while (buf[j])
		write(out, &buf[j++], 1);
	write(out, "\"\n", 2);
}

size_t		env_len(char **env)
{
	size_t	len;

	len = 0;
	while (env[len])
		len++;
	len -= 2;
	return (len);
}

void		env_sort(char **a, size_t len)
{
	size_t	i;
	size_t	turn;
	char	*buf;

	i = 0;
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

int			arg_check(char *arg)
{
	int i;
	int result;

	i = 0;
	result = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_printf("minishell: export: `%s': not a valid identifier'\n", arg);
		g_shell.status = 1;
		return (1);
	}
	return (0);
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
