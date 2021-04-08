/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_parser_cmd_utilit.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:38:35 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/08 16:22:05 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_cp_ar_sh_part(char ***r_a, int i, int len)
{
	while (i < len)
	{
		(*r_a)[i] = NULL;
		i++;
	}
	return ;
}

void	*ft_free_r_a(char ***r_a)
{
	free((*r_a));
	(*r_a) = NULL;
	return (NULL);
}

void	ft_free_r_a_i(char ***r_a, int i)
{
	free((*r_a)[i]);
	(*r_a)[i] = NULL;
	free_array_shell((*r_a));
	return ;
}

void	ft_ar_null(char ***ar_pipe)
{
	ft_putstr_error(strerror(errno), errno);
	free_array_shell_2(ar_pipe);
	return ;
}

char	**ft_parser_shel_cycle(t_cmd *ar_t_cmd, int len, char **envp,
		char ***cmd)
{
	if (ft_check_er_args(ar_t_cmd, len) == -1)
		free_array_shell((*cmd));
	else if (ar_t_cmd != NULL && ar_t_cmd[0].args != NULL)
	{
		envp = ft_exec_cmd(ar_t_cmd, envp, len);
		free_close_fd(ar_t_cmd, len);
		free_t_cmd(ar_t_cmd, len);
	}
	return (envp);
}
