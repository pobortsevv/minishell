/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_parser_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:07:24 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/29 16:23:42 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

static char		**ft_copy_array_shell(char **r_a, char **a, t_cmd  **cmd, char **envp)
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
	if (!(norm = ft_make_norm(a, &((*cmd)->in), &((*cmd)->out), envp)))
	//	if (!(norm = ft_make_norm(a, in, out)))
		return (NULL);
//	printf("после нормализации\n");
//	ft_print_array_2(norm);
//	printf("after in=%d, out =%d\n", (*cmd)->in, (*cmd)->out);
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
	while (i < len)
	{
		r_a[i] = NULL;
		i++;
	}
	free_array_shell(norm);
	return (r_a);
}

static t_cmd	ft_make_tcmd(char **a, char **envp, int in, int out)
{
	t_cmd	res;
	t_cmd	*res_ad;

	res.id = 0;
	res_ad = &res;
	res.in = in;
	res.out = out;
	res.args = ft_copy_array_shell(res.args, a, &res_ad, envp);
//	if (res.out != out) 
//		printf("парсер в пайпе встретил редирект на out\n");
//	printf("!!after in=%d, out =%d\n", res.in, res.out);
//	read(0,0,1);
	res.len_args = ft_lenarray(a);
	return (res);
}

static t_cmd	*ft_make_ar_cmd(char ***arg_pipe, int len, char **envp)
{
	t_cmd	*ar_cmd;
	int		i;
	int		fd[2];
	int		in;
	int		out;

	i = 0;
	fd[0] = 0; //in
	ar_cmd = (t_cmd *)malloc(sizeof(t_cmd) * len);
	while (i < len)
	{
		in = fd[0];
		if (i < len - 1)
		{
			pipe(fd);
			out = fd[1];
		}
		else if (i == len - 1)
			out = 1;

		(ar_cmd)[i] = ft_make_tcmd(arg_pipe[i], envp, in, out);
//		printf("!!!! in =%d, out =%d\n", ar_cmd[i].in, ar_cmd[i].out);
		//TODO если изменился out => был редирект => меняю для следующего по цепочке pipe in на новый in
		if (out != 1 && out != ar_cmd[i].out)
		{
			close(fd[0]);
			fd[0] = 0;
		//	fd[0] = ar_cmd[i].out;
		}
		//пришла ошибка, если ar_cmd[i].args[0] == NULL
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

char			**ft_parser_shell(char **envp, char *str)
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
		ar_t_cmd = ft_make_ar_cmd(ar_pipe, len, envp);
		free_array_shell_2(ar_pipe);
		/*TODO  вызов функций для выполнения массива t_cmd */
		/* а пока печать массива t_cmd */
		//envp = ft_exec_cmd(ar_t_cmd, envp, len);
		//free_t_cmd(ar_t_cmd, len);
		//
		//в случае ошибки у нас вернеться ar_t_cmd = NULL
		if (ar_t_cmd != NULL)
		{
			ft_print_array_t_cmd(ar_t_cmd, len);
			envp = ft_exec_cmd(ar_t_cmd, envp, len);
			free_close_fd(ar_t_cmd, len);
			free_t_cmd(ar_t_cmd, len);
		}
		i++;
	}
	/* free массив - массив команд разделенных ;*/
	free_array_shell(cmd);
	/*TODO убрать эту проверку в дальнейшем, когда будем использовать envp */
	return (envp);
}
