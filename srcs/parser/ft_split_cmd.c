/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 12:46:17 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/10 10:56:34 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

static int	ft_isntend_split(char const *s, int *flag)
{
	int		ret;

	ret = 1;
	if ((checkbit(*flag, SLASH_1) && checkbit(*flag, SLASH_2)) || !checkbit(*flag, SLASH_1))
	{
		if (checkbit(*flag, SLASH_2))
		{
			*flag = switchbit(*flag, SLASH_1);
			*flag = switchbit(*flag, SLASH_2);
		}
		if (!(checkbit(*flag, SINGLE_QUOTE)) && s[0] == '\\')
			* flag = setbit(*flag, SLASH_1);
		else if (s[0] == 39)
			*flag = switchbit(*flag, SINGLE_QUOTE);
		else if (!(checkbit(*flag, SINGLE_QUOTE)) && s[0] == '"')
			*flag = switchbit(*flag, DOUBLE_QUOTE);
	}
	else if (checkbit(*flag, SLASH_1))
		*flag = setbit(*flag, SLASH_2);
	return (ret);
}

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
	int		flag;

	count = 0;
	flag = 0;
	while (*s)
	{
		while (*s && ft_isntend_split(s, &flag) && (s[0] == c &&
			(!checkbit(flag, SINGLE_QUOTE) || !checkbit(flag, DOUBLE_QUOTE) || !checkbit(flag, SLASH_2))))
			s++;
		if (*s && ft_isntend_split(s, &flag) && (s[0] != c ||
				(s[0] == c && (checkbit(flag, SINGLE_QUOTE)
					|| checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
		{
			count++;
			while (*s && ft_isntend_split(s, &flag) && (s[0] != c ||
				(s[0] == c && (checkbit(flag, SINGLE_QUOTE)
					|| checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
				s++;
		}
	}
	return (count);
}

char		*ft_create_word(char const *s, char c)
{
	char	*word;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (s[i] && ft_isntend_split(&s[i], &flag) && (s[i] != c || (s[i] == c &&
			(checkbit(flag, SINGLE_QUOTE) || checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	flag = 0;
	while (s[i] && ft_isntend_split(&s[i], &flag) && (s[i] != c || (s[i] == c &&
			(checkbit(flag, SINGLE_QUOTE) || checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char		**ft_split_cmd(char const *s, char c)
{
	size_t	i;
	char	**result;
	int		flag;

	i = 0;
	flag = 0;
	if (!s ||
			!(result = (char **)malloc(sizeof(char *) * (ft_count(s, c)) + 1)))
		return (NULL);
	while (*s)
	{
		while (*s && s[0] == c && ft_isntend_split(s, &flag))
			s++;
		if (*s && ft_isntend_split(s, &flag) && (s[0] != c || (s[0] == c &&
			(checkbit(flag, SINGLE_QUOTE) || checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
		{
			if (!(result[i] = ft_create_word(s, c)))
			{
				ft_free_split(result, i);
				return (NULL);
			}
			i++;
			flag = 0;
			while (*s && ft_isntend_split(s, &flag) && (s[0] != c || (s[0] == c
			&& (checkbit(flag, SINGLE_QUOTE) || checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
