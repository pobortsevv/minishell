/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_str_utilit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 08:44:17 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 09:13:59 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_check_cond_if1(char const *s, int *flag, int *i)
{
	(*i)++;
	*flag = switchbit(*flag, SINGLE_Q);
	if (!checkbit(*flag, SINGLE_Q) && s[*i] == 34)
		*flag = setbit(*flag, DOUBLE_Q);
	if (!checkbit(*flag, SINGLE_Q) && s[*i] == 92)
		*flag = setbit(*flag, SLASH_1);
	return ;
}

void		ft_check_cond_if2(char const *s, int *flag, int *i)
{
	(*i)++;
	*flag = switchbit(*flag, DOUBLE_Q);
	if (!checkbit(*flag, DOUBLE_Q) && (s[*i] == 39))
		*flag = setbit(*flag, SINGLE_Q);
	if (s[*i] == 92)
		*flag = setbit(*flag, SLASH_1);
	return ;
}

void		ft_check_cond_if3(char const *s, int *flag, int *i)
{
	(*i) += 2;
	if (s[*i] == 39 || s[*i] == 34)
		ft_check_condition_sh(s, flag, i);
	return ;
}

static int	t(char *s, int *i)
{
	if (s[(*i) + 1] == ' ')
	{
		while (s[(*i) + 1] == ' ')
			(*i)++;
	}
	return (1);
}

int			ft_chec_str_if(char *str, int i, int flag)
{
	int	ret;

	ret = str[i] != '\0' && !checkbit(flag, SLASH_1) && !checkbit(flag, SLASH_2)
		&& !checkbit(flag, SINGLE_Q) && !checkbit(flag, DOUBLE_Q)
		&& ((str[i] == ';' && t(str, &i) && str[i + 1] == ';')
				|| (str[i] == ';' && t(str, &i) && str[i + 1] == '|')
				|| (str[i] == '|' && t(str, &i) && (str[i + 1] == ';'
						|| str[i + 1] == '\0'))
				|| (str[i] == '|' && t(str, &i) && (str[i + 1] == '|'
						|| str[i + 1] == '\0'))
				|| (str[i] == '>' && t(str, &i) && (str[i + 1] == '<'
						|| str[i + 1] == '\0'))
				|| (str[i] == '<' && t(str, &i) && (str[i + 1] == '>'
						|| str[i + 1] == '\0'))
				|| (str[i] == '<' && t(str, &i) && (str[i + 1] == '<'
						|| str[i + 1] == '\0'))
				|| (str[i] == '>' && str[i + 1] == '>' && t(str, &i)
					&& (str[i + 2] == '>' || str[i + 2] == '<'
						|| str[i + 1] == '\0')));
	return (ret);
}
