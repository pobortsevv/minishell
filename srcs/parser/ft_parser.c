/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 08:48:50 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/05 13:44:26 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

//int	g_post = 0;

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\r' || c == '\t' ||
		c == '\v')
		return (1);
	return (0);
}

static void ft_check_path(t_cmd *sh, char *str, int *post)
{
	if ((str[*post] != '\0') && (str[*post] == '/' ||
				(str[*post] == '~' && str[*post + 1] == '/') ||
				(str[*post] == '.' && str[*post + 1] == '/')))
			sh->id = setbit(sh->id, PATH);
	return ;
}

static int	ft_isntend (char *s, int *flag, int *post)
{
	if (s[*post] == ';' && (*flag = setbit(*flag, SEMICOLON)) && (*post)++)
		return (0);
	else if (s[*post] == '|' && s[*post + 1] != '|' &&
		(*flag = setbit(*flag, PIPE)) && (*post)++)
		return (0);
	else if (s[*post] == '>' && s[*post + 1] != '>' &&
		(*flag = setbit(*flag, REDIRECTING_OUT)) && (*post)++)
		return (0);
	else if (s[*post] == '<' && s[*post + 1] != '<' &&
		(*flag = setbit(*flag, REDIRECTING_IN)) && (*post)++)
		return (0);
	else if (s[*post] == '>' && s[*post + 1] == '>' &&
		(*flag = setbit(*flag, APPENDIG_OUT)) && (*post)++ && (*post)++)
		return (0);
	else if (s[*post] == '&' && s[*post + 1] == '&' &&
			(*flag = setbit(*flag, AND)) && (*post)++ && (*post)++)
		return (0);
	else if (s[*post] == '|' && s[(*post) + 1] == '|' &&
			(*flag = setbit(*flag, OR)) &&  (*post)++ && (*post)++)
		return (0);
	return (1);
}


static int	ft_isntend_b (char *s, int *flag, int *post)
{
	int 	ret;

	ret = 1;
	if (!(checkbit(*flag, SINGLE_QUOTE)) && s[*post] == '\\')
	{
		(*post)++;
		if (s[*post] != '\0')
			ret = 1;
		else
			ret = 0;
	}
	else if (s[*post] == 39)
	{
		*flag = switchbit(*flag, SINGLE_QUOTE);
		(*post)++;
		if (s[*post] != '\0')
			ret = 1;
		else
			ret = 0;
	} else if (!(checkbit(*flag, SINGLE_QUOTE)))
		ret = ft_isntend(s, flag, post);
	return(ret);
}


static char	*ft_get_word (t_cmd *sh, char *str, int *post)
{
	char	*res;
	char	*temp;
	char	c[2];

	res = NULL;
	c[1] = '\0';
	while (str[*post] != '\0' && ft_isspace(str[*post]))
		(*post)++;
	if (str[*post] != '\0' && (sh->id == 0 || sh->id >= 128))
	{
		res = (char *)malloc(1);
		res[0] = '\0';
		while (str[*post] != '\0' && ft_isntend_b(str, &(sh->id), post)
				&& (checkbit(sh->id, SINGLE_QUOTE) || !(ft_isspace(str[*post]))))
		{
			temp = res;
			c[0] = str[*post];
			res = ft_strjoin(res, c);
			if (temp)
				free(temp);
			(*post)++;
			while (str[*post] != '\0' && ft_isspace(str[*post])
					&& ft_isspace(str[*post + 1]))
				(*post)++;
		}
	}
	return (res);
}

static t_list	*ft_make_lst(t_cmd *sh, char *str, int *post)
{
	t_list	*cmd;
	t_list	*first;
	char	*temp;

	temp = ft_get_word(sh, str, post);
	cmd = ft_lstnew((void*)temp);
	first = cmd;
	while ((temp = ft_get_word(sh, str, post)) != NULL &&
		ft_isntend(str, &(sh->id), post))
	{
		if (temp[0] != 0)
		{
			cmd = ft_lstnew((void *)temp);
			ft_lstadd_back(&first, cmd);
		}
	}
	return (first);
}

static char **ft_make_array(t_list **first)
{
	int		size;
	char	**array;
	int		i;
	t_list	*t;

	i = 0;
	size = ft_lstsize(*first);
	array = malloc(sizeof(char *)* size +1);
	array[size] = NULL;
	t = *first;
	while (t != NULL)
	{
		array[i] = ft_strdup((char *)t->content);
		t=t->next;
		i++;
	}
	ft_lstclear(first, free);
	return (array);
}

t_cmd		ft_parser_inst(char **w_envp, char *str, int *post)
{
	t_list	*first;
	t_cmd	shh;

	ft_bzero(&shh, sizeof(shh));
	while (str[*post] != '\0' && ft_isspace(str[*post]))
		(*post)++;
	if (str[*post] != '\0')
	{
		ft_check_path(&shh, str, post);
		first = ft_make_lst(&shh, str, post);
		shh.args = ft_make_array(&first);
	}
	 (void)(w_envp);
	return (shh);
}

t_list 		ft_parser(char **w_envp, char *str)
{
	int		post;
	int 	i;
	t_list	*first;
	t_list	*instr;
	t_cmd	shh[100];

	post = 0;
	i = 1;
	if (str[post] != '\0')
	{
		shh[0] = ft_parser_inst(w_envp, str, &post);
		first = ft_lstnew((void *)(&shh[0]));
	}
	while (str[post] != '\0')
	{
		shh[i] = ft_parser_inst(w_envp, str, &post);
		instr = ft_lstnew((void *)(&shh[i]));
		ft_lstadd_back(&(first), instr);
		i++;
	}
	(void)(w_envp);
	return (*first);
}
