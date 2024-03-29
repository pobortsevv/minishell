/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:10:12 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 09:11:40 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_check_condition_sh(char const *s, int *flag, int *i)
{
	if (checkbit(*flag, SLASH_2))
		*flag = unsetbit(*flag, SLASH_2);
	{
		if (!(checkbit(*flag, SINGLE_Q)) && s[(*i)] == 92)
			*flag = setbit(*flag, SLASH_1);
		else if (!(checkbit(*flag, DOUBLE_Q)) && s[*i] == 39
				&& s[(*i) + 1] != 39)
			ft_check_cond_if1(s, flag, i);
		else if (!(checkbit(*flag, DOUBLE_Q))
				&& s[*i] == 39 && s[(*i) + 1] == 39)
		{
			(*i) += 2;
			if (s[*i] == 39 || s[*i] == 34)
				ft_check_condition_sh(s, flag, i);
		}
		else if (!(checkbit(*flag, SINGLE_Q))
				&& (s[*i] == '"' && s[(*i) + 1] != '"'))
			ft_check_cond_if2(s, flag, i);
		else if (!(checkbit(*flag, SINGLE_Q))
				&& (s[*i] == '"' && s[(*i) + 1] == '"'))
			ft_check_cond_if3(s, flag, i);
	}
	return ;
}

static int	ft_is_check(char const *s, int *flag, int *i)
{
	int		ret;

	ret = 1;
	if (!checkbit(*flag, SLASH_1))
		ft_check_condition_sh(s, flag, i);
	else
	{
		*flag = unsetbit(*flag, SLASH_1);
		*flag = setbit(*flag, SLASH_2);
	}
	return (ret);
}

static int	t1(char *s, int *i)
{
	if (s[(*i)] == ' ')
	{
		while (s[(*i)] == ' ')
			(*i)++;
	}
	return (1);
}

int			ft_check_str(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (str && t1(str, &i) && (str[i] == ';' || str[i] == '|'))
		return (258);
	while (str && str[i] != '\0')
	{
		ft_is_check(str, &flag, &i);
		if (str[i] == '\0')
			break ;
		if (ft_chec_str_if(str, i, flag))
			return (258);
		i++;
	}
	if (checkbit(flag, SINGLE_Q) || checkbit(flag, DOUBLE_Q))
		return (-1);
	return (0);
}
