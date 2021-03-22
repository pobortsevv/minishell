/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_parser_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:07:24 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/22 17:18:21 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

static char		**ft_copy_array_shell(char **r_a, char **a)
{
	int		i;
	int		len;
	int		res;

	i = 0;
	len = ft_lenarray(a);
	r_a = (char **)malloc(sizeof(char *) * len + 1);
	if (r_a == NULL)
		return (ft_parser_er2(strerror(errno)));
	r_a[len] = NULL;
	while (a[i] != NULL)
	{
		if ((r_a[i] = (char *)malloc(ft_strlen(a[i]) + 1)) == NULL)
			return (ft_parser_er2(strerror(errno)));
		res = ft_strlcpy(r_a[i], a[i], ft_strlen(a[i]) + 1);
		if (res != (int)ft_strlen(a[i]))
		{
			free(r_a[i]);
			r_a[i] = NULL;
			free_array_shell(r_a);
			return (ft_parser_er2(strerror(errno)));
		}
		i++;
	} return (r_a);
}

static t_cmd	ft_make_tcmd(char **a)
{
	t_cmd	res;

	res.args = ft_copy_array_shell(res.args, a);
	res.len_args = ft_lenarray(a);
	res.id = 0;
	res.in = 0;
	res.out = 1;
	return (res);
}

static t_cmd	*ft_make_ar_cmd(char ***arg_pipe, int len)
{
	t_cmd	*ar_cmd;
	int		i;

	i = 0;
	ar_cmd = (t_cmd *)malloc(sizeof(t_cmd) * len);
	while (i < len)
	{
		(ar_cmd)[i] = ft_make_tcmd(arg_pipe[i]);
		i++;
	}
	return (ar_cmd);
}

static char		***ft_new_parser_cmd(char *cmd, int *len)
{
	char	**cmd_pipe;
	char	***arg_pipe;
	int		i;

	i = 0;
	cmd_pipe = ft_split_cmd(cmd, '|', 0, 0);
	*len = ft_lenarray(cmd_pipe);
	arg_pipe = (char ***)malloc(sizeof(char**) * (*len) + 1);
	arg_pipe[*len] = NULL;
	while (i < *len)
	{
		arg_pipe[i] = ft_split_arg(cmd_pipe[i], SYM, 0, 0);
		i++;
	}
	free_array_shell(cmd_pipe);
	return (arg_pipe);
}

char			**ft_parser_shell(char **envp, char *str)
{
	char	**cmd;
	t_cmd	*ar_t_cmd;
	int		i;
	char	***ar_pipe;
	int		len;

	i = 0;
	if ((cmd = ft_split_cmd(str, ';', 0, 0)) == NULL)
		ft_printf("%s\n", strerror(errno));
	while (cmd != 0 && cmd[i] != NULL)
	{
		/* здесь получаем массив *** - массив аргументов по pipe*/
		if ((ar_pipe = ft_new_parser_cmd(cmd[i], &len)) == NULL)
		{
			ft_printf("%s\n", strerror(errno));
			continue ; // TODO или break - завершить обработку строки?
		}
		ar_t_cmd = ft_make_ar_cmd(ar_pipe, len);
		free_array_shell_2(ar_pipe);
		/*TODO  вызов функций для выполнения массива t_cmd */
		/* а пока печать массива t_cmd */
		//ft_print_array_t_cmd(ar_t_cmd, len);
		envp = ft_exec_cmd(ar_t_cmd, envp, len);			
		free_t_cmd(ar_t_cmd, len);
		i++;
	}
	/* free массив - массив команд разделенных ;*/
	free_array_shell(cmd);
	/*TODO убрать эту проверку в дальнейшем, когда будем использовать envp */
	return (envp);
}
