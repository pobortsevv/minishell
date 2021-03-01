/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 09:41:12 by sabra             #+#    #+#             */
/*   Updated: 2021/01/04 19:01:32 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

t_struct	ft_minus_init(t_struct flgs)
{
	flgs.minus = 1;
	flgs.zero = 0;
	return (flgs);
}

t_struct	ft_width_init(const char *str, t_struct flgs, int i, va_list args)
{
	if (ft_isdigit(str[i]) && flgs.width == 0)
		flgs.width = ft_atoi(&str[i]);
	else if (str[i] == '*')
	{
		flgs.width = va_arg(args, int);
		if (flgs.width < 0)
		{
			flgs.width *= -1;
			flgs = ft_minus_init(flgs);
		}
	}
	return (flgs);
}

t_struct	ft_dot_star_init(const char *str, t_struct flgs, int i,
								va_list args)
{
	if (ft_isdigit(str[++i]) && flgs.dot_star == -1)
		flgs.dot_star = ft_atoi(&str[i]);
	else if (str[i] == '*')
		flgs.dot_star = va_arg(args, int);
	else
		flgs.dot_star = 0;
	return (flgs);
}
