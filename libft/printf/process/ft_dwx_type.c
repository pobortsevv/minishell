/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dwx_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:05:02 by sabra             #+#    #+#             */
/*   Updated: 2021/01/04 19:03:39 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

void	ft_put_null_dwx(int len)
{
	while (len-- > 0)
		ft_putchar_fd('0', 1);
}

int		ft_dot_star_dwx(unsigned int num, t_struct flgs, int count)
{
	flgs.dot_star -= count;
	if (flgs.dot_star >= 0)
		flgs.width -= flgs.dot_star;
	if (flgs.minus == 1)
	{
		ft_put_null_dwx(flgs.dot_star);
		if (count != 0 || flgs.dot_star > 0)
			ft_putnbr16_fd(num, 1, "0123456789abcdef");
	}
	while ((flgs.width)-- > 0)
		ft_putchar_fd(' ', 1);
	if (flgs.minus == 0)
	{
		ft_put_null_dwx(flgs.dot_star);
		if (count == 0 && flgs.dot_star <= 0)
			return (count > flgs.lenght ? count : flgs.lenght);
		ft_putnbr16_fd(num, 1, "0123456789abcdef");
	}
	return (count > flgs.lenght ? count : flgs.lenght);
}

void	ft_null_dot_star_dwx(t_struct flgs, unsigned int num)
{
	if (flgs.minus == 1)
	{
		ft_putnbr16_fd(num, 1, "0123456789abcdef");
		while ((flgs.width)-- > 0)
			ft_putchar_fd(' ', 1);
	}
	else if (flgs.zero == 1)
	{
		ft_put_null_dwx(flgs.width);
		ft_putnbr16_fd(num, 1, "0123456789abcdef");
	}
	else
	{
		while ((flgs.width)-- > 0)
			ft_putchar_fd(' ', 1);
		ft_putnbr16_fd(num, 1, "0123456789abcdef");
	}
}

int		ft_dwx_type(t_struct flgs, va_list args)
{
	int				count;
	unsigned int	num;
	unsigned int	buff;

	count = 0;
	num = va_arg(args, unsigned int);
	buff = num;
	while (buff > 0)
	{
		buff /= 16;
		count++;
	}
	if (num == 0 && flgs.dot_star != 0)
		count = 1;
	flgs.width -= count;
	if (flgs.dot_star > -1)
	{
		count = ft_dot_star_dwx(num, flgs, count);
		return (count);
	}
	ft_null_dot_star_dwx(flgs, num);
	return (count > flgs.lenght ? count : flgs.lenght);
}
