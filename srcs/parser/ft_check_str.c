/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:10:12 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/29 16:12:43 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"


static void	ft_check_condition_sh(char const *s, int *flag, int *i)
{
	if (!(checkbit(*flag, SLASH_2)))
	{
		if (!(checkbit(*flag, SINGLE_Q)) && s[(*i)] == 92)
		{
			(*i)++;
			*flag = setbit(*flag, SLASH_1);
		}
		else if (!(checkbit(*flag, DOUBLE_Q)) && s[*i] == 39 && s[(*i) + 1] != 39)
		{
			(*i)++;
			*flag = switchbit(*flag, SINGLE_Q);
		}
		else if (!(checkbit(*flag, DOUBLE_Q)) && s[*i] == 39 && s[(*i) + 1] == 39)
			(*i) += 2;
		else if (!(checkbit(*flag, SINGLE_Q))
				&& (s[*i] == '"' && s[(*i) + 1] != '"'))
		{
			(*i)++;
			*flag = switchbit(*flag, DOUBLE_Q);
			if (s[*i] == 92)
				*flag = setbit(*flag, SLASH_1);
		}
		else if (!(checkbit(*flag, SINGLE_Q))
				&& (s[*i] == '"' && s[(*i) + 1] == '"'))
			(*i) += 2;

	}
	else if (checkbit(*flag, SLASH_2))
		*flag = unsetbit(*flag, SLASH_2);
	return ;
}

static int	ft_is_check(char const *s, int *flag, int *i)
{
	int		ret;

	ret = 1;
	if (checkbit(*flag, SLASH_2))
		*flag = unsetbit(*flag, SLASH_2);
	if (!checkbit(*flag, SLASH_1))
		ft_check_condition_sh(s, flag, i);
	else
	{
		*flag = unsetbit(*flag, SLASH_1);
		*flag = setbit(*flag, SLASH_2);
		//if (s[*i] != 34 && s[*i] != 39 && s[*i] != 92)
		//	ft_check_condition(s, flag, i);
	}
	return (ret);
}



int		ft_check_str(char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (str && str[i] != '\0')
	{
		ft_is_check(str, &flag, &i);
		if (!checkbit(flag, SLASH_1) && 
				!checkbit(flag, SLASH_2) &&
				!checkbit(flag, SINGLE_Q) &&
				!checkbit(flag, DOUBLE_Q) &&
				((str[i] == ';' && str[i + 1] == ';')
				 || (str[i] == '|' && str[i + 1] == '|')
				 || (str[i] == '>' && str[i + 1] == '<')
				 || (str[i] == '<' && str[i + 1] == '>')
				 || (str[i] == '<' && str[i + 1] == '<')
				 || (str[i] == '>' && str[i + 1] == '>' && 
					 ((str[i + 2] = '>') || str[i + 2] == '<'))))
			return (258);
		i++;
	}
	if (checkbit(flag, SINGLE_Q) || checkbit(flag, DOUBLE_Q))
			return(-1);
	return (0);   // все ОК
}
