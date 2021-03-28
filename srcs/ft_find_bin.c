/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 22:22:43 by sabra             #+#    #+#             */
/*   Updated: 2021/03/28 22:40:58 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_find_bin(char *filename, char *path)
{
	struct stat 	buf;
	int		result;
	char		**split;
	char		*shot;
	size_t		len;

	if (stat(filename, &buf) == -1)
		result = 0;
	else
		return (filename);
	len = 0;
	split = ft_split(path, ':');
	while (split[len])
		len++;
	while (len-- >= 0)
	{
		shot = ft_strdup(split[len]);
		// TODO сделать функцию ft_dupjoin;
	}
	return (NULL);
}
