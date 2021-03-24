/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parser_shell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:41:40 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/24 08:17:57 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**ft_parser_er2(char *error)
{
	//TODO  печать в поток 2
	ft_printf("%s\n", error);
	return (NULL);
}

char	*ft_parser_er1(char *error)
{
	ft_printf("%s\n", error);
	return (NULL);
}

char	**ft_parser_err_free2(char *error, char **a)
{
	int		i;

	i = 0;
	ft_printf("%s\n", error);
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

int		ft_parser_err_fd(char *name)
{
	ft_putstr_fd("Error: Permission deniedied", 2);
	ft_putstr_fd(name, 2);
	return (-1);
}

