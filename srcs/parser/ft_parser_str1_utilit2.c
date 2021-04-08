/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str1_utilit2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:08:19 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 11:47:58 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_res_arg_if0(char *str, int i, int *flag)
{
	int	ret;

	ret = (!(checkbit(*flag, SLASH_2))) && (!(checkbit(*flag, SLASH_1)))
							&& (str[i] == 39 || str[i] == 34);
	return (ret);
}

int		ft_res_arg_if1(char *str, int i, int *flag)
{
	int	ret;

	ret = str[i] != '\0' && (!(checkbit(*flag, SINGLE_Q)))
		&& (!checkbit(*flag, SLASH_1))
		&& (!checkbit(*flag, SLASH_2)) && str[i] == '$';
	return (ret);
}

int		ft_res_arg_if2(char *str, int i, int *flag)
{
	int	ret;

	ret = str[i] != '\0' && (checkbit(*flag, SINGLE_Q) ||
			checkbit(*flag, SLASH_2) || (checkbit(*flag, DOUBLE_Q)
				&& (str[i] != 92 || (str[i] == 92 && str[i + 1] != '\0'
						&& str[i + 1] != 34
						&& str[i + 1] != 92
						&& str[i + 1] != '$'))) || *flag == 0);
	return (ret);
}

void	ft_res_arg_part1(char *str, char **envp, t_word *w, char **res)
{
	char	*temp;

	temp = ft_dollar(str, &(w->i), envp);
	ft_in_cycle(res, temp, &(w->d), ft_strlen(str));
	(w->i)--;
	return ;
}
