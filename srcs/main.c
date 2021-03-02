/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:47:01 by sabra             #+#    #+#             */
/*   Updated: 2021/03/02 14:14:38 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

static int		error_message(int error)
{
	ft_putendl_fd("Error", FD_ERR);
	if (error == PROBLEM_WITH_MALLOC)
		ft_putendl_fd("Problem with memeory (malloc)", FD_ERR);
	return (error);
}

int				main(int argc, char **argv, char **envp)
{
	char		*str;

	while (1)
	{
		ft_read(&str);
		if (str == NULL)
			return (error_message(PROBLEM_WITH_MALLOC));
	//	ft_parser(&sh, envp, str1);
	}
	free(str);
	if (argc && argv[0] && envp[0])
		;
	return (0);
}
