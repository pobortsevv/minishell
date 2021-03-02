/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:47:01 by sabra             #+#    #+#             */
/*   Updated: 2021/03/02 13:39:08 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

int		main(int argc, char **argv, char **envp)
{
//	t_command	sh;
	char		*str;
//	char		*str1 = "echo 'hello word' >> text.txt";

	while (1)
	{
		ft_read(&str);
		printf("%s\n", str);
	}
	printf("%s\n", str);
	free(str);
//	ft_parser(&sh, envp, str1);
	if (argc && argv[0] && envp[0])
		;
	return (0);
}
