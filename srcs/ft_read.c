/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:14:07 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/02 13:40:19 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "../libft/libft/libft.h"

void	ft_read(char **str)
{
	char	c[2];
	int		length;
	char	*temp;

	c[1] = '\0';
	length = 1;
	*str = (char*)malloc(1);
	*str[0] = '\0';
	write(1, "minishell> ", 11);
	while (length > 0)
	{
		length=read(0, &c[0], 1);
		if (c[0] == 10 || length < 1)
			break;
		temp = *str;
		*str = ft_strjoin(*str, c);
	   	free(temp);
	}	
	return ;
}
