/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str1_utilit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 09:28:27 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 09:44:11 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_ch_con_if0(char const *s, int *flag, int *i)
{
	(*i)++;
	*flag = switchbit(*flag, SINGLE_Q);
	if (!checkbit(*flag, SINGLE_Q) && s[*i] == 34)
	{
		(*i)++;
		*flag = setbit(*flag, DOUBLE_Q);
	}
	if (!checkbit(*flag, SINGLE_Q) && s[*i] == 92)
		*flag = setbit(*flag, SLASH_1);
	return ;
}

static void	ft_ch_con_if1(char const *s, int *flag, int *i)
{
	(*i)++;
	*flag = switchbit(*flag, DOUBLE_Q);
	if (!checkbit(*flag, DOUBLE_Q) && s[*i] == 39)
	{
		*flag = setbit(*flag, SINGLE_Q);
		(*i)++;
	}
	if (s[*i] == 92)
		*flag = setbit(*flag, SLASH_1);
	return ;
}

static void	ft_ch_con_if2(char const *s, int *flag, int *i)
{
	(*i) += 2;
	if (s[*i] == 39 || s[*i] == 34)
		ft_check_condition(s, flag, i);
	return ;
}

void		ft_check_condition(char const *s, int *flag, int *i)
{
	if (checkbit(*flag, SLASH_2))
		*flag = unsetbit(*flag, SLASH_2);
	{
		if (!(checkbit(*flag, SINGLE_Q)) && s[(*i)] == 92)
			*flag = setbit(*flag, SLASH_1);
		else if (!(checkbit(*flag, DOUBLE_Q)) && s[*i] == 39
				&& s[(*i) + 1] != 39)
			ft_ch_con_if0(s, flag, i);
		else if (!(checkbit(*flag, DOUBLE_Q))
				&& s[*i] == 39 && s[(*i) + 1] == 39)
		{
			(*i) += 2;
			if (s[*i] == 39 || s[*i] == 34)
				ft_check_condition(s, flag, i);
		}
		else if (!(checkbit(*flag, SINGLE_Q))
				&& (s[*i] == '"' && s[(*i) + 1] != '"'))
			ft_ch_con_if1(s, flag, i);
		else if (!(checkbit(*flag, SINGLE_Q))
				&& (s[*i] == '"' && s[(*i) + 1] == '"'))
			ft_ch_con_if2(s, flag, i);
	}
	return ;
}
