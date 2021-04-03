/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:42:40 by sabra             #+#    #+#             */
/*   Updated: 2021/04/03 14:43:27 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


static int		is_in_set(char s, char *set)
{
	int i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

static void		ft_free_split(char **result, size_t last)
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

static size_t		ft_count(char const *s, char *set)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && is_in_set(*s, set))
			s++;
		if (*s && !is_in_set(*s, set))
		{
			count++;
			while (*s && !is_in_set(*s, set))
				s++;
		}
	}
	return (count);
}

char		*ft_create_word(char const *s, char *set)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && !is_in_set(s[i], set))
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && !is_in_set(s[i], set))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char		**ft_splitset(char const *s, char *set)
{
	size_t	i;
	char	**result;

	i = 0;
	if (!s ||
	!(result = (char **)malloc(sizeof(char *) * (ft_count(s, set)) + 1)))
		return (NULL);
	while (*s)
	{
		while (*s && is_in_set(*s, set))
			s++;
		if (*s && !is_in_set(*s, set))
		{
			if (!(result[i] = ft_create_word(s, set)))
			{
				ft_free_split(result, i);
				return (NULL);
			}
			i++;
			while (*s && !is_in_set(*s, set))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
