/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 07:44:59 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/07 09:29:00 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			ft_putint(int c)
{
	return (write(1, &c, 1));
}

t_hstr		*ft_make_el(void)
{
	t_hstr			*one;

	if (!(one = (t_hstr *)malloc(sizeof(t_hstr))))
		return (NULL);
	one->cmd = (char *)malloc(sizeof(char) * 1024);
	one->cmd[0] = '\0';
	one->after = NULL;
	one->before = NULL;
	return (one);
}

void		ft_add_before(t_hstr **lst, t_hstr *new)
{
	new->after = *lst;
	(*lst)->before = new;
	(*lst) = new;
	return ;
}

t_hstr		*ft_read_term(t_hstr **history)
{
	struct termios	term;
	struct termios	pre_term;
	t_hstr			*el;

	el = NULL;
//	if (tgetent(0, shell.term) < 0)
	if (tgetent(0, "xterm-256color") < 0)
		return (el);
	if (tcgetattr(0, &term) < 0)
		return (el);
	pre_term = term;
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) < 0)
		return (el);
	ft_putstr_fd("\033[0;35m\033[1mminishell> \033[0m", STDOUT);
	el = ft_read_t(history);
	if (tcsetattr(0, TCSANOW, &pre_term) < 0)
		return (el);
	return (el);
}

int			ft_give_str(char **str)
{
	t_hstr			*el;

	el = ft_read_term(&(shell.start));
	if (el == NULL)
	{
		printf("ERRER in termcap\n");
		return (0);
	}
	(*str) = (char *)malloc(sizeof(char) * ft_strlen(shell.start->cmd) + 2);
	ft_strlcpy((*str), (shell.start->cmd), ft_strlen(shell.start->cmd) + 1);
	return (ft_strlen(shell.start->cmd));
}
