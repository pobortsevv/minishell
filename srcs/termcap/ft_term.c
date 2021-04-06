/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 07:44:59 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/06 10:33:02 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"
# include <term.h>
#include  <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char    buf[100];
char    *buffer;

size_t	ft_strlchar(char *dst, const char src, size_t dstsize);

int         ft_putint(int c)
{
   return (write(1, &c, 1));
}

t_hstr	*ft_make_el(void)
{
	t_hstr	*one;

	if (!(one = (t_hstr *)malloc(sizeof(t_hstr))))
		return (NULL);
	one->cmd = (char *)malloc(sizeof(char) *1024);
	one->cmd[0] = '\0';
	one->after = NULL;
	one->before = NULL;
	return (one);
}
void	ft_move_left_clear(int len)
{
	int	i;

	i = 0;
	buffer = buf;
	bzero(buffer, 100);
//	tputs(tgetstr("cm", &buffer), 1, ft_putint);
//	tputs(tgoto(tgetstr("ed", &buffer), 0, 0), 1, ft_putint);
//	tputs(tgetstr("kS", &buffer), 1, ft_putint);
//	tputs(tgoto(tgetstr("ch", &buffer), 0, 0), 1, ft_putint);
//	tputs(tgetstr("cd", &buffer), 1, ft_putint);
	while (i < len)
	{
		tputs(tgetstr("kb", &buffer), 1, ft_putint);
		buffer = buf;
		bzero(buffer, 100);
		i++;
	}
	buffer = buf;
	bzero(buffer, 100);
	tputs(tgetstr("cd", &buffer), 1, ft_putint);
	buffer = buf;
	bzero(buffer, 100);
//	write(1, "minishell: ", 11); 
	return ;
}

void 	ft_add_before(t_hstr **lst, t_hstr *new)
{
	new->after = *lst;
	(*lst)->before = new;
	(*lst) = new;
	return;
}
//t_hstr		*ft_read_t(char **str, t_hstr *history, t_hstr *element)
t_hstr		*ft_read_t(char **str, t_hstr **history)
{
	char	*s;
	int		l;
	t_hstr	*now;
	t_hstr	*el;

//	tputs(tgetstr("sc", &buffer), 1, ft_putint);
//	write(1, "minishell: ", 11); 
	if ((*history)->cmd != '\0')
	{
		el = ft_make_el();
		ft_add_before(history, el);
	}
	else
		el = *history;
	now = *history;
	s = (char *)malloc(sizeof(char) * 256);
	*(str[0]) = '\0';
	s[0] = '\0';
	while (strcmp(s, "\n"))
	{
		bzero(s, 256);
		l= read(0, s, 100);
		if (!strcmp(s, "\e[A"))
		{
			ft_move_left_clear(strlen(el->cmd));
			bzero(s, 256);
			if (now->after !=NULL && (now->after)->cmd != '\0')
				now = now->after;
			el->cmd[0] = '\0';
			if (el != now)
				strlcpy(el->cmd, now->cmd, 1024);
			write(1, el->cmd, strlen(el->cmd));
		}
		else if (!strcmp(s, "\e[B"))
		{
			ft_move_left_clear(strlen(el->cmd));
			bzero(s, 256);
			if (now->before != NULL)
				now = now->before;
			el->cmd[0] = '\0';
			if (el != now)
				strlcpy(el->cmd, now->cmd, 1024);
			write(1, el->cmd, strlen(el->cmd));
		}
		else
		{

			write(1, s, 1);
			s[1] = '\0';
			if (s[0] != '\n')
				ft_strlchar(el->cmd, s[0], 1024);
		}
	}
	free(s);
	return (el);
}


t_hstr		*ft_read_term(char **str, t_hstr **history)
{
	char			*termtype = "xterm-256color";
	struct termios 	term;
	struct termios 	pre_term;
	t_hstr			*element;
	t_hstr			*temp;
	t_hstr			*el;

//	write(1, "minishell: ", 11); 
	(*str) = (char *)malloc(sizeof(char) *1024);
	if (tgetent(0, termtype) < 0)
		return (el);
	if (tcgetattr(0, &term) < 0) // получить атрибуты терминала
		return (el);
	pre_term = term;
	term.c_lflag &= ~(ECHO); // если установлен отображать вводимые символы
	term.c_lflag &= ~(ICANON);// усли установлен запустить канонический режим. 
	term.c_cc[VTIME] = 0; // 0 - не ждать read
	if (tcsetattr(0, TCSANOW, &term) < 0)
		return (el);
//	tputs(tgetstr("sc", &buffer), 1, ft_putint);
//	cur_v = tgetstr("rc", &buffer);
//	printf("<%s>\n", cur_v);
//	buffer = buf;
//	bzero(buffer, 100);
	write(1, "minishell: ", 11); 
//	tputs(tgetstr("rs", &buffer), 1, ft_putint);
	element = ft_make_el();
	el = ft_read_t(str, history);
	if (tcsetattr(0, TCSANOW, &pre_term) < 0)
		return(el);
	return (el);
}



int	main()
{
	char	*str;
	int		i=0;
	t_hstr	*start;
	t_hstr	*el;
	t_hstr	*temp;

	el = ft_make_el();
	start = el;
	while (i < 4)
	{
		el = ft_read_term(&str, &start);
		i++;

	}
	printf("лист командЖ\n");
	temp = start;
	while (temp->cmd[0] != '\0')
	{
		printf("<%s>\n", (temp)->cmd);
		temp = (temp)->after;
	}
	write(1, "\nEND\n", 4);
	//TODO очистить лист
	return (0);
}
