/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_parser_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:07:24 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/15 11:33:47 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include  <stdio.h>

void	free_array_shell(char **ar)
{
	int		i;

	i = 0;
	if (ar != NULL)
	{
		while (ar[i] != NULL)
		{
			free(ar[i]);
			ar[i] = NULL;
			i++;
		}
		free(ar);
		ar= NULL;
	}
	return ;
}

void	free_array_shell_2(char ***ar)
{
	int		i;

	i = 0;
	if (ar != NULL)
	{
		while (ar[i] != NULL)
		{
			free_array_shell(ar[i]);
			//ar[i] = NULL;
			i++;
		}
		free(ar);
		ar= NULL;
	}
	return ;
}

t_cmd  		*ft_new_parser_cmd(char *cmd)
{

	char	**cmd_pipe;
//	t_cmd	*res;
	char	***arg_pipe;
	int		i;
	int		len;

	i = 0;
	cmd_pipe=ft_split_cmd(cmd, '|');
//	printf("проверка разбивка pipe\n");
//	ft_print_array_2(cmd_pipe); //  проверила - все ок
//	res = ft_make_array_t_cmd(cmd_pipe);
//	printf("проверка выдачи:\n");
 	i =0;
	len = ft_lenarray(cmd_pipe);
	printf("len cmd_pipe=%d \n", len);
	arg_pipe = (char ***)malloc(sizeof(char**) * len + 1);
	arg_pipe[len] = NULL;
	while (i<len)
	{
		arg_pipe[i] = ft_split_arg(cmd_pipe[i], SYM);
		int k = 0;
		printf("result разбивки по аргументам: \n");
		while (arg_pipe[i][k] != NULL)
		{
			printf("%s\n", arg_pipe[i][k]);
			k++;
		}
		i++;
	}
	free_array_shell(cmd_pipe);
	free_array_shell_2(arg_pipe);
	return 0;
}

int		ft_parser_shell(char **envp, char *str)
{
	char	**cmd;
	t_cmd	*ar_t_cmd;
	int		i;

	i = 0;
	cmd = ft_split_cmd(str, ';');
	while (cmd[i] != NULL)
	{
		ar_t_cmd = ft_new_parser_cmd(cmd[i]); 
		i++;
		//TODO  вызов функций для выполнения массива t_cmd
		// а пока печать массива t_cmd
		//TODO очистиить массив arg_pipe, на него ссылается массив ar_t_cmd, то есть список аргументов  
	}
	free_array_shell(cmd);
	//TODO убрать эту проверку
	if (envp != NULL)
		printf("OK");
	
	return (0);
}

