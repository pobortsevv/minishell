/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:47:01 by sabra             #+#    #+#             */
/*   Updated: 2021/03/02 11:22:57 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_command	sh;
	char		*str = "echo 'hello word' >> text.txt";

	ft_parser(&sh, envp, str);
	return (0);
}
