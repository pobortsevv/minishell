/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 12:43:34 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/12 12:37:59 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include  <stdio.h>

t_cmd  		**ft_parser_cmd(char **w_envp, char *str)
{
	char	**cmd;
//	char	**cmd_pipe;
	t_cmd	**ar_cmd;
	int		len;
	int 	i;
	char 	*test;
	char	***test_cmd_pipe;
	char	****test_ar_cmd;

	i = 0;
	ar_cmd = NULL;
	cmd = ft_split_cmd(str, ';'); // массив команд,  строка разбита по ;
//	printf("result ; :\n");
//	ft_print_array_2(cmd);

	//найти длину массива cmd
	len = ft_lenarray(cmd);
//	printf("len =%d\n", len);
//
//	TEST
//
	test_cmd_pipe = (char ***)malloc(sizeof(char **) * len + 1);
	test_cmd_pipe[len] = NULL;
	i = 0;
	while (i < len)
	{
		test_cmd_pipe[i]=ft_split_cmd(cmd[i], '|');
		printf("#######result pipe:\n");
		ft_print_array_2(test_cmd_pipe[i]);
		printf("#######проверка в ft_parser_cmd\n");
		i++;
	}
	test_ar_cmd = (char ****)malloc(sizeof(char ***)*len + 1);
	test_ar_cmd[len] = NULL;


	ar_cmd = (t_cmd **)malloc(sizeof(t_cmd *) * len + 1);
	test = (char *)malloc(3);
//	test[0] = 'g';
	ar_cmd[len] = NULL;
	//создать массив длиной cmd, для массива массивов  t_cmd
	//заполнить массив
	//передать массив в main 
	i = 0;
	while (cmd[i] != NULL)
	{
	//	cmd_pipe = ft_split_cmd(cmd[i], '|');
	//	printf("result pipe:\n");
	//	ft_print_array_2(cmd_pipe);
	//	printf("проверка в ft_parser_cmd\n");
	//	printf("len = %zu\n", ft_strlen(cmd_pipe[i])); 
	//	ar_cmd[i] = ft_make_2_array_t_cmd(test_cmd_pipe);
		//
		//здесь через t_cmd
		//
	//	ar_cmd[i] = ft_make_2_array_t_cmd(test_cmd_pipe[i]);
	//	if (ar_cmd[i] == NULL)
	//		printf("%d  = NULL", i);
	//	printf("FGFH\n");
	
		test_ar_cmd[i] = ft_make_array_cmd(test_cmd_pipe[i]);

		//	printf("@@@@%s\n", ar_cmd[0][0].args[0]);
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
	int i1 = 0;
	int	j1 = 0;
	int	z1 = 0;
	while (test_ar_cmd[i1] != NULL)
	{
		j1= 0;
		while(test_ar_cmd[i1][j1] != NULL)
		{
			z1=0;
			while (test_ar_cmd[i1][j1][z1] != NULL)
			{
				printf("%s\n", test_ar_cmd[i1][j1][z1]);
				z1++;
			}
			j1++;
		}
		i1++;
	}
//	printf("нулевой в парсере:\n");
//	printf("%s\n", ar_cmd[0][0].args[0]);
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
