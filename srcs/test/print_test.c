/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:35:33 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/10 16:00:15 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

// тест-функция: печать из "списка команд"

void		ft_m_test_pr(t_list *first)
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

// тест-функция: печать из двухмерного массива строк, ограниченного NULL

void	ft_print_array_2(char ** arr)
{
	int		i;

	i = 0;
	while(arr[i] != NULL)
	{
		printf("%s \n",arr[i]);
		i++;
	}
	return ;
}
