/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setbit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:16:02 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/03 10:44:35 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	setbit(const int value, const int position)
{
	return (value | (1 << position));
}
