/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:08:05 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/11 15:42:26 by mlaureen         ###   ########.fr       */
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
	char	*res_get;
	char	*temp;
	char	c[2];

	res_get = NULL;
	c[1] = '\0';
	printf("1111\n");
	while (str[*post] != '\0' && ft_isspace(str[*post]))
		(*post)++;
	printf("12\n");
	if (str[*post] != '\0')  //&& (sh->id = )
	{
		printf("$$$$$\n");
		printf("str=<%s>, post=%d\n", str, *post);
		res_get = (char *)malloc(3);
		if (res_get == NULL)
		{
			printf("error\n");
			return (NULL);
		}
		printf("str[]post=%c\n", str[*post]);
		//res_get[0] = '\0';
		//res_get[1] = '\0';
		//res_get[2] = '\0';
		ft_bzero(res_get, sizeof(res_get));
		printf("%d\n", sh->id);
		if (checkbit(sh->id, 2))
		{
			sh->id=unsetbit(sh->id, 2);
			res_get[0] = '>';
			while (str[*post] != '\0' && ft_isspace(str[*post]))
				(*post)++;
		}
		else if (checkbit(sh->id, 3))
		{
			sh->id=unsetbit(sh->id, 3);
			res_get[0] = '<';
			while (str[*post] != '\0' && ft_isspace(str[*post]))
				(*post)++;
		}
		else if (checkbit(sh->id, 4))
		{
			sh->id=unsetbit(sh->id, 4);
			res_get[0] = '>';
			res_get[1] = '>';
			while (str[*post] != '\0' && ft_isspace(str[*post]))
				(*post)++;
		}
		printf("13\n");
		while (str[*post] != '\0' && (ft_isntend_b(str, &(sh->id), post)) &&
				(!checkbit(sh->id, 2) && !checkbit(sh->id, 3) &&
				!checkbit(sh->id, 4)) && !(ft_isspace(str[*post])))
				//&& (checkbit(sh->id, SINGLE_QUOTE) || checkbit(sh->id, DOUBLE_QUOTE) || !(ft_isspace(str[*post]))))
		{
			temp = res_get;
			c[0] = str[*post];
			printf("before strjoin\n");
			res_get = ft_strjoin(res_get, c);
			printf("after strjoin\n");
			if (temp)
				free(temp);
			(*post)++;
			while (str[*post] != '\0' && ft_isspace(str[*post])
					&& ft_isspace(str[*post + 1]))
				(*post)++;
		}
	}
	printf("ВАЖНО: %s\n", res_get);
	return (res_get);
}

 t_list	*ft_make_lst(t_cmd *sh, char *str, int *post)
{
	t_list	*cmd;
	t_list	*first;
	char	*temp;

//	printf("0list память ок\n");
//	printf("str =%s, post = %d\n", str, *post);
	temp = ft_get_word(sh, str, post);
	printf("1list память ок\n");
//	printf("wwww\n");
	cmd = ft_lstnew((void*)temp);
	printf("2list память ок\n");
	first = cmd;
	printf("3list память ок\n");
//	printf("first temp@@@@@@ = %s\n", temp);
	ft_pass_space(str, post);
	printf("4list память ок\n");
//	while ((temp = ft_get_word(sh, str, post)) != NULL 
//			&& (ft_isntend(str, &(sh->id), post) != 2))
	while ((temp = ft_get_word(sh, str, post)) != NULL 
			&& (ft_isntend(str, &(sh->id), post) != 2))
	{
//		printf("в цикле temp = <%s>\n", temp);
//		read(0,0,1);
		if (temp[0] != 0)
		{
			cmd = ft_lstnew((void *)temp);
			ft_lstadd_back(&first, cmd);
		}
	}
	printf("5list память ок\n");
	printf("titttt\n");
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
//		printf("лист команд %s\n", t->content);
		array[i] = ft_strdup((char *)t->content);
		t=t->next;
		i++;
	}
//	ft_lstclear(first, free);
	return (array);
}

t_cmd	ft_parser_inst(char *str)
{
	t_list	*first;
	t_cmd	shh;
	int		post;

	post = 0;
	ft_bzero(&shh, sizeof(shh));
	printf("2память ок\n");
//	printf("1sssss\n");
	printf("srr[%d]=<%c>\n", post, str[post]);
	while (str[post] != '\0' && ft_isspace(str[post]))
		(post)++;
	printf("3память ок\n");
	if (str[post] != '\0')
	{
		printf("4память ок\n");
		ft_check_path(&shh, str, &post);
//		printf("1dddd\n");
//		printf("str =%s, post = %d\n", str, post);
		printf("5память ок\n");
		first = ft_make_lst(&shh, str, &post);
		printf("6память ок\n");
//		printf("1fffff\n");
//		printf("str =%s, post = %d\n", str, post);
		printf("7память ок\n");
		shh.args = ft_make_array(&first);
		printf("8память ок\n");
//		printf("1aaaa\n");
	}
//	 (void)(w_envp);
	return (shh);
}
/*
t_cmd	*ft_make_array_t_cmd(char **cmd_pipe)
{
	int		len;
	t_cmd	*res;
	int		i;
	t_cmd	temp;

	i = 0;
	len = ft_lenarray(cmd_pipe);
	res = (t_cmd *)malloc(sizeof(t_cmd) * len + 1);
	ft_bzero(&temp, sizeof(temp));
	temp.id = setbit(temp.id, END_ARRAY);
	res[len] = temp;
	while (!(checkbit(res[i].id, END_ARRAY)))
	{
		res[i] = ft_parser_inst(cmd_pipe[i]);
		int	j=0;
		printf("check = %zu", checkbit(res[0].id, END_ARRAY));
		printf("check len  = %zu\n", checkbit(res[len].id, END_ARRAY));
		while (res[i].args[j] != NULL)
		{
			printf("@@@@res[%d].args[%d]\n = %s\n",i, j, res[i].args[j]);
			j++;
			read(0, 0, 1);
		}
		i++;
	}
	printf("##### END###");
	return (res);
}
*/

t_cmd	*ft_make_array_t_cmd(char **cmd_pipe)
{
	int		len;
	t_cmd	*res;
	int		i;
	t_cmd	temp;


	i = 0;
	len = ft_lenarray(cmd_pipe);
	printf("leni cmd_pipe =%d\n", len);
	res = (t_cmd *)malloc(sizeof(t_cmd) * len + 1);
	if (res == NULL)
	{
		printf("error\n");
		return(NULL);
	}
	printf("память ок\n");
	ft_bzero(&temp, sizeof(temp));
	temp.id = setbit(temp.id, END_ARRAY);
	res[len] = temp;
	printf("0память ок\n");
	while (!(checkbit(res[i].id, END_ARRAY)))
	{
		printf("1память ок\n");
		res[i] = ft_parser_inst(cmd_pipe[i]);
//		int	j=0;
//		printf("check i = %zu", checkbit(res[i].id, END_ARRAY));
//		printf("check len  = %zu\n", checkbit(res[len].id, END_ARRAY));
//		while (res[i].args[j] != NULL)
//		{
//			printf("WWWWW reis[%d].args[%d]\n = %s\n",i, j, res[i].args[j]);
//			j++;
//			read(0, 0, 1);
//		}
		i++;
	}
//	printf("##### END###");
	return (res);
}

t_cmd		*ft_make_2_array_t_cmd(char **cmd_pipe)
{
	int		i;
	t_cmd	*res;

	i = 0;
	res = NULL;
	i = 0;
	res = ft_make_array_t_cmd(cmd_pipe);
	printf("WOWWW !\n");
	return (res);
}
