/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:35:33 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 13:32:56 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

void		ft_print_array_3(char ***ar)
{
	int		i;
	int		j;

	i = 0;
	while (ar[i] != NULL)
	{
		j = 0;
		while (ar[i][j] != NULL)
		{
			printf("array[%d][%d]=%s\n", i, j, ar[i][j]);
			j++;
		}
		i++;
	}
	return ;
}

void		ft_m_test_pr(t_list *first)
{
	t_list	*t;
	t_cmd	*ex;
	int		i;

	t = first;
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

void		ft_print_array_2(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s \n", arr[i]);
		i++;
	}
	return ;
}

void		ft_print_array_t_cmd(t_cmd *ar_t_cmd, int len)
{
	int		u;
	int		j;

	u = 0;
	printf("печать результата - массива t_cmd\n");
	while (u < len)
	{
		j = 0;
		printf("len=%d\n", ar_t_cmd[u].len_args);
		while (ar_t_cmd[u].args[j] != NULL)
		{
			if (ar_t_cmd[u].args[j] != NULL)
				printf("ar_cmd[%d].args[%d]\n = <%s>\n", u, j,
						ar_t_cmd[u].args[j]);
			j++;
		}
		printf("ar_cmd[%d].in=%d\n", u, ar_t_cmd[u].in);
		printf("ar_cmd[%d].out=%d\n", u, ar_t_cmd[u].out);
		u++;
	}
	printf("массив напечатан\n");
	return ;
}
