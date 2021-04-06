/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 07:44:59 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/06 13:04:17 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

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
	if (tcgetattr(0, &term) < 0)// получить атрибуты терминала
		return (el);
	pre_term = term;
	term.c_lflag &= ~(ECHO); // если установлен отображать вводимые символы
	term.c_lflag &= ~(ICANON);// усли установлен запустить канонический режим
	term.c_cc[VTIME] = 0; // 0 - не ждать read
	if (tcsetattr(0, TCSANOW, &term) < 0)
		return (el);
	write(1, "minishell: ", 11);
	el = ft_read_t(history);
	if (tcsetattr(0, TCSANOW, &pre_term) < 0)
		return (el);
	return (el);
}

int			main(void)
{
	int				i;
	t_hstr			*start;
	t_hstr			*el;
	t_hstr			*temp;

	i = 0;
	el = ft_make_el();
	start = el;
	while (i < 4)
	{
		el = ft_read_term(&start);
		i++;
	}
	printf("лист командЖ\n");
	temp = start;
	while (temp != NULL)
	{
		printf("<%s>\n", (temp)->cmd);
		temp = (temp)->after;
	}
	write(1, "\nEND\n", 4);
	temp = start;
	while (temp != NULL)
	{
		free(temp->cmd);
		temp = (temp)->after;
	}
	return (0);
}
