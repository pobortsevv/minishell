/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:37:52 by sabra             #+#    #+#             */
/*   Updated: 2021/01/05 09:52:19 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_mod(int fd, char **container)
{
	char	*result;
	int		end_1;
	int		i;

	end_1 = 0;
	i = 0;
	result = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (container[fd][end_1] != '\n' && container[fd][end_1] != '\0')
		end_1++;
	if (container[fd][end_1] == '\n')
		end_1++;
	while (container[fd][end_1] != '\0')
	{
		result[i] = container[fd][end_1];
		i++;
		end_1++;
	}
	if (container[fd])
		free(container[fd]);
	result[i] = '\0';
	return (result);
}

int		ft_readfile(int fd, char **line, char **container)
{
	int		count;

	while ((count = read(fd, container[fd], BUFFER_SIZE)) > 0)
	{
		container[fd][count] = '\0';
		if ((ft_strchr(container[fd], '\n')))
		{
			*line = (!(*line) ? ft_strdup_gnl(container[fd]) :
			ft_strjoin_gnl(*line, container[fd]));
			if (!(*line))
				return (-1);
			container[fd] = ft_mod(fd, container);
			return (1);
		}
		*line = ft_strjoin_gnl(*line, container[fd]);
	}
	if (count == 0 && !(*line))
		*line = ft_strdup_gnl("\0");
	return (count == -1 ? (-1) : 0);
}

int		cont_check(int fd, char **line, char **container)
{
	if ((ft_strchr(container[fd], '\n')))
	{
		if (!(*line = ft_strdup_gnl(container[fd])))
			return (-1);
		container[fd] = ft_mod(fd, container);
		return (1);
	}
	else
	{
		if (!(*line = ft_strdup_gnl(container[fd])))
			return (-1);
	}
	return (2);
}

int		get_next_line(int fd, char **line)
{
	static char			*container[1000];
	int					result;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	if (container[fd])
	{
		if ((result = (cont_check(fd, line, container))) < 2)
			return (result);
	}
	else
		container[fd] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	result = ft_readfile(fd, line, container);
	if (result < 1)
	{
		free(container[fd]);
		container[fd] = NULL;
	}
	return (result);
}
