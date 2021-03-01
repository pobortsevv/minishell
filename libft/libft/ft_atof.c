/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:09:24 by sabra             #+#    #+#             */
/*   Updated: 2021/01/17 13:45:47 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_intlen(int n)
{
	int len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

float	ft_atof(char *str)
{
	int		i;
	int		div;
	int		atoi;
	float	atof;

	i = str[0] == '-' ? 1 : 0;
	atoi = ft_atoi(str);
	atof = 0;
	div = atoi == 0 && i == 1 ? -1 : 1;
	while (ft_space((str[i])))
		i++;
	i += ft_intlen(atoi);
	div *= (atoi < 0 ? -1 : 1);
	if (str[i] != '.')
		return (atoi);
	else
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		div *= 10;
		atof = (atof * 10) + (str[i++] - '0');
	}
	atof /= div;
	return (atoi + atof);
}
