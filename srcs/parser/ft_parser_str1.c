/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:30:20 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/30 12:05:46 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_check_condition(char const *s, int *flag, int *i)
{
	if (!(checkbit(*flag, SLASH_2)))
	{
		if (!(checkbit(*flag, SINGLE_Q)) && s[(*i)] == 92)
			*flag = setbit(*flag, SLASH_1);
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

int			ft_is(char const *s, int *flag, int *i)
{
	int		ret;

	ret = 1;
	if (checkbit(*flag, SLASH_2))
		*flag = unsetbit(*flag, SLASH_2);
	if (!checkbit(*flag, SLASH_1))
		ft_check_condition(s, flag, i);
	else
	{
		*flag = unsetbit(*flag, SLASH_1);
		*flag = setbit(*flag, SLASH_2);
		//if (s[*i] != 34 && s[*i] != 39 && s[*i] != 92)
		//	ft_check_condition(s, flag, i);
	}
	return (ret);
}

static void	ft_in_cycle(char **res, char *temp, int *j, size_t len)
{
	char	*t1;

	(*res)[*j] = '\0';
	t1 = *res;
	*res = ft_strjoin_mod(*res, temp, len);
	//printf("%p, %p\n", t1, temp);
	free(t1);
	free(temp);
	*j = ft_strlen(*res);
	return ;
}

static void ft_init_res0(char *str, char **res, int *i, int *j)
{
	*i = 0;
	*j = 0;
	(*res)[ft_strlen(str)] = '\0';
	(*res)[0] = '\0';
	return ;
}

char		*ft_res0(char *str, int *flag, char **envp)
{
	char	*res;
	char	*temp;
	int		i;
	int		j;

	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_init_res0(str, &res, &i, &j);
	while (str[i] != '\0')
	{
		ft_is(str, flag, &i);
		if (((!(checkbit(*flag, SLASH_2)) && (str[i] == 39 || str[i] == 34))))
		{
			//	||(*flag == 0 && str[i] == 92))
			ft_is(str, flag, &i);
		}
		if (str[i] != '\0' && (!(checkbit(*flag, SINGLE_Q)))
				&& (!checkbit(*flag, SLASH_1)) && (!checkbit(*flag, SLASH_2)) && str[i] == '$' && !checkbit(*flag, SLASH_1))
		{
//			temp = ft_dollar(str, &i, flag, envp);
			temp = ft_dollar(str, &i, envp);
			ft_in_cycle(&res, temp, &j, ft_strlen(str));
			i--;
		}
		else if (str[i] != '\0'
				&& ((checkbit(*flag, SLASH_2))
					|| (checkbit(*flag, SLASH_1) && (str[i + 1] =='$' || str[i + 1] == 92 || str[i + 1] == 39 || str[i + 1] == 34))
					|| ((!checkbit(*flag, SLASH_1)) && (!checkbit(*flag, SLASH_2)))))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}


char		*ft_res_arg(char *str, int *flag, char **envp)
{
	char	*res;
	char	*temp;
	int		i;
	int		j;

	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_init_res0(str, &res, &i, &j);
	while (str[i] != '\0')
	{
		ft_is(str, flag, &i);
		if (((!(checkbit(*flag, SLASH_2)) && (str[i] == 39 || str[i] == 34))))
		{
			//	||(*flag == 0 && str[i] == 92))
		//	printf("1\n");
			ft_is(str, flag, &i);
		}
		if (str[i] != '\0' && (!(checkbit(*flag, SINGLE_Q)))
				&& (!checkbit(*flag, SLASH_1)) && (!checkbit(*flag, SLASH_2)) && str[i] == '$') // && !checkbit(*flag, SLASH_1))
		{
	//		temp = ft_dollar(str, &i, flag, envp);
			temp = ft_dollar(str, &i, envp);
			ft_in_cycle(&res, temp, &j, ft_strlen(str));
			i--;
		}
		else if (str[i] != '\0'
				&&  (checkbit(*flag, SINGLE_Q) ||
					checkbit(*flag, SLASH_2) ||
					(checkbit(*flag, DOUBLE_Q) &&
					 (str[i] != 92 || (str[i] == 92 && str[i + 1] != '\0' && str[i + 1] != 34 && str[i + 1] != 92 && str[i + 1] != '$')
					 )) ||
					*flag == 0))
		{
	//		printf("2\n");
			res[j++] = str[i];
		}
	//	TODO если у флага  установлены  биты " ' - выдать ошибку "кавычки не закрыты"
	//	printf("flag =%d\n", *flag);
	//	printf("str=%s\n", &str[i]);
			i++;
	}
	res[j] = '\0';
	return (res);
}

