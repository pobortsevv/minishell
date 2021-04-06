/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_utilit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:53:34 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/06 14:04:29 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/ft_minishell.h"
#include "ft_minishell.h"

static void	ft_move_left_clear(int len)
{
	int		i;
	char	buf[100];
	char	*buffer;

	i = 0;
	buffer = buf;
	ft_bzero(buffer, 100);
	while (i < len)
	{
		tputs(tgetstr("kb", &buffer), 1, ft_putint);
		buffer = buf;
		ft_bzero(buffer, 100);
		i++;
	}
	buffer = buf;
	ft_bzero(buffer, 100);
	tputs(tgetstr("cd", &buffer), 1, ft_putint);
	buffer = buf;
	bzero(buffer, 100);
	return ;
}

static void	term_up(char **s, t_hstr **now, t_hstr **el)
{
	ft_move_left_clear(ft_strlen((*el)->cmd));
	ft_bzero((*s), 256);
	if ((*now)->after != NULL && ((*now)->after)->cmd != '\0')
		(*now) = (*now)->after;
	(*el)->cmd[0] = '\0';
	if ((*el) != (*now))
		ft_strlcpy((*el)->cmd, (*now)->cmd, 1024);
	write(1, (*el)->cmd, ft_strlen((*el)->cmd));
	return ;
}

static void	term_down(char **s, t_hstr **now, t_hstr **el)
{
	ft_move_left_clear(ft_strlen((*el)->cmd));
	ft_bzero((*s), 256);
	if ((*now)->before != NULL)
		(*now) = (*now)->before;
	(*el)->cmd[0] = '\0';
	if ((*el) != (*now))
		ft_strlcpy((*el)->cmd, (*now)->cmd, 1024);
	write(1, (*el)->cmd, ft_strlen((*el)->cmd));
	return ;
}

static void	in_cycle_term(char **s, t_hstr **now, t_hstr **el)
{
	int		l;

	ft_bzero((*s), 256);
	l = read(0, (*s), 100);
	if (!ft_strcmp((*s), "\e[A"))
		term_up(s, now, el);
	else if (!ft_strcmp((*s), "\e[B"))
		term_down(s, now, el);
	else if (!ft_strcmp((*s), "\t"))
		ft_bzero((*s), 256);
	else if (!ft_strcmp((*s), "\n") && (*el)->cmd[0] == '\0')
		ft_bzero((*s), 256);
	else
	{
		write(1, (*s), 1);
		(*s)[1] = '\0';
		if ((*s)[0] != '\n')
			ft_strlchar((*el)->cmd, (*s)[0], 1024);
	}
	return ;
}

t_hstr		*ft_read_t(t_hstr **history)
{
	char	*s;
	t_hstr	*now;
	t_hstr	*el;

	if ((*history)->cmd != '\0')
	{
		el = ft_make_el();
		ft_add_before(history, el);
	}
	else
		el = *history;
	now = *history;
	s = (char *)malloc(sizeof(char) * 256);
	s[0] = '\0';
	while (ft_strcmp(s, "\n"))
		in_cycle_term(&s, &now, &el);
	free(s);
	return (el);
}
