/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 23:25:54 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 19:39:25 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		ft_unstr(char *var, char *key)
{
	size_t	i;
	size_t	var_len;
	size_t	key_len;

	i = 0;
	var_len = 0;
	key_len = 0;
	if (!var || !var[0] || !key)
		return (0);
	while (var[i] && key[i] && var[i] == key[i] && var[i] != '=')
		i++;
	while (var[var_len] && var[var_len] != '=')
		var_len++;
	while (key[key_len] && key[key_len] != '=')
		key_len++;
	if (key_len == i && key_len == var_len)
		return (1);
	return (0);
}

char	**ft_del_env(char **ev, size_t env_count, char *el)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	if (!el)
		return (ev);
	res = (char **)malloc(sizeof(char *) * env_count + 1);
	if (!res)
		return (NULL);
	while (i < env_count)
	{
		if (ft_unstr(ev[i], el))
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

char	**find_unset(char *arg, size_t *env_count, char **ev)
{
	size_t	j;

	j = 0;
	while (j < *env_count)
	{
		if (ev[j] && ft_unstr(ev[j], arg))
		{
			ev = ft_del_env(ev, --(*env_count), arg);
			if (!ev)
				return (NULL);
			(*env_count)--;
			break ;
		}
		j++;
	}
	return (ev);
}

char	**ft_unset(t_cmd *cmd, char **ev)
{
	int		i;
	size_t	env_count;

	i = 1;
	env_count = 0;
	while (ev[env_count])
		env_count++;
	if (cmd->len_args == 1)
		return (ev);
	while (i < cmd->len_args)
	{
		if (!unset_check(cmd->args[i]))
		{
			i++;
			continue;
		}
		if (!(ev = find_unset(cmd->args[i], &env_count, ev)))
			return (NULL);
		i++;
	}
	return (ev);
}
