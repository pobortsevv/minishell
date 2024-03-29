/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbitop.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lana <LanaLebedeva2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:13:05 by lana              #+#    #+#             */
/*   Updated: 2021/03/05 13:15:57 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBITOP_H
# define LIBBITOP_H

# include <stddef.h>

size_t	checkbit(const int value, const int position);
int		setbit(const int value, const int position);
int		unsetbit(const int value, const int position);
int		switchbit(const int value, const int position);

#endif
