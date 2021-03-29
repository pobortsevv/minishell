/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:53:39 by sabra             #+#    #+#             */
/*   Updated: 2021/03/29 11:47:58 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_exec_bin(t_cmd *cmd, char *filename, char **ev)
{
	pid_t	pid;
	int	status;
	
	pid = fork();
	if (pid == 0)
		execve(filename, &cmd->args[0], ev);
	else
		wait(&status);
	return (1);
}