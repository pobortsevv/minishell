/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parser_shell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:41:40 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 18:36:40 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**ft_parser_er2(char *error)
{
	ft_putstr_fd("minishell: ", g_shell.out_tmp);
	ft_putstr_fd(error, g_shell.out_tmp);
	ft_putstr_fd("\n", g_shell.out_tmp);
	return (NULL);
}

char	*ft_parser_er1(char *error)
{
	ft_putstr_fd("minishell: ", g_shell.out_tmp);
	ft_putstr_fd(error, g_shell.out_tmp);
	ft_putstr_fd("\n", g_shell.out_tmp);
	return (NULL);
}

char	**ft_parser_err_free2(char *error, char **a)
{
	int		i;

	i = 0;
	ft_putstr_fd("minishell: ", g_shell.out_tmp);
	ft_putstr_fd(error, g_shell.out_tmp);
	ft_putstr_fd("\n", g_shell.out_tmp);
	while (a && a[i])
	{
		free(a[i]);
		a[i] = NULL;
		i++;
	}
	if (a)
	{
		free(a);
		a = NULL;
	}
	return (NULL);
}

char	**ft_parser_free2(char **a)
{
	int		i;

	i = 0;
	while (a && a[i])
	{
		free(a[i]);
		a[i] = NULL;
		i++;
	}
	if (a)
	{
		free(a);
		a = NULL;
	}
	return (NULL);
}

int		ft_parser_err_fd(char **name)
{
	ft_putstr_fd("minishell: ", g_shell.out_tmp);
	ft_putstr_fd(*name, g_shell.out_tmp);
	ft_putstr_fd(": Permission deniedied\n", g_shell.out_tmp);
	if (*name != NULL)
	{
		free(*name);
		*name = NULL;
	}
	g_shell.status = 1;
	return (1);
}
