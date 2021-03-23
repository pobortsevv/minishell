/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_parser_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:07:24 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/23 15:07:11 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

static char		**ft_copy_array_shell(char **r_a, char **a, int *in, int *out)
{
	int		i;
	int		len;
	int		res;
	char	**norm;

	i = 0;
	len = ft_lenarray(a);
	//printf("array a:\n");
	//ft_print_array_2(a);
	r_a = (char **)malloc(sizeof(char *) * len + 1);
	if (r_a == NULL)
		return (ft_parser_er2(strerror(errno)));
	r_a[len] = NULL;
	if (!(norm = ft_make_norm(a, in, out)))
		return (NULL);
	//printf("после нормализации\n");
	//ft_print_array_2(norm);
	while (norm[i] != NULL)
	{
		if ((r_a[i] = (char *)malloc(ft_strlen(norm[i]) + 1)) == NULL)
			return (ft_parser_er2(strerror(errno)));
		res = ft_strlcpy(r_a[i], norm[i], ft_strlen(norm[i]) + 1);
		if (res != (int)ft_strlen(norm[i]))
		{
			free(r_a[i]);
			r_a[i] = NULL;
			free_array_shell(r_a);
			return (ft_parser_er2(strerror(errno)));
		}
		i++;
	}
	free_array_shell(norm);
	return (r_a);
}

static t_cmd	ft_make_tcmd(char **a)
{
	t_cmd	res;

	res.id = 0;
	res.in = 0;
	res.out = 1;
	res.args = ft_copy_array_shell(res.args, a, &res.in, &res.out);
	res.len_args = ft_lenarray(a);
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
		//пришла ошибка, если ar_cmd[i].args[0] == NULL
		//TODO обработать pipe через dup2
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
	//printf("после сплита по pipe\n");
	//ft_print_array_3(arg_pipe);
	free_array_shell(cmd_pipe);
	return (arg_pipe);
}

int				ft_parser_shell(char **envp, char *str)
{
	char	**cmd;
	t_cmd	*ar_t_cmd;
	int		i;
	char	***ar_pipe;
	int		len;

	i = 0;
	ar_t_cmd = NULL;
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
		//printf("массив полученный pipe:\n");
		//ft_print_array_3(ar_pipe);
		ar_t_cmd = ft_make_ar_cmd(ar_pipe, len);
		free_array_shell_2(ar_pipe);
		/*TODO  вызов функций для выполнения массива t_cmd */
		/* а пока печать массива t_cmd */
//		if (ar_t_cmd[0].args != NULL) 
		if (ar_t_cmd != NULL)
		{
			ft_print_array_t_cmd(ar_t_cmd, len);
			free_close_fd(ar_t_cmd, len);
			free_t_cmd(ar_t_cmd, len);
		}
		i++;
	}
	/* free массив - массив команд разделенных ;*/
	free_array_shell(cmd);
	/*TODO убрать эту проверку в дальнейшем, когда будем использовать envp */
	(void)envp;
	return (0);
}
