/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr16_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:43:25 by sabra             #+#    #+#             */
/*   Updated: 2021/01/04 18:54:03 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_change_base(unsigned long n, char *base)
{
	char	result;
	int		base_n;

	base_n = ft_strlen(base);
	result = base[n % base_n];
	return (result);
}

void	ft_putnbr16_fd(unsigned long num, int fd, char *base)
{
	unsigned long	n;
	unsigned long	base_n;

	base_n = ft_strlen(base);
	n = num;
	if (n < base_n)
		ft_putchar_fd(ft_change_base(n, base), fd);
	else
	{
		ft_putnbr16_fd(n / base_n, fd, base);
		ft_putnbr16_fd(n % base_n, fd, base);
	}
}
