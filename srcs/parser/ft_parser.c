/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 08:48:50 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/03 15:53:07 by mlaureen         ###   ########.fr       */
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

static char	*ft_get_word (t_sh *sh, char *str, int *post)
{
	char	*res;
	char	*temp;
	char	c[2];

	res = NULL;
	c[1] = '\0';
	while (str[*post] != '\0' && ft_isspace(str[*post]))
		(*post)++;
	if (str[*post] != '\0')
	{
		res = (char *)malloc(1);
		res[0] = '\0';
		while (ft_isntend(str, &(sh->flag), post) && !(ft_isspace(str[*post])
					&& str[*post] != '\0'))
		{
			if (str[*post] != ' ')
			{
				temp = res;
				c[0] = str[*post];
				res = ft_strjoin(res, c);
				if (temp)
					free(temp);
				(*post)++;
			}
			while (ft_isspace(str[*post]) && ft_isspace(str[*post + 1]))
				(*post)++;
		}
	}
	return (res);
}


void		ft_pars_arg(t_sh *sh, char *str, int *post)
{
	char	*arg;
	t_list	*alist;

	arg = ft_get_word(sh, str, post);
	if (arg != NULL)
	{
		sh->arg = ft_lstnew((void *)arg);
	}
	if (str[*post] != '\0' && ft_isntend(str, &(sh->flag), post))
		while ((arg =ft_get_word(sh, str,post)) != NULL)
		{
			alist = ft_lstnew((void *)arg);
			ft_lstadd_back(&(sh->arg), alist);
		}

	return ;
}

void		ft_parser_inst(t_sh *sh, char **w_envp, char *str, int *post)
{
	char	*temp;
	char	c[2];

	c[1] = '\0';
	while (str[*post] != '\0' && ft_isspace(str[*post]))
		(*post)++;
	if ((str[*post] != '\0') && (str[*post] == '/' ||
				(str[*post] == '~' && str[*post + 1] == '/') ||
				(str[*post] == '.' && str[*post + 1] == '/')))
			sh->flag = setbit(sh->flag, PATH);
	if (str[*post] != '\0')
	{
		sh->inst = (char *)malloc(1);
		sh->inst[0] = '\0';
		while (ft_isntend(str, &(sh->flag), post)  && !(ft_isspace(str[*post]))
					&& str[*post] != '\0')
		{
			if (str[*post] != ' ')
			{
				temp = sh->inst;
				c[0] = str[*post];
				sh->inst = ft_strjoin(sh->inst, c);
				if (temp)
					free(temp);

			}
			while (ft_isspace(str[*post]) && ft_isspace(str[*post + 1]))
				(*post)++;
			(*post)++;
		}
		if (ft_isspace(str[*post]))
			(*post)++;
		while (ft_isntend(str, &sh->flag, post) && str[*post] != '\0')
		{
			ft_pars_arg(sh, str, post);
		//	if (sh->arg->content !=NULL)
		//		printf("%s\n", (char *)(sh->arg->content));
		}

	}
	if (w_envp)
		;
	return ;
}

void		ft_parser(t_sh *sh, char **w_envp, char *str)
{
	int		post;

	post = 0;
	if (str[post] != '\0')
	{
		//TODO парсер инструкции
		ft_parser_inst(sh, w_envp, str, &post);
		//TODO парсер инструкции
		while (str[post] != '\0')
		{
			// TODO парсер аргументов
			//ft_parser_arg(sh, w_envp, str);
			;
		}
		//TODO парсер инструкции
	}
	if (w_envp)
		;
	return ;
}
