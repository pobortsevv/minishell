/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:30:20 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 11:48:52 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			ft_is(char const *s, int *flag, int *i)
{
	int		ret;

	ret = 1;
	if (!checkbit(*flag, SLASH_1))
		ft_check_condition(s, flag, i);
	else
	{
		*flag = unsetbit(*flag, SLASH_1);
		*flag = setbit(*flag, SLASH_2);
	}
	return (ret);
}

void		ft_in_cycle(char **res, char *temp, int *j, size_t len)
{
	char	*t1;

	(*res)[*j] = '\0';
	t1 = *res;
	*res = ft_strjoin_mod(*res, temp, len);
	free(t1);
	free(temp);
	*j = ft_strlen(*res);
	return ;
}

static void	ft_init_res0(char *str, char **res, int *i, int *j)
{
	int		len;
	int		k;

	*i = 0;
	*j = 0;
	k = 0;
	len = ft_strlen(str);
	while (k <= len)
	{
		(*res)[k] = '\0';
		k++;
	}
	return ;
}

char		*ft_res0(char *str, int *flag, char **envp)
{
	char	*res;
	t_word	w;

	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_init_res0(str, &res, &(w.i), &(w.d));
	while (str[w.i] != '\0')
	{
		ft_is(str, flag, &(w.i));
		if (!(checkbit(*flag, SLASH_2)) && (str[w.i] == 39 || str[w.i] == 34))
		{
			ft_is(str, flag, &(w.i));
			if (str[w.i] == '\0')
				break ;
		}
		if (str[w.i] != '\0' && ft_res0_if(str, flag, &w))
			ft_res0_part0(str, &w, envp, &res);
		else if (str[w.i] != '\0' && ft_res0_if1(str, flag, &w))
			res[(w.d)++] = str[w.i];
		if (str[w.i] != '\0')
			(w.i)++;
	}
	res[w.d] = '\0';
	res = ft_res_arg(str, flag, envp);
	ft_res0_part1(&res, &w);
	return (res);
}

char		*ft_res_arg(char *str, int *flag, char **envp)
{
	char	*res;
	t_word	w;

	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_init_res0(str, &res, &(w.i), &(w.d));
	while (str[w.i] != '\0')
	{
		ft_is(str, flag, &(w.i));
		if (str[w.i] != '\0' && ft_res_arg_if0(str, w.i, flag))
		{
			ft_is(str, flag, &(w.i));
			if (str[w.i] == '\0')
				break ;
		}
		if (str[w.i] != '\0' && ft_res_arg_if1(str, w.i, flag))
			ft_res_arg_part1(str, envp, &w, &res);
		else if (str[w.i] != '\0' && ft_res_arg_if2(str, w.i, flag))
			res[(w.d)++] = str[w.i];
		if (str[w.i] != '\0')
			(w.i)++;
	}
	res[w.d] = '\0';
	return (res);
}
