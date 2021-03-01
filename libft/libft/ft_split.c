/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:39:08 by sabra             #+#    #+#             */
/*   Updated: 2020/11/09 16:11:15 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_split(char **result, size_t last)
{
	size_t i;

	i = 0;
	while (i < last)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

size_t		ft_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char		*ft_create_word(char const *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char		**ft_split(char const *s, char c)
{
	size_t	i;
	char	**result;

	i = 0;
	if (!s ||
	!(result = (char **)malloc(sizeof(char *) * (ft_count(s, c)) + 1)))
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			if (!(result[i] = ft_create_word(s, c)))
			{
				ft_free_split(result, i);
				return (NULL);
			}
			i++;
			while (*s != c && *s)
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
