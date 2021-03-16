/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_parser_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:07:24 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/16 09:54:47 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include  <stdio.h>

void print_3_arr(char ***ar)
{
	int i;
	int	j;

	i = 0;
	while(ar[i] != NULL)
	{
		j = 0;
		while (ar[i][j] != NULL)
		{
			printf("array[%d][%d]=%s\n", i,j, ar[i][j]);
			j++;
		}
		i++;
	}
	return ;
}



void	free_array_shell(char **ar)
{
	int		i;

	i = 0;
	if (ar != NULL)
	{
		while (ar[i] != NULL)
		{
			free(ar[i]);
			ar[i] = NULL;
			i++;
		}
		free(ar);
		ar= NULL;
	}
	return ;
}

void	free_array_shell_2(char ***ar)
{
	int		i;

	i = 0;
	if (ar != NULL)
	{
		while (ar[i] != NULL)
		{
			free_array_shell(ar[i]);
			i++;
		}
		free(ar);
		ar= NULL;
	}
	return ;
}

void	free_t_cmd(t_cmd *ar_t_cmd, int len)
{
	int 	u;
	int		j;

	u = 0;
	while (u < len)
	{
		j=0;
		while(j < ar_t_cmd[u].len_args)
		{
			if (ar_t_cmd[u].args[j] != NULL)
			{
				free(ar_t_cmd[u].args[j]);
				ar_t_cmd[u].args[j] = NULL;
			}
			j++;
		}
		if (ar_t_cmd[u].args != NULL)
		{
			free(ar_t_cmd[u].args);
			ar_t_cmd[u].args = NULL;
		}
		u++;
	}
	free(ar_t_cmd);
	return ;
}

char	**ft_copy_array_shell(char **r_a,  char **a)
{
	int		i;
	int		len;
	int		res;

	i = 0;
	len = ft_lenarray(a);
	r_a = (char **)malloc(sizeof(char *) * len + 1);
	if (r_a == NULL)
	{
		// TODO обработку ошибок
		return (NULL);
	}
	while (a[i] != NULL)
	{
		r_a[i] = (char *)malloc(sizeof(char) * ft_strlen(a[i]) + 1);
		res = ft_strlcpy(r_a[i], a[i], ft_strlen(a[i]) + 1);
		if (res != (int)ft_strlen(a[i]))
		{
			// TODO обработку ошибок
			printf("ERROR with copy\n");
			return (NULL);
		}
		i++;
	}
	return (r_a);
}

t_cmd	ft_make_tcmd(char **a)
{
	t_cmd	res;

	res.args=ft_copy_array_shell(res.args, a);
	res.len_args = ft_lenarray(a);
	res.id = 0;
	res.in = 0;
	res.out	= 1;
	return (res);
}

t_cmd	*ft_make_ar_cmd(char ***arg_pipe, int len)
{
	t_cmd	*ar_cmd;
	int		i;

	i = 0;
	ar_cmd = (t_cmd *)malloc(sizeof(t_cmd) * len);
	while(i < len)	
	{
		(ar_cmd)[i] = ft_make_tcmd(arg_pipe[i]);
		i++;
	}
	return (ar_cmd);
}

char	 	***ft_new_parser_cmd(char *cmd, int *len)
{

	char	**cmd_pipe;
	char	***arg_pipe;
	int		i;

	i = 0;
	cmd_pipe=ft_split_cmd(cmd, '|');
	*len = ft_lenarray(cmd_pipe);
	arg_pipe = (char ***)malloc(sizeof(char**) * (*len) + 1);
	arg_pipe[*len] = NULL;
	while (i<*len)
	{
		arg_pipe[i] = ft_split_arg(cmd_pipe[i], SYM);
		i++;
	}
	free_array_shell(cmd_pipe);
	return (arg_pipe);
}

int		ft_parser_shell(char **envp, char *str)
{
	char	**cmd;
	t_cmd	*ar_t_cmd;
	int		i;
	char	***ar_pipe;
	int		len;

	i = 0;
	cmd = ft_split_cmd(str, ';');
	while (cmd[i] != NULL)
	{
		// здесь получаем массив *** - массив аргументов по pipe
		ar_pipe = ft_new_parser_cmd(cmd[i], &len);
	 	ar_t_cmd = ft_make_ar_cmd(ar_pipe, len);
		free_array_shell_2(ar_pipe);
		//TODO  вызов функций для выполнения массива t_cmd
		// а пока печать массива t_cmd

		printf("печать результата - массива t_cmd\n"); 
		int u = 0;
		while (u < len)
		{
			int		j=0;
			while(j < ar_t_cmd[u].len_args)
			{
				printf("ar_cmd[%d].args[%d]\n = %s\n",u, j, ar_t_cmd[u].args[j]);
				j++;
			}
			u++;
		}
		printf("массив напечатан\n");

		// free массив ar_t_cmd, то есть список аргументов  
		free_t_cmd(ar_t_cmd, len);
		i++;
	}
	// free массив - массив команд разделенных ; 
	free_array_shell(cmd);
	//TODO убрать эту проверку в дальнейшем, когда будем использовать envp
	if (envp != NULL)
		printf("OK");
	return (0);
}
