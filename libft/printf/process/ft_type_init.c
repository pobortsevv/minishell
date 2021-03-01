/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:53:09 by sabra             #+#    #+#             */
/*   Updated: 2021/01/04 19:04:23 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

int		ft_type_init(t_struct flgs, va_list args)
{
	int i;

	i = 0;
	if (flgs.type == 'c' || flgs.type == '%')
		i = ft_c_type(flgs, args, i);
	if (flgs.type == 's')
		i = ft_s_type(flgs, args);
	else if (flgs.type == 'p')
		i = ft_p_type(flgs, args);
	if (flgs.type == 'd' || flgs.type == 'i')
		i = ft_di_type(flgs, args, i);
	else if (flgs.type == 'u')
		i = ft_u_type(flgs, args);
	else if (flgs.type == 'x')
		i = ft_dwx_type(flgs, args);
	else if (flgs.type == 'X')
		i = ft_upx_type(flgs, args);
	return (i);
}
