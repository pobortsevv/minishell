/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 01:17:24 by sabra             #+#    #+#             */
/*   Updated: 2021/03/23 17:44:33 by sabra            ###   ########.fr       */
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

//int		quote_check(char *arg)
//{
	//int result;
	//int i;
//
	//i = 0;
	//result = 0;
	//while (arg[i])
	//{
		//if (arg[])
	//}
//}

static int	arg_check(char *arg)
{
	int i;
	int result;

	i = 0;
	result = 1;
	//if (arg[0] == '\"' || arg[0] == '\'')
		//result = quote_check(arg);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_printf("minishell: export: `%s': not a valid identifier'\n", arg);
		return (0);
	}
	return (1);
}

void	ft_print_export(char **ev)
{
	char	**buf;
	size_t	i;
	size_t	j;

	buf = ft_copy_envp(ev);
	env_sort(buf);
	if (!buf)
		return (0);
	i = 0;
	while(buf[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (buf[i][j] && buf[i][j] != '=')
			write(1, &buf[i][j++], 1);
		if (!buf[i][j])
		{
			write(1, "\n", 1);
			i++;
			continue;
		}
		else if (buf[i][j] == '=' && buf[i][j + 1] == '\0')
		{
			write(1, "=\"\"\n", 4);
			i++;
			continue;
		}
		ft_printf("%c\"", buf[i][j++]);
		while (buf[i][j])
			write(1, &buf[i][j++], 1);
		write(1, "\"\n", 2);
		i++;
	}
	ft_free_mat(buf);
}

int		ft_export(t_cmd *cmd, char **ev)
{
	int	i;
	
	i = 0;
	if (cmd->len_args == 1)
	{
		ft_print_export(ev);
		return (1);
	}
	if (cmd->len_args > 1)
	{
		if (!arg_check(cmd->args[i]))
		{
			i++;
		}
	}
	return (1);
}
