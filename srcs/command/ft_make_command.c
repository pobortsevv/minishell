/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 07:37:09 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/22 15:57:44 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "stdio.h"

void	ft_make_command(t_cmd *ar_t_cmd, int len)
{
	int		i;
	char	**ar_com;

	i = 0;
	while(i < len)
	{

		//printf(" в парсер строк\n");
		//  обработка t_cmd в массив для отправики в команду
		ar_com = ft_parser_str(ar_t_cmd[i]);
		//  получили:
		//  ar_com[0] - сама команда, если checkbit(ae_cmd[j].PATH) == 1, то команда с путем 
		//  &ar[1] - если ar[1] != NULL массив команд, ограниченный снизу NULL
		//  Тестовая печать ar_com:
		printf("печать - заменить на исполнение ar_cmd[0]- команда -рабочая \n");
		printf("ar_cmd[i]  - в работе, пока только копии из парсера (не обработаны < > и $\n");
		ft_print_array_2(ar_com);
		free(ar_com);
		i++;
	}
	return ;
}
