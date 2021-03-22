/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 23:25:54 by sabra             #+#    #+#             */
/*   Updated: 2021/03/22 22:10:38 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_unstr(char *var, char *key)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!var || !key)
		return(0);
	while (var[i] && key[i] && var[i] == key[i] && var[i] != '=')
		i++;
	while (var[len] && var[len] != '=')
		len++;
	if (ft_strlen(key) == i && ft_strlen(key) == len)
		return (1);
	return (0);
}

char 	**ft_del_env(char **ev, size_t env_count, char *el)
{
	size_t	i;
	size_t	j;
	char 	**res;

	i = 0;
	j = 0;
	res = (char **)malloc(sizeof(char *) * env_count + 1);
	if (!res)
		return (NULL);
	while (i < env_count)
	{
		if (ft_strnstr(ev[i], el, ft_strlen(el)))
		{
			i++;
			continue;
		}
		res[j] = ft_strdup(ev[i]);
		i++;
		j++;
	}
	res[j] = NULL;
	ft_free_mat(ev);
	return (res);
}

size_t	unset_check(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=' || ft_isdigit(s[0]))
		{
			ft_printf("minishell: unset: `%s': not a valid identifier\n", s);
			return (0);
		}
		i++;
	}
	return (1);
}

char 	**ft_unset(t_cmd *cmd, char **ev)
{
	int	i;
	size_t	j;
	size_t	env_count;


	i = 1;
	env_count = 0;
	while (ev[env_count])
		env_count++;
	if (cmd->len_args == 1)
		return (ev);
	while (i < cmd->len_args)
	{
		j = 0;
		if (!unset_check(cmd->args[i]))
		{
			i++;
			continue;
		}
		while (j < env_count)
		{
			if (ev[j] && ft_unstr(ev[j], cmd->args[i]))
			{
				ev = ft_del_env(ev, --env_count, cmd->args[i]);
				if (!ev)
					return (NULL);
				env_count--;
			}
			j++;
		}
		i++;
	}
	return (ev);
}
