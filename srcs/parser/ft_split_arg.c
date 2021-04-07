/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:42:54 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/07 14:34:21 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

size_t		ft_count_a(char const *s, char *c)
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

static void	in_ft_split_arg(char **s, char *c, t_word *w)
{
	(w->i)++;
	w->flag = 0;
	if (((*s)[0] == '>' && (*s)[1] == '>')
			|| ((*s)[0] == '<' && (*s)[1] == '<'))
		w->d = 2;
	else if ((*s)[0] == '>' || (*s)[0] == '<')
		w->d = 1;
	if (w->d)
		w->flag = setbit(w->flag, TAIL);
	while (*((*s) + w->d) && ft_isntend_split(((*s) + w->d), &(w->flag))
			&& ((!ft_strchr(c, (*s)[w->d])) || (ft_strchr(c, (*s)[w->d])
					&& (checkbit(w->flag, SINGLE_Q) || checkbit(w->flag, TAIL)
						|| checkbit(w->flag, DOUBLE_Q)
						|| checkbit(w->flag, SLASH_2)))))
	{
		(*s)++;
		if (w->d > 0 && (*s))
			(w->d)--;
		if (!(ft_strchr(c, (*s)[0])) && checkbit(w->flag, TAIL))
			w->flag = unsetbit(w->flag, TAIL);
	}
	return ;
}

static void	in_ft_split_arg0(char **s, t_word *w)
{
	while (*(*s) && *(*s) == ' ')
		(*s)++;
	if ((*s)[0] == '>' && (*s)[1] == '>')
		w->d = 2;
	else if ((*s)[0] == '>' || (*s)[0] == '<')
		w->d = 1;
	if (w->d && *((*s) + w->d))
		w->flag = setbit(w->flag, TAIL);
	return ;
}

static int	in_ft_split_arg1(char *s, char *c, t_word *w)
{
	int		res;

	res = (*(s + w->d) && ft_isntend_split((s + w->d), &(w->flag))
			&& ((!ft_strchr(c, s[w->d])) || (ft_strchr(c, s[w->d])
					&& (checkbit(w->flag, SINGLE_Q)
						|| checkbit(w->flag, TAIL)
						|| checkbit(w->flag, DOUBLE_Q)
						|| checkbit(w->flag, SLASH_2)))));
	return (res);
}

char		**ft_split_arg(char *s, char *c, size_t i, int flag)
{
	char	**result;
	t_word	wrd;

	wrd.d = 0;
	wrd.i = i;
	wrd.flag = flag;
	if (!s ||
		!(result = (char **)malloc(sizeof(char *) * (ft_count_a(s, c)) + 1)))
		return (NULL);
	while (*s && *(s + wrd.d))
	{
		in_ft_split_arg0(&s, &wrd);
		if (in_ft_split_arg1(s, c, &wrd) == 1)
		{
			if (!(result[wrd.i] = ft_create_word_a(s, c)))
			{
				ft_free_split(result, wrd.i);
				return (NULL);
			}
			in_ft_split_arg(&s, c, &wrd);
		}
	}
	result[wrd.i] = NULL;
	return (result);
}
