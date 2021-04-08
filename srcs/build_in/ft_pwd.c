/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 01:17:01 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 18:34:13 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_pwd(int out)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	ft_putendl_fd(path, out);
	ft_free_line(&path);
	return (0);
}
