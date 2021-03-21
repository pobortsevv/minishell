/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:30:41 by sabra             #+#    #+#             */
/*   Updated: 2021/03/21 20:13:00 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char		**ft_copy_envp(char **ev)
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
	evc = (char **)malloc(sizeof(char *) * env_count + 1);
	if (!evc)
		return (NULL);
	while (i < env_count)
	{
		evc[i] = ft_strdup(ev[i]);
		i++;
	}
	evc[i] = NULL;
	return (evc);
}
