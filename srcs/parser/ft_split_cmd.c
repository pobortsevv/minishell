/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:02:21 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/17 12:37:52 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

size_t		ft_count(char const *s, char c)
{
	size_t	count;
	int		flag;

	count = 0;
	flag = 0;
	while (*s)
	{
		while (*s && ft_isntend_split(s, &flag) && (s[0] == c &&
			(!checkbit(flag, SINGLE_Q) || !checkbit(flag, DOUBLE_Q) ||
			!checkbit(flag, SLASH_2))))
			s++;
		if (*s && ft_isntend_split(s, &flag) && (s[0] != c ||
				(s[0] == c && (checkbit(flag, SINGLE_Q)
					|| checkbit(flag, DOUBLE_Q) || checkbit(flag, SLASH_2)))))
		{
			count++;
			while (*s && ft_isntend_split(s, &flag) && (s[0] != c ||
				(s[0] == c && (checkbit(flag, SINGLE_Q)
					|| checkbit(flag, DOUBLE_Q) || checkbit(flag, SLASH_2)))))
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
			(checkbit(flag, SINGLE_Q) || checkbit(flag, DOUBLE_Q) ||
			checkbit(flag, SLASH_2)))))
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	flag = 0;
	while (s[i] && ft_isntend_split(&s[i], &flag) && (s[i] != c || (s[i] == c &&
			(checkbit(flag, SINGLE_Q) || checkbit(flag, DOUBLE_Q) ||
			checkbit(flag, SLASH_2)))))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_skip(char const **s, int *flag, char c)
{
	*flag = 0;
	while (**s && ft_isntend_split(*s, flag) && ((*s)[0] != c || ((*s)[0] == c
			&& (checkbit(*flag, SINGLE_Q) || checkbit(*flag, DOUBLE_Q) ||
				checkbit(*flag, SLASH_2)))))
		(*s)++;
	return ;
}

static int	ft_check_flag(int flag)
{
	int		res;

	res = 0;
	res = (checkbit(flag, SINGLE_Q) || checkbit(flag, DOUBLE_Q) ||
			checkbit(flag, SLASH_2));
	return (res);
}

char		**ft_split_cmd(char const *s, char c, size_t i, int flag)
{
	char	**result;

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
			(ft_check_flag(flag)))))
		{
			if (!(result[i] = ft_create_word(s, c)))
			{
				ft_free_split(result, i);
				return (NULL);
			}
			i++;
			ft_skip(&s, &flag, c);
		}
	}
	result[i] = NULL;
	return (result);
}
