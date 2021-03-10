/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:08:05 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/10 16:20:55 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_lenarray(char **cmd)
{
	int		res;

	res = 0;
	while (cmd && cmd[res] != 0)
		res++;
	return (res);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\r' || c == '\t' ||
		c == '\v')
		return (1);
	return (0);
}

 void ft_check_path(t_cmd *sh, char *str, int *post)
{
	if ((str[*post] != '\0') && (str[*post] == '/' ||
				(str[*post] == '~' && str[*post + 1] == '/') ||
				(str[*post] == '.' && str[*post + 1] == '/')))
			sh->id = setbit(sh->id, PATH);
	return ;
}

void	ft_pass_space(char *str, int *post)
{
	while (str[*post] != '\0' && ft_isspace(str[*post]))
		(*post)++;
	return ;
}

int	ft_isntend (char *s, int *flag, int *post)
{
	// ft_pass_space(s, post);
	if (s[*post] == '>' && s[*(post) + 1] != '>' &&
		(*flag = setbit(*flag, REDIRECTING_OUT)) && (*post)++)
		return (2);
	else if (s[*post] == '<' && s[*(post) + 1] != '<' &&
		(*flag = setbit(*flag, REDIRECTING_IN)) && (*post)++)
		return (2);
	else if (s[*post] == '>' && s[*(post) + 1] == '>' &&
			!checkbit(*flag, REDIRECTING_OUT) &&
		(*flag = setbit(*flag, APPENDIG_OUT)) && (*post)++ && (*post)++)
		return (2);
	return (1);
}


 int	ft_isntend_b (char *s, int *flag, int *post)
{
	int 	ret;

	ret = 1;
	if (!(checkbit(*flag, SINGLE_QUOTE)) && s[*post] == '\\')
	{
		//(*post)++;
		if (s[*post+1] != '\0')
			ret = 1;
		else
			ret = 0;
	}
	else if (s[*post+1] == 39)
	{
		*flag = switchbit(*flag, SINGLE_QUOTE);
//		(*post)++;
		if (s[*post+1] != '\0')
			ret = 1;
		else
			ret = 0;
	}
	else if (!(checkbit(*flag, SINGLE_QUOTE)) && s[*post + 1] == '"')
	{
		*flag = switchbit(*flag, DOUBLE_QUOTE);
//		(*post)++;
		if (s[*post+1] != '\0')
			ret = 1;
		else
			ret = 0;
	}
	else if (!(checkbit(*flag, SINGLE_QUOTE)) && !(checkbit(*flag, DOUBLE_QUOTE)))
	{
		ret = ft_isntend(s, flag, post);
//		ft_pass_space(s, post);
	}
	return(ret);
}

char	*ft_get_word (t_cmd *sh, char *str, int *post)
{
	char	*res;
	char	*temp;
	char	c[2];

	res = NULL;
	c[1] = '\0';
	while (str[*post] != '\0' && ft_isspace(str[*post]))
		(*post)++;
	if (str[*post] != '\0')  //&& (sh->id = )
	{
		res = (char *)ft_calloc(4, 3);
		res[0] = '\0';
		res[1] = '\0';
		res[3] = '\0';
//		printf("%d\n", sh->id);
		if (checkbit(sh->id, 2))
		{
			sh->id=unsetbit(sh->id, 2);
			res[0] = '>';
			while (str[*post] != '\0' && ft_isspace(str[*post]))
				(*post)++;
		}
		else if (checkbit(sh->id, 3))
		{
			sh->id=unsetbit(sh->id, 3);
			res[0] = '<';
			while (str[*post] != '\0' && ft_isspace(str[*post]))
				(*post)++;
		}
		else if (checkbit(sh->id, 4))
		{
			sh->id=unsetbit(sh->id, 4);
			res[0] = '>';
			res[1] = '>';
			while (str[*post] != '\0' && ft_isspace(str[*post]))
				(*post)++;
		}
		while (str[*post] != '\0' && (ft_isntend_b(str, &(sh->id), post)) &&
				(!checkbit(sh->id, 2) && !checkbit(sh->id, 3) &&
				!checkbit(sh->id, 4)) && !(ft_isspace(str[*post])))
				
				//&& (checkbit(sh->id, SINGLE_QUOTE) || checkbit(sh->id, DOUBLE_QUOTE) || !(ft_isspace(str[*post]))))
		{
			temp = res;
			c[0] = str[*post];
			res = ft_strjoin(res, c);
			if (temp)
				free(temp);
			(*post)++;
			while (str[*post] != '\0' && ft_isspace(str[*post])
					&& ft_isspace(str[*(post + 1)]))
				(*post)++;
		}

	}
	return (res);
}

 t_list	*ft_make_lst(t_cmd *sh, char *str, int *post)
{
	t_list	*cmd;
	t_list	*first;
	char	*temp;

	temp = ft_get_word(sh, str, post);
	cmd = ft_lstnew((void*)temp);
	first = cmd;
//	printf("first temp@@@@@@ = %s\n", temp);
	ft_pass_space(str, post);
//while ((temp = ft_get_word(sh, str, post)) != NULL 
//			&& (ft_isntend(str, &(sh->id), post) != 2))
	while((temp = ft_get_word(sh, str, post)) != NULL) 
	{
//		printf("в цикле temp = <%s>\n", temp);
//		read(0,0,1);
		if (temp[0] != 0)
		{
			cmd = ft_lstnew((void *)temp);
			ft_lstadd_back(&first, cmd);
		}
	}
//	printf("t =%d\n", t);
	return (first);
}

char **ft_make_array(t_list **first)
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

t_cmd		ft_parser_inst(char *str)
{
	t_list	*first;
	t_cmd	shh;
	int		post;

	post = 0;
	ft_bzero(&shh, sizeof(shh));
	while (str[post] != '\0' && ft_isspace(str[post]))
		(post)++;
	if (str[post] != '\0')
	{
		ft_check_path(&shh, str, &post);
		first = ft_make_lst(&shh, str, &post);
		shh.args = ft_make_array(&first);
	}
//	 (void)(w_envp);
	return (shh);
}

t_cmd	*ft_make_array_t_cmd(char ***cmd_pipe)
{
	int		len;
	t_cmd	*res;
	int		i;

	i = 0;
	len = ft_lenarray(*cmd_pipe);
//	printf("len=%d\n", len);
//	printf("массив:\n");
//	ft_print_array_2(cmd_pipe);
	res = (t_cmd *)malloc(sizeof(t_cmd) * len);
//	res[len] = NULL;
	while (i < len)
	{
		res[i] = ft_parser_inst(*cmd_pipe[i]);
		/*
		int	j=0;
		while (res[i].args[j] != NULL)
		{
			printf("res[%d].args[%d]\n = %s\n",i, j, res[i].args[j]);
			j++;
		}
		*/
		i++;
	}
	return (res);
}
