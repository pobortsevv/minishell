/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arg_utilit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:40:23 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/07 13:18:19 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_crt_wrd_1(char const *s, char *c, t_word *w)
{
	while (s[w->i] && ft_isntend_split(&s[w->i + w->d], &(w->flag)) &&
			((!ft_strchr(c, s[w->i + w->d])) || (ft_strchr(c, s[w->i + w->d])
				&& (checkbit(w->flag, SINGLE_Q) || checkbit(w->flag, TAIL) ||
				checkbit(w->flag, DOUBLE_Q) || checkbit(w->flag, SLASH_2)))))
	{
		(w->i)++;
		if (w->d > 0)
			(w->d)--;
		if (!(ft_strchr(c, s[w->i + w->d])) && checkbit(w->flag, TAIL))
			w->flag = unsetbit(w->flag, TAIL);
	}
	return ;
}

static void	ft_crt_wrd_2(char const *s, char *c, char **word, t_word *w)
{
	while (s[w->i] && ft_isntend_split(&s[w->i + w->d], &(w->flag))
			&& ((!ft_strchr(c, s[w->i + w->d])) || (ft_strchr(c, s[w->i + w->d])
			&& (checkbit(w->flag, SINGLE_Q) || checkbit(w->flag, TAIL)
				|| checkbit(w->flag, DOUBLE_Q) || checkbit(w->flag, SLASH_2)))))
	{
		(*word)[w->i] = s[w->i];
		(w->i)++;
		if (w->d > 0)
			(w->d)--;
		if (!(ft_strchr(c, s[w->i + w->d])) && checkbit(w->flag, TAIL))
			w->flag = unsetbit(w->flag, TAIL);
	}
	(*word)[w->i] = '\0';
	return ;
}

char		*ft_create_word_a(char const *s, char *c)
{
	char	*word;
	t_word	wrd;

	wrd.i = 0;
	wrd.flag = 0;
	wrd.d = 0;
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		wrd.d = 2;
	else if (s[0] == '>' || s[0] == '<')
		wrd.d = 1;
	if (wrd.d)
		wrd.flag = setbit(wrd.flag, TAIL);
	ft_crt_wrd_1(s, c, &wrd);
	if (!(word = (char *)malloc(sizeof(char) * (wrd.i + 1))))
		return (NULL);
	wrd.i = 0;
	wrd.flag = 0;
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		wrd.d = 2;
	else if (s[0] == '>' || s[0] == '<')
		wrd.d = 1;
	if (wrd.d)
		wrd.flag = setbit(wrd.flag, TAIL);
	ft_crt_wrd_2(s, c, &word, &wrd);
	return (word);
}
