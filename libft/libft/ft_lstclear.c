/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:29:57 by sabra             #+#    #+#             */
/*   Updated: 2021/02/01 15:21:24 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*elem;
	t_list	*list;

	list = *lst;
	while (list)
	{
		elem = list->next;
		if (del)
			del(list->content);
		free(list);
		list = elem;
	}
	*lst = NULL;
}
