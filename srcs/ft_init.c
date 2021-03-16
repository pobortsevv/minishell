/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 07:47:52 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/16 12:01:12 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		**ft_copy_envp(char **ev)
{
	size_t	env_count;
	size_t	i;
	char	**evc;

	if (!ev)
		return (NULL);
	env_count = 0;
	i = 0;
	while (ev[env_count])
		env_count++;
	evc = (char **)malloc(env_count);
	if (!evc)
		return (NULL);
	while (i < env_count)
	{
		evc[i] = ft_strdup(ev[i]);
		i++;
	}
	return (evc);
}

 void			ft_set_sh(t_cmd *sh)
{
	sh->args = NULL;
	sh->id = 0;
	sh->in = 0;
	sh->out = 1;
	return ;
}

char			**ft_init(char **ev)
{
	return (ft_copy_envp(ev));
//	ft_set_sh(sh);
}
