/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 07:47:52 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/05 07:50:49 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

// TODO сделать копирование в новый массив
static void		ft_copy_envp(char **envp, char **w_envp)
{
	if (envp && w_envp)
		;
	return ;
}

 void			ft_set_sh(t_cmd *sh)
{
	sh->args = NULL;
	sh->id = 0;
	sh->in = 0;
	sh->out = 1;
	return ;
}

void			ft_init(char **envp, char **w_envp)
{
	ft_copy_envp(envp, w_envp);
//	ft_set_sh(sh);
	return ;
}

