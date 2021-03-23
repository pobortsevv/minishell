/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arg_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 07:06:47 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/17 09:16:03 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_check_d(const char *s, int *d, int *flag, int *i)
{
	*i = 0;
	*flag = 0;
	*d = 0;
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		*d = 2;
	else if (s[0] == '>' || s[0] == '<')
		*d = 1;
	if (*d)
		*flag = setbit(*flag, TAIL);
	return ;
}

void		ft_check_d_less(const char s, char *c, int *d, int *flag)
{
	if (*d > 0)
		(*d)--;
	if (!(ft_strchr(c, s)) && checkbit(*flag, TAIL))
		*flag = unsetbit(*flag, TAIL);
	return ;
}

int			ft_check_tail(int flag)
{
	int		ret;

	ret = (checkbit(flag, SINGLE_Q) || checkbit(flag, TAIL) ||
			checkbit(flag, DOUBLE_Q) || checkbit(flag, SLASH_2));
	return (ret);
}
