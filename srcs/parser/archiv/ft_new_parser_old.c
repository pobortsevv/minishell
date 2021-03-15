/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 12:43:34 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/12 08:36:58 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include  <stdio.h>

t_cmd  		**ft_parser_cmd(char **w_envp, char *str)
{
	char	**cmd;
	char	**cmd_pipe;
	t_cmd	**ar_cmd;
	int		len;
	int 	i;
	char 	*test;

	i = 0;
	ar_cmd = NULL;
	cmd = ft_split_cmd(str, ';'); // массив команд,  строка разбита по ;
//	printf("result ; :\n");
//	ft_print_array_2(cmd);

	//найти длину массива cmd
	len = ft_lenarray(cmd);
//	printf("len =%d\n", len);
	ar_cmd = (t_cmd **)malloc(sizeof(t_cmd *) * len + 1);
	test = (char *)malloc(3);
	test[0] = 'g';
	ar_cmd[len] = NULL;
	//создать массив длиной cmd, для массива массивов  t_cmd
	//заполнить массив
	//передать массив в main 
	i = 0;
	while (cmd[i] != NULL)
	{
		cmd_pipe = ft_split_cmd(cmd[i], '|');
	//	printf("result pipe:\n");
	//	ft_print_array_2(cmd_pipe);
		printf("проверка в ft_parser_cmd\n");
		printf("len = %zu\n", ft_strlen(cmd_pipe[i])); 
		ar_cmd[i] = ft_make_2_array_t_cmd(cmd_pipe);
		if (ar_cmd[i] == NULL)
			printf("%d  = NULL", i);
		printf("FGFH\n");
		printf("@@@@%s\n", ar_cmd[0][0].args[0]);
	//	printf("%s\n", ar_cmd[i][f].args[j]);
		/*
		int f = 0;
		while (!(checkbit(ar_cmd[i][f].id, END_ARRAY)))
		{
			int	j=0;
			while (ar_cmd[i][f].args[j] != NULL)
			{
				printf("ar_cmd[%d][%d].args[%d]\n = %s\n",i, f, j, ar_cmd[i][f].args[j]);
				j++;
				read(0, 0, 1);
			}
			f++;
		}
		*/
		i++;
	}
	printf("нулевой в парсере:\n");
	printf("%s\n", ar_cmd[0][0].args[0]);
	/*
	i=0;
	printf("пеечатаю массив \n");
	while (ar_cmd[i] != NULL)
	{
		int f = 0;
		while (!(checkbit(ar_cmd[i][f].id, END_ARRAY)))
		{
			int	j=0;
			while (ar_cmd[i][f].args[j] != NULL)
			{
				printf("ar_cmd[%d][%d].args[%d]\n = %s\n",i, f, j, ar_cmd[i][f].args[j]);
				j++;
				read(0, 0, 1);
			}
			f++;
		}
		i++;
	}
*/
	(void)(w_envp);
	return (ar_cmd);
}
