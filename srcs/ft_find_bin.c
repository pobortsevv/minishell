/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 22:22:43 by sabra             #+#    #+#             */
/*   Updated: 2021/03/29 13:58:17 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_find_bin(char *filename, char *path)
{
	struct stat 	buf;
	char		**split;
	char		*shot;
	char		*tmp;
	size_t		len;

	if (stat(filename, &buf) != -1)
		return (filename);
	if (!path)
		return (NULL);
	len = 0;
	split = ft_split(path, ':');
	while (split[len])
		len++;
	while (len-- > 0)
	{
		tmp = ft_strjoin(split[len], "/");
		shot = ft_dup_join(tmp, filename);
		if (tmp)
			ft_free_line(&tmp);
		if (stat(shot, &buf) != -1)
		{
			ft_free_mat(split);
			return (shot);
		}
		if (shot)
			ft_free_line(&shot);
	}
	ft_free_mat(split);
	return (NULL);
}
