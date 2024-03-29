/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:05:16 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 16:20:51 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_mat(char **mat)
{
	int i;

	i = 0;
	if (!mat)
		return (NULL);
	while (mat[i])
	{
		ft_free_line(&mat[i]);
		i++;
	}
	free(mat);
	mat = NULL;
	return (mat);
}

void	ft_free_line(char **line)
{
	free(*line);
	*line = NULL;
}
