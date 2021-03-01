/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:41:15 by sabra             #+#    #+#             */
/*   Updated: 2021/01/04 19:04:56 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

void	ft_put_null_u(int len)
{
	while ((len--) > 0)
		ft_putchar_fd('0', 1);
}

int		ft_dot_star_u(unsigned int num, t_struct flgs, int count)
{
	flgs.dot_star -= count;
	if (flgs.dot_star >= 0)
		flgs.width -= flgs.dot_star;
	if (flgs.minus == 1)
	{
		ft_put_null_u(flgs.dot_star);
		if (count != 0 || flgs.dot_star > 0)
			ft_putnbr16_fd(num, 1, "0123456789");
	}
	while (flgs.width > 0)
	{
		ft_putchar_fd(' ', 1);
		flgs.width--;
	}
	if (flgs.minus == 0)
	{
		ft_put_null_u(flgs.dot_star);
		if (count == 0 && flgs.dot_star <= 0)
			return (count > flgs.lenght ? count : flgs.lenght);
		ft_putnbr16_fd(num, 1, "0123456789");
	}
	return (count > flgs.lenght ? count : flgs.lenght);
}

void	ft_null_dot_star_u(t_struct flgs, unsigned int num)
{
	if (flgs.minus == 1)
	{
		ft_putnbr16_fd(num, 1, "0123456789");
		while ((flgs.width)-- > 0)
			ft_putchar_fd(' ', 1);
	}
	else if (flgs.zero == 1)
	{
		ft_put_null_u(flgs.width);
		ft_putnbr16_fd(num, 1, "0123456789");
	}
	else
	{
		while ((flgs.width)-- > 0)
			ft_putchar_fd(' ', 1);
		ft_putnbr16_fd(num, 1, "0123456789");
	}
}

int		ft_u_type(t_struct flgs, va_list args)
{
	int				count;
	unsigned int	num;
	unsigned int	buff;

	count = 0;
	num = va_arg(args, unsigned int);
	buff = num;
	while (buff > 0)
	{
		buff /= 10;
		count++;
	}
	if (num == 0 && flgs.dot_star != 0)
		count = 1;
	flgs.width -= count;
	if (flgs.dot_star != -1)
	{
		count = ft_dot_star_u(num, flgs, count);
		return (count > flgs.lenght ? count : flgs.lenght);
	}
	ft_null_dot_star_u(flgs, num);
	return (count > flgs.lenght ? count : flgs.lenght);
}
