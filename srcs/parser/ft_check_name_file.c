/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_name_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:32:59 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 08:26:46 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_pars_name(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		f;

	res = NULL;
	i = 0;
	j = 0;
	f = 0;
	f = checkbit(f, SINGLE_Q);
	if (str != NULL)
		res = ft_res_arg(str, &f, NULL);
	return (res);
}
