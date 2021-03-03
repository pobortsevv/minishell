/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:47:01 by sabra             #+#    #+#             */
/*   Updated: 2021/03/03 16:01:31 by mlaureen         ###   ########.fr       */
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
	t_command	sh;
	char		**w_envp=NULL;
	t_list		*t;

	ft_init(&sh, envp, w_envp);
	while (1)
	{
		ft_read(&str);
		if (str == NULL)
			return (error_message(PROBLEM_WITH_MALLOC));
		//TODO заменить envp  на w_envp, когда реализуем копирование
	//	printf("before parser str =<%s>\n", str); 
		ft_parser(&sh, envp, str);
//		printf("str =<%s>, flag =%d\n", sh.inst, sh.flag); 
//		t = sh.arg;
//		while (t != NULL)
//		{
//			printf("%s\n", (char *)(t->content));
//			t = t->next;
//		}

		// TODO вызов реализации команды со структурой sh

		// TODO  кейс: export qwe=1234; echo $qwe
		//  если парсер создат "листы комманд", то надо заново парсить, 
		//  для раскрытия - соответсвенно на этапе парсинга не имеет смысла раскрывать? .
		//  надо парсить по  PIPE  кейс: cat | ls    
		//  	начнут одновременно но ls закроет stdin, и cat получит 1 строчку
		//  - у каждой команды свой stdin, stdout - это надо прописать 

	}
	free(str);
	if (argc && argv[0] && envp[0])
		;
	return (0);
}
