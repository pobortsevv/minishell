/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:42:54 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/15 09:46:19 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

static int	ft_isntend_split_a(char const *s, int *flag)
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

void		ft_free_split_a(char **result, size_t last)
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

size_t		ft_count_a(char const *s, char *c)
{
	size_t	count;
	int		flag;

	count = 0;
	flag = 0;
	while (*s)
	{
		while (*s && ft_isntend_split_a(s, &flag) && (ft_strchr(c, s[0]) &&
			(!checkbit(flag, SINGLE_QUOTE) || !checkbit(flag, DOUBLE_QUOTE) || !checkbit(flag, SLASH_2))))
			s++;
		if (*s && ft_isntend_split_a(s, &flag) && ((!ft_strchr(c, s[0])) ||
				(ft_strchr(c, s[0]) && (checkbit(flag, SINGLE_QUOTE)
					|| checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
		{
			count++;
			while (*s && ft_isntend_split_a(s, &flag) && ((!ft_strchr(c, s[0])) ||
				(ft_strchr(c, s[0]) && (checkbit(flag, SINGLE_QUOTE)
					|| checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
				s++;
		}
	}
	return (count);
}

char		*ft_create_word_a(char const *s, char *c)
{
	char	*word;
	int		i;
	int		flag;
	int		d;

	i = 0;
	flag = 0;
	d = 0;
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] =='<'))
		d = 2;
	else if (s[0] == '>' ||  s[0] == '<')
		d = 1;
	if (d)
		flag = setbit(flag, TAIL);
	while (s[i] && ft_isntend_split_a(&s[i+d], &flag) && ((!ft_strchr(c, s[i+d])) || (ft_strchr(c, s[i+d])  &&
			(checkbit(flag, SINGLE_QUOTE) || checkbit(flag, TAIL) ||checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
	{
		i++;
		if (d > 0)
			d--;
		if (!(ft_strchr(c, s[i + d])) && checkbit(flag, TAIL))
			flag = unsetbit(flag, TAIL);
	}
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	flag = 0;
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' &&  s[1] == '<'))
		d = 2;
	else if (s[0] == '>' ||  s[0] == '<')
		d = 1;
	if (d)
		flag = setbit(flag, TAIL);
	while (s[i] && ft_isntend_split_a(&s[i+d], &flag) && ((!ft_strchr(c, s[i+d])) || (ft_strchr(c, s[i+d]) &&
			(checkbit(flag, SINGLE_QUOTE) ||  checkbit(flag, TAIL) || checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
	{
		word[i] = s[i];
		i++;
		if (d > 0)
			d--;
		if (!(ft_strchr(c, s[i + d])) && checkbit(flag, TAIL))
			flag = unsetbit(flag, TAIL);
	}
	word[i] = '\0';
	return (word);
}

char		**ft_split_arg(char const *s, char *c)
{
	size_t	i;
	char	**result;
	int		flag;
	int 	d;

	d = 0;
	i = 0;
	flag = 0;
	if (!s ||
			!(result = (char **)malloc(sizeof(char *) * (ft_count_a(s, c)) + 1)))
		return (NULL);
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		if (s[0] == '>' && s[1] == '>')
			d = 2;
		else if (s[0] == '>' ||  s[0] == '<')
			d = 1;
		if (d)
			flag = setbit(flag, TAIL);
		if (*(s+d) && ft_isntend_split_a((s+d), &flag) && ((!ft_strchr(c, s[d])) || (ft_strchr(c, s[d]) &&
			(checkbit(flag, SINGLE_QUOTE) ||checkbit(flag, TAIL) || checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
	//	if (*s != ' ' && *s)
		{
			if (!(result[i] = ft_create_word_a(s, c)))
			{
				ft_free_split_a(result, i);
				return (NULL);
			}
			i++;
			flag = 0;
			if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] =='<'))
 				d = 2;
			else if (s[0] == '>' ||  s[0] == '<')
				d = 1;
			if (d)
			flag = setbit(flag, TAIL);
			while (*(s+d) && ft_isntend_split_a((s+d), &flag) && ((!ft_strchr(c, s[d])) || (ft_strchr(c, s[d])  &&
			(checkbit(flag, SINGLE_QUOTE) || checkbit(flag, TAIL) ||checkbit(flag, DOUBLE_QUOTE) || checkbit(flag, SLASH_2)))))
			{
				s++;
 			    if (d > 0)
 					d--;
 				if (!(ft_strchr(c, s[0])) && checkbit(flag, TAIL))
					flag = unsetbit(flag, TAIL);
			}
		}
	}
	result[i] = NULL;
	//TODO убрать тестовою печать
	i = 0;
	printf("result = = \n");
	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		i++;
	}
	return (result);
}
