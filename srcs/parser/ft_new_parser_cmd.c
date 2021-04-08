/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_parser_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:07:24 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 17:33:04 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		**ft_cp_ar_sh(char **r_a, char **a, t_cmd **cmd, char **envp)
{
	int		i;
	int		res;
	char	**norm;

	i = 0;
	if ((r_a = (char **)malloc(sizeof(char *) * ft_lenarray(a) + 1)) == NULL)
		return (ft_parser_er2(strerror(errno)));
	r_a[ft_lenarray(a)] = NULL;
	if (!(norm = ft_make_norm(a, &((*cmd)->in), &((*cmd)->out), envp)))
		return (ft_free_r_a(&r_a));
	while (norm[i] != NULL)
	{
		if ((r_a[i] = (char *)malloc(ft_strlen(norm[i]) + 1)) == NULL)
			return (ft_parser_er2(strerror(errno)));
		res = ft_strlcpy(r_a[i], norm[i], ft_strlen(norm[i]) + 1);
		if (res != (int)ft_strlen(norm[i]))
		{
			ft_free_r_a_i(&r_a, i);
			return (ft_parser_er2(strerror(errno)));
		}
		i++;
	}
	ft_cp_ar_sh_part(&r_a, i, ft_lenarray(a));
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
	res.args = ft_cp_ar_sh(res.args, a, &res_ad, envp);
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
	fd[0] = 0;
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
	ar_t_cmd = NULL;
	if ((cmd = ft_split_cmd(str, ';', 0, 0)) == NULL)
		ft_putstr_error(strerror(errno), errno);
	while (cmd != 0 && cmd[i] != NULL)
	{
		if (((ar_pipe = ft_new_parser_cmd(cmd[i], &len)) == NULL) ||
			((ar_t_cmd = ft_make_ar_cmd(ar_pipe, len, envp)) == NULL))
		{
			ft_ar_null(ar_pipe);
			continue ;
		}
		free_array_shell_2(ar_pipe);
		envp = ft_parser_shel_cycle(ar_t_cmd, len, envp, &cmd);
		i++;
	}
	free_array_shell(cmd);
	return (envp);
}
