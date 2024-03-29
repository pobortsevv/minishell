/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:08:05 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/16 11:05:47 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_lenarray(char **cmd)
{
	int		res;

	res = 0;
	while (cmd && cmd[res] != 0)
		res++;
	return (res);
}
