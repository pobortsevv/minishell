/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:25:59 by sabra             #+#    #+#             */
/*   Updated: 2021/01/04 19:02:44 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

void		ft_s_with_minus(t_struct flgs, const char *str)
{
	if (flgs.dot_star > 0)
	{
		while ((flgs.dot_star)-- > 0 && *str)
		{
			ft_putchar_fd(*str, 1);
			str++;
		}
	}
	else if (flgs.dot_star < 0)
		ft_putstr_fd(str, 1);
}

int			ft_s_null_minus(t_struct flgs, int count, const char *str)
{
	if (flgs.zero == 1)
	{
		while ((flgs.width)-- > 0)
			ft_putchar_fd('0', 1);
	}
	while ((flgs.width)-- > 0)
		ft_putchar_fd(' ', 1);
	if (flgs.minus == 0)
	{
		if (flgs.dot_star < (int)ft_strlen(str) && flgs.dot_star > 0)
		{
			while ((flgs.dot_star)-- > 0)
			{
				ft_putchar_fd(*str, 1);
				str++;
			}
			return (count);
		}
		else if (flgs.dot_star != 0)
			ft_putstr_fd(str, 1);
	}
	return (count);
}

int			ft_s_type(t_struct flgs, va_list args)
{
	const char	*str;
	int			count;

	str = va_arg(args, const char *);
	if (str == NULL)
		str = "(null)";
	if (flgs.dot_star > 0 && flgs.dot_star < (int)ft_strlen(str))
		count = flgs.dot_star;
	else
		count = (int)ft_strlen(str);
	if (flgs.dot_star == 0)
	{
		count = flgs.width;
		while ((flgs.width)-- > 0)
			ft_putchar_fd(' ', 1);
		return (count);
	}
	flgs.width -= count;
	if (flgs.minus == 1)
	{
		ft_s_with_minus(flgs, str);
	}
	count = (flgs.width > 0 ? count + flgs.width : count);
	count = ft_s_null_minus(flgs, count, str);
	return (count);
}

int			ft_c_type(t_struct flgs, va_list args, int count)
{
	count = (flgs.width >= 1 ? flgs.width : 1);
	if (flgs.minus == 1)
	{
		if (flgs.type == 'c')
			ft_putchar_fd(va_arg(args, int), 1);
		else
			ft_putchar_fd('%', 1);
	}
	if (flgs.type == '%' && flgs.zero == 1)
		while ((flgs.width)-- > 1)
			ft_putchar_fd('0', 1);
	else
	{
		while ((flgs.width)-- > 1)
			ft_putchar_fd(' ', 1);
	}
	if (flgs.minus == 0)
	{
		if (flgs.type == 'c')
			ft_putchar_fd(va_arg(args, int), 1);
		else
			ft_putchar_fd('%', 1);
	}
	return (count);
}
