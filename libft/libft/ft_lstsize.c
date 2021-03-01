/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:39:39 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 20:19:30 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int			len;
	t_list		*list;

	list = lst;
	len = 0;
	if (!lst)
		return (0);
	while (list->next != NULL)
	{
		list = list->next;
		len++;
	}
	if (list->next == NULL)
		len++;
	return (len);
}
