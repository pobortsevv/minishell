/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str1_utilit1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 09:52:23 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 11:08:03 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_res0_if(char *str, int *flag, t_word *w)
{
	int	ret;

	ret = str[w->i] != '\0' && (!(checkbit(*flag, SINGLE_Q)))
				&& (!checkbit(*flag, SLASH_1)) && (!checkbit(*flag, SLASH_2))
				&& str[w->i] == '$' && !checkbit(*flag, SLASH_1);
	return (ret);
}

int		ft_res0_if1(char *str, int *flag, t_word *w)
{
	int	ret;

	ret = str[w->i] != '\0' && ((checkbit(*flag, SLASH_2))
			|| (checkbit(*flag, SLASH_1) && (str[w->i + 1] == '$'
					|| str[w->i + 1] == 92 || str[w->i + 1] == 39
					|| str[w->i + 1] == 34))
			|| ((!checkbit(*flag, SLASH_1))
				&& (!checkbit(*flag, SLASH_2))));
	return (ret);
}

void	ft_res0_part1(char **res, t_word *w)
{
	while (w->d >= 2 && ((*res)[w->d - 1] == 34 || (*res)[w->d - 1] == 39)
			&& (*res)[w->d - 2] != 92)
	{
		(*res)[w->d] = '\0';
		(w->d)--;
	}
	return ;
}

void	ft_res0_part0(char *str, t_word *w, char **envp, char **res)
{
	char	*temp;

	temp = ft_dollar(str, &(w->i), envp);
	ft_in_cycle(res, temp, &(w->d), ft_strlen(str));
	(w->i)--;
	return ;
}
