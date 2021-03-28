/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 01:17:01 by sabra             #+#    #+#             */
/*   Updated: 2021/03/28 12:25:54 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_pwd(int out)
{
	char *path;
	
	path = getcwd(NULL, 0);
	if (!path)
		return (0);
	ft_putendl_fd(path, out);
	ft_free_line(&path);
	return (1);
}
