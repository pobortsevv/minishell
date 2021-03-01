/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:23:05 by sabra             #+#    #+#             */
/*   Updated: 2021/01/04 19:02:09 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

t_struct	struct_init(void)
{
	t_struct flgs;

	flgs.minus = 0;
	flgs.zero = 0;
	flgs.width = 0;
	flgs.dot_star = -1;
	flgs.lenght = 0;
	flgs.type = '\0';
	return (flgs);
}

int			ft_parser(const char *str, int i, va_list args, int *count)
{
	t_struct flgs;

	flgs = struct_init();
	while (flgs.type == '\0' && str[i] != '\0')
	{
		if (str[i] == '%')
			flgs.type = '%';
		else if (str[i] == '0' && flgs.minus == 0 && str[i - 1] == '%')
			flgs.zero = 1;
		else if (str[i] == '-')
			flgs = ft_minus_init(flgs);
		else if (str[i] == '.')
			flgs = ft_dot_star_init(str, flgs, i, args);
		else if (((str[i] >= '1' && str[i] <= '9') ||
		(str[i] == '*' && str[i - 1] != '.')) && flgs.dot_star == -1)
			flgs = ft_width_init(str, flgs, i, args);
		else if (ft_isalpha(str[i]))
			flgs.type = str[i];
		i++;
	}
	flgs.lenght = flgs.width >= flgs.dot_star ? flgs.width : flgs.dot_star;
	*count += ft_type_init(flgs, args);
	return (i);
}

int			ft_write_common(const char *str, va_list args, int i)
{
	int		count;

	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			i = ft_parser(str, i + 1, args, &count) - 1;
		else
		{
			ft_putchar_fd(str[i], 1);
			count++;
		}
		i++;
	}
	return (count);
}
