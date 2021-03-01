/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 15:28:56 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 20:20:26 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

float	ft_queq(float a, float b, float c, int id)
{
	float d;
	float x1;
	float x2;

	d = b * b - (4 * a * c);
	if (d < 0)
		return (2147483647);
	x1 = (-b + sqrtf(d)) / (2 * a);
	x2 = (-b - sqrtf(d)) / (2 * a);
	if (id == 1)
		return (x1);
	return (x2);
}
