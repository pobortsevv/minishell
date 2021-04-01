/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 08:00:42 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/01 12:07:25 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_sckip_space(char *a, int *i)
{
	while (a[*i] == ' ')
		(*i)++;
	return ;
}

int			ft_write_append(char *a, int *out)
{
	int		f;
	int		i;
	char	*temp;

	i = 0;
	ft_sckip_space(a, &i);
	temp = ft_pars_name(&a[i]);
	if ((f = open(temp, O_WRONLY | O_APPEND | O_CREAT, 0666)) < 0)
		ft_parser_err_fd(&temp);
	if (*out < 0)
		close(f);
	else
	{
		if (*out != 1)
			close(*out);
		*out = f;
	}
	if (temp != NULL)
		free(temp);
	return (0);
}

int			ft_write_only(char *a, int *out)
{
	int		f;
	int		i;
	char	*temp;

	i = 0;
	ft_sckip_space(a, &i);
	temp = ft_pars_name(&a[i]);
	if ((f = open(temp, O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
		ft_parser_err_fd(&temp);
	if (*out < 0)
		close(f);
	else
	{
		if (*out != 1)
			close(*out);
		*out = f;
	}
	if (temp != NULL)
		free(temp);
	return (0);
}

int			ft_read_only(char *a, int *in)
{
	int		f;
	int		i;
	char	*temp;

	i = 0;
	ft_sckip_space(a, &i);
	temp = ft_pars_name(&a[i]);
	if ((f = open(temp, O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
		ft_parser_err_fd(&temp);
	if (*in < 0)
		close(f);
	else
	{
		if (*in != 0)
			close(*in);
		*in = f;
	}
	if (temp != NULL)
		free(temp);
	return (0);
}
