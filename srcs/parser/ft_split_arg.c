/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:42:54 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/17 09:38:22 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

size_t			ft_count_a(char const *s, char *c)
{
	size_t	count;
	int		flag;

	count = 0;
	flag = 0;
	while (*s)
	{
		while (*s && ft_isntend_split(s, &flag) && (ft_strchr(c, s[0]) &&
			(!checkbit(flag, SINGLE_Q) || !checkbit(flag, DOUBLE_Q) ||
			!checkbit(flag, SLASH_2))))
			s++;
		if (*s && ft_isntend_split(s, &flag) && ((!ft_strchr(c, s[0])) ||
				(ft_strchr(c, s[0]) && (checkbit(flag, SINGLE_Q)
					|| checkbit(flag, DOUBLE_Q) || checkbit(flag, SLASH_2)))))
		{
			count++;
			while (*s && ft_isntend_split(s, &flag) && ((!ft_strchr(c, s[0])) ||
				(ft_strchr(c, s[0]) && (checkbit(flag, SINGLE_Q)
					|| checkbit(flag, DOUBLE_Q) || checkbit(flag, SLASH_2)))))
				s++;
		}
	}
	return (count);
}

static char		*ft_create_w_a(char const *s, char *c, int i, int d)
{
	char	*word;
	int		flag;

	ft_check_d(s, &d, &flag, &i);
	while (s[i] && ft_isntend_split(&s[i + d], &flag) &&
			((!ft_strchr(c, s[i + d])) || (ft_strchr(c, s[i + d])
				&& ft_check_tail(flag))))
	{
		i++;
		ft_check_d_less(s[i + d], c, &d, &flag);
	}
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_check_d(s, &d, &flag, &i);
	while (s[i] && ft_isntend_split(&s[i + d], &flag)
			&& ((!ft_strchr(c, s[i + d])) || (ft_strchr(c, s[i + d]) &&
					ft_check_tail(flag))))
	{
		word[i] = s[i];
		i++;
		ft_check_d_less(s[i + d], c, &d, &flag);
	}
	word[i] = '\0';
	return (word);
}

static int		ft_check_in_split(char *s, char *c, int d, int *flag)
{
	int		res;

	res = (*(s + d) && ft_isntend_split((s + d), flag)
				&& ((!ft_strchr(c, s[d])) || (ft_strchr(c, s[d])
				&& ft_check_tail(*flag))));
	return (res);
}

static void		ft_in_split(char **s, char *c, int *d, int *flag)
{
	while (ft_check_in_split(*s, c, *d, flag))
	{
		(*s)++;
		if (*d > 0 && **(s))
			(*d)--;
		if (!(ft_strchr(c, (*s)[0])) && checkbit(*flag, TAIL))
			*flag = unsetbit(*flag, TAIL);
	}
	return ;
}

char			**ft_split_arg(char *s, char *c, size_t i, int flag)
{
	char	**res;
	int		d;

	d = 0;
	if (!s || !(res = (char **)malloc(sizeof(char *) * (ft_count_a(s, c)) + 1)))
		return (NULL);
	while (*s && *(s + d))
	{
		while (*s && *s == ' ')
			s++;
		ft_check_d(s, &d, &flag, &flag);
		if (ft_check_in_split(s, c, d, &flag))
		{
			if (!(res[i] = ft_create_w_a(s, c, 0, 0)) && ft_free_split(res, i))
				return (NULL);
			i++;
			ft_check_d(s, &d, &flag, &flag);
			ft_in_split(&s, c, &d, &flag);
			if (d != 0 && *(s + d + 1) == '\0')
				break ;
		}
	}
	res[i] = NULL;
	return (res);
}
