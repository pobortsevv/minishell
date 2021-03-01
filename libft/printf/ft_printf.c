/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:01:47 by sabra             #+#    #+#             */
/*   Updated: 2021/01/04 19:01:01 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	ft_printf(const char *input, ...)
{
	int		count;
	char	*str;
	va_list	args;

	str = ft_strdup((char *)input);
	va_start(args, input);
	count = ft_write_common(str, args, 0);
	va_end(args);
	free(str);
	return (count);
}
