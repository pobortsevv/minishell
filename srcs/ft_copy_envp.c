/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:30:41 by sabra             #+#    #+#             */
/*   Updated: 2021/03/28 14:52:16 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char		*create_var(char *key, char *value)
{ char *result;
	char *tmp_key;
	char *tmp;

	if (!key || !value)
		return (NULL);
	tmp_key = ft_strdup(key);
	tmp = ft_strjoin(tmp_key, "=");
	ft_free_line(&tmp_key);
	result = ft_strjoin(tmp, value);
	ft_free_line(&tmp);
	if (value)
		ft_free_line(&value);
	return (result);
}

char		*ft_find_env(char *key, char **ev)
{
	size_t i;
	size_t len_env;

	i = 0;
	len_env = 0;
	while (ev[len_env])
		len_env++;
	if (!key)
		return (NULL);
	while (i < len_env)
	{
		if (ft_strnstr(ev[i], key, ft_strlen(key)))
			return (ev[i]);
		i++;
	}
	return (NULL);
}

char		**ft_init_envp(char **ev)
{
	size_t	len_env;
	char 	*pwd_value;
	char	*new_pwd;

	len_env = 0;
	while (ev[len_env])
		len_env++;
	ev = ft_del_env(ev, len_env, ft_find_env("OLDPWD", ev));
	if (!ft_find_env("PWD", ev))
	{
		pwd_value = getcwd(NULL, 0);
		if (!pwd_value)
			return (ev);
		new_pwd = create_var("PWD", pwd_value);
		ev = add_value(new_pwd, ev);
	}
	else
	{
		pwd_value = getcwd(NULL, 0);
		if (!pwd_value)
			return (ev);
		new_pwd = create_var("PWD", pwd_value);
		ev = change_value(new_pwd, ev);
	}
	ev = add_value("?=0", ev);
	return (ev);
}

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
