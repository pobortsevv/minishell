/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:47:01 by sabra             #+#    #+#             */
/*   Updated: 2021/03/04 10:51:37 by mlaureen         ###   ########.fr       */
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

void			exec_cmd(t_sh *sh, char **envp)
{
	//size_t	cmds_len;
	//size_t	i;
	
	if ((ft_strncmp(sh->inst, "pwd", ft_strlen(sh->inst))) == 0)
		pwd(sh, envp);

}

int			main(int argc, char **argv, char **envp)
{
	char		*str;
	t_cmd		sh;
	char		**w_envp=NULL;
//	int			i = 0;

	ft_init(&sh, envp, w_envp);
	while (1)
	{
		ft_read(&str);
		if (str == NULL)
			return (error_message(PROBLEM_WITH_MALLOC));
		//TODO заменить envp  на w_envp, когда реализуем копирование
		//	printf("before parser str =<%s>\n", str);

		ft_parser(&sh, envp, str);

//		printf("id = %d\n", sh.id); 
//		while (sh.args[i] != NULL)
//		{
//			printf("%s\n", sh.args[i]);
//			i++;
//		}

		// TODO вызов реализации команды со структурой sh

		//exec_cmd(&sh, envp);

		// TODO  кейс: export qwe=1234; echo $qwe
		//  если парсер создат "листы комманд", то надо заново парсить, 
		//  для раскрытия - соответсвенно на этапе парсинга не имеет смысла раскрывать? .
		//  надо парсить по  PIPE  кейс: cat | ls    
		//  	начнут одновременно но ls закроет stdin, и cat получит 1 строчку
		//  - у каждой команды свой stdin, stdout - это надо прописать 

	}
	//TODO очистка массива sh.array
	free(str);
	if (argc && argv[0] && envp[0])
		;
	return (0);
}
