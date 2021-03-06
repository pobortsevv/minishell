/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:47:01 by sabra             #+#    #+#             */
/*   Updated: 2021/03/06 12:24:33 by sabra            ###   ########.fr       */
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
// тест-функция: печать из "списка команд"

void		ft_test_pr(t_list *first)
{
	t_list	*t;
	t_cmd	*ex;
	int		i;

	t=first;
	while (t != NULL)
	{
		i = 0;
		printf("инструкция:\n");
		ex = (t_cmd *)(t->content);
		printf("id = %d\n", ex->id);
		while (ex->args[i] != NULL)
		{
			printf("%s\n", (char *)(ex->args[i]));
			i++;
		}
		t = t->next;
	}
	return ;
}

void			init_command(t_cmd *cmd, char **envp)
{
	if ((ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]))) == 0)
		pwd(cmd, envp);
	//if ((ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0]))) == 0)
		//env(cmd, envp);
}

void			exec_cmd(t_list *first, char **envp)
{
	t_list	*list;
	t_cmd	*cmd;

	list = first;
	while (list)
	{
		cmd = (t_cmd *)(list->content);
		init_command(cmd, envp);
		list = list->next;
	}

}

int			main(int argc, char **argv, char **envp)
{
	char		*str;
//	t_cmd		sh;
	t_list		first;
	char		**w_envp=NULL;

	ft_init(envp, w_envp);
	while (1)
	{
		ft_read(&str);
		if (str == NULL)
			return (error_message(PROBLEM_WITH_MALLOC));
		//TODO заменить envp  на w_envp, когда реализуем копирование
		//	printf("before parser str =<%s>\n", str);

		first = ft_parser(envp, str);
		// тестовая печать списка команд
		ft_test_pr(&first);


		// TODO вызов реализации команды со структурой sh

		exec_cmd(&first, envp);

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
