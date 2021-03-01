/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 23:00:15 by sabra             #+#    #+#             */
/*   Updated: 2020/11/08 18:59:55 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_num_len(long int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		len++;
	if (n != 0)
	{
		len = 0;
		if (n < 0)
			len++;
		while (n != 0)
		{
			n /= 10;
			len++;
		}
	}
	return (len);
}

char	*ft_num_convert(long int n, char *str, size_t len)
{
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	if (n == 0)
		str[0] = '0';
	else
	{
		len--;
		while (n != 0)
		{
			str[len] = (n % 10) + '0';
			n /= 10;
			len--;
		}
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t		len;
	long int	num;
	char		*str;

	num = (long int)n;
	len = ft_num_len(num);
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	return (ft_num_convert(num, str, len));
}
