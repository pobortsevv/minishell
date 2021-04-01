/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:10:12 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/01 09:24:52 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"


static void	ft_check_condition_sh(char const *s, int *flag, int *i)
{
	if (checkbit(*flag, SLASH_2))
		*flag = unsetbit(*flag, SLASH_2);
//	if (!(checkbit(*flag, SLASH_2)))
	{
		if (!(checkbit(*flag, SINGLE_Q)) && s[(*i)] == 92)
		{
	//		(*i)++;
			*flag = setbit(*flag, SLASH_1);
		}
		else if (!(checkbit(*flag, DOUBLE_Q)) && s[*i] == 39 && s[(*i) + 1] != 39)
		{
			(*i)++;
			*flag = switchbit(*flag, SINGLE_Q);
			if (!checkbit(*flag, SINGLE_Q) && s[*i] == 34)
				*flag = setbit(*flag, DOUBLE_Q);
			if (!checkbit(*flag, SINGLE_Q) && s[*i] == 92)
				*flag = setbit(*flag, SLASH_1);
		}
		else if (!(checkbit(*flag, DOUBLE_Q))
				&& s[*i] == 39 && s[(*i) + 1] == 39)
		{
			(*i) += 2;
			if (s[*i] == 39 || s[*i] == 34)
				ft_check_condition_sh(s, flag, i);
		}
		else if (!(checkbit(*flag, SINGLE_Q))
				&& (s[*i] == '"' && s[(*i) + 1] != '"'))
		{
			(*i)++;
			*flag = switchbit(*flag, DOUBLE_Q);
			if (!checkbit(*flag, DOUBLE_Q) && (s[*i] == 39))
			{
				*flag = setbit(*flag, SINGLE_Q);
			//	i++;
			}
			if (s[*i] == 92)
				*flag = setbit(*flag, SLASH_1);
		}
		else if (!(checkbit(*flag, SINGLE_Q))
				&& (s[*i] == '"' && s[(*i) + 1] == '"'))
		{
			(*i) += 2;
			if (s[*i] == 39 || s[*i] == 34)
				ft_check_condition_sh(s, flag, i);
		}
	}
//	else if (checkbit(*flag, SLASH_2))
//		*flag = unsetbit(*flag, SLASH_2);
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

static int	t(char *s, int *i)
{
	if (s[(*i) + 1] == ' ')
	{
		while (s[(*i) + 1] == ' ')
			(*i)++;
	}
	return (1);
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
			break;
		if (str[i] != '\0' &&
				!checkbit(flag, SLASH_1) &&
				!checkbit(flag, SLASH_2) &&
				!checkbit(flag, SINGLE_Q) &&
				!checkbit(flag, DOUBLE_Q) &&
				((str[i] == ';' && t(str, &i) && str[i + 1] == ';')
				 || (str[i] == ';' && t(str, &i) && str[i +1] =='|')
				 || (str[i] == '|' && t(str, &i) && (str[i + 1] == ';' || str[i + 1] == '\0'))
				 || (str[i] == '|' && t(str, &i) && (str[i + 1] == '|' || str[i + 1] == '\0'))
				 || (str[i] == '>' && t(str, &i) && (str[i + 1] == '<' || str[i + 1] == '\0'))
				 || (str[i] == '<' && t(str, &i) && (str[i + 1] == '>' || str[i + 1] == '\0'))
				 || (str[i] == '<' && t(str, &i) && (str[i + 1] == '<' || str[i + 1] == '\0'))
				 || (str[i] == '>' && str[i + 1] == '>' && t(str, &i) &&
					 (str[i + 2] == '>' || str[i + 2] == '<' || str[i + 1] == '\0'))))
			return (258);
//		printf("<%s>\n",  &str[i]);
//		printf("^^SLASH1%zu\n", checkbit(flag, SLASH_1));
//		printf("^^SLASH2%zu\n", checkbit(flag, SLASH_2));
//		printf("^^S%zu\n", checkbit(flag, SINGLE_Q));
//		printf("^^D%zu\n", checkbit(flag, DOUBLE_Q));
		i++;
	}
	if (checkbit(flag, SINGLE_Q) || checkbit(flag, DOUBLE_Q))
			return(-1);
	return (0);   // все ОК
}
