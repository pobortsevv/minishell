/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_parser_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:07:24 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/12 15:20:27 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include  <stdio.h>

t_cmd  		*ft_new_parser_cmd(char *cmd)
{
	char	**cmd_pipe;
//	t_cmd	*res;
	char	**arg_pipe;
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
	
	while (i<len)
	{
		arg_pipe = ft_split_arg(cmd_pipe[i], SYM);
		free(arg_pipe);
		i++;
	}

//	while (!(checkbit(res[i].id, END_ARRAY)))
//	while (i<len)
//	{
//		int j=0;
//		while (res[i].args[j] != NULL)
//		{
//			printf("WWWWW reis[%d].args[%d]\n = %s\n",i, j, res[i].args[j]);
//			j++;
	//		read(0, 0, 1);
//		}
//		i++;
//	}
//	printf("проверка разбивка pipe\n");
//	ft_print_array_2(cmd_pipe);
	return 0;
}
