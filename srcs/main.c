/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:47:01 by sabra             #+#    #+#             */
/*   Updated: 2021/03/20 08:00:38 by mlaureen         ###   ########.fr       */
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

int			init_command(t_cmd *cmd, char **envp, t_list *list)
{
	if ((ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]))) == 0)
		return (ft_pwd());
	if ((ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0]))) == 0)
		return (ft_env(envp));
	if ((ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]))) == 0)
		return (ft_export(cmd, envp));
	if ((ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]))) == 0)
		return (ft_cd(cmd));
	if ((ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0]))) == 0)
		return (ft_exit(cmd, list));
	return (1);
}
/*
void			exec_cmd(t_cmd *ar_cmd, char **env, int cmd_count)
{
	size_t i;

	i = 0;
	while (i < cmd_count)
	{

	}
}
*/
int			main(int argc, char **argv, char **envp)
{
	char		*str;
//	t_cmd		sh;
//	t_list		first;
	char		**evc=NULL;
//	t_cmd		**ar_cmd;
//	t_cmd		*ar_cmd;
//	char		**cmd;
//	int			i;

	str = NULL;
	evc = ft_copy_envp(envp);
	while (1)
	{
		printf("читаю строку\n");
		get_next_line(0, &str);
		//ft_read(&str);
		if (str == NULL)
			return (error_message(PROBLEM_WITH_MALLOC));
		//TODO заменить envp  на w_envp, когда реализуем копирование
		//	printf("before parser str =<%s>\n", str);
		// TODO из парсера вызывается исполнение команд 
		printf("начинаю парсер\n");
		if (ft_parser_shell(evc, str))
		{
			printf("Error with shell\n");
			break ;
		}

		// вызов реализации команды со структурой sh

		//exec_cmd(&first, envp);

		// TODO  кейс: export qwe=1234; echo $qwe
		//  если парсер создат "листы комманд", то надо заново парсить,
		//  для раскрытия - соответсвенно на этапе парсинга не имеет смысла раскрывать? .
		//  надо парсить по  PIPE  кейс: cat | ls
		//  	начнут одновременно но ls закроет stdin, и cat получит 1 строчку
		//  - у каждой команды свой stdin, stdout - это надо прописать
		if (str)
			free(str);
	}
	ft_free_mat(evc);
	//TODO очистка массива sh.array
	if (str)	
		free(str);
	if (argc && argv[0] && envp[0])
		;
	return (0);
}
