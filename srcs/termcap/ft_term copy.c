/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 07:44:59 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/04 13:30:34 by mlaureen         ###   ########.fr       */
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

void	ft_move_left_clear(void)
{
	buffer = buf;
	tputs(tgoto(tgetstr("ch", &buffer), 0, 0), 1, ft_putint);
	tputs(tgetstr("cd", &buffer), 1, ft_putint);
	buffer = buf;
	bzero(buffer, 100);
	write(1, "minishell: ", 11); 
	return ;
}

int		ft_read_t(char **str, t_hstr *history, t_hstr *element)
{
	char	*s;
	int		l;
	t_hstr	*now;

	now = history;
	s = (char *)malloc(sizeof(char) * 256);
	*(str[0]) = '\0';
	s[0] = '\0';
	while (strcmp(s, "\n"))
	{
		bzero(s, 256);
		l= read(0, s, 100);
		/*
		if (!strcmp(s, "\e[A"))
		{
			ft_move_left_clear();
			bzero(s, 256);
			if (now->before != NULL)
				now = now->before;
			free(element->cmd);
			element->cmd = (char *)malloc(sizeof(char) * strlen(now->cmd) + 1);
			strlcpy(element->cmd, now->cmd, strlen(now->cmd));
			write(1,"up", 2);
			write(1, element->cmd, strlen(element->cmd));
		}
		else if (!strcmp(s, "\e[B"))
		{
			ft_move_left_clear();
			bzero(s, 256);
			write(1,"down", 4);
		}
		else
		*/
		{

			write(1, s, 1);
			s[1] = '\0';
			if (s[0] != '\n')
				ft_strlchar(element->cmd, s[0], 1024);
		//		ft_strlchar(*str, s[0], 1024);
		}
	}
	strlcpy(*str, element->cmd, 1024);
//	printf("*str=%s\n", *str);
//	printf("elm=%s\n",element->cmd);
//	write(1, "1\n", 2);
//	write(1, *str, strlen(*str));
	free(s);
	return (0);
}

t_hstr	ft_make_el(void)
{
	t_hstr	one;

	one.cmd = (char *)malloc(sizeof(char) *1024);
	one.cmd[0] = '\0';
	one.after = NULL;
	one.before = NULL;
	return (one);
}

void 	ft_add_before(t_hstr **lst, t_hstr *new)
{
//	write(1, (*lst)->cmd, 1);
//	write(1, " before\n", 8);
	printf("до  add lst=%s, new=%s\n", (*lst)->cmd,  new->cmd);
	new->after = *lst;
	(*lst)->before = new;
	printf("address new  %p\n", new);
	printf("address *lst %p\n", *lst);
	printf("присвоил address new->after  %p\n", new->after);
	printf("address new->before %p\n", new->before);
	(*lst) = new;
	printf("address new  %p\n", new);
	printf("address new->after  %p\n", new->after);
	printf("address new->before %p\n", new->before);
	printf("address *lst %p\n", *lst);
	printf("address lst->after  %p\n", (*lst)->after);
	printf("address lst->before %p\n", (*lst)->before);

	printf("gockt  add lst=%s, new=%s\n", (*lst)->cmd,  new->cmd);
//	write(1, (*lst)->cmd, 1);
//	write(1, " after\n", 7);
	return;
}

int		ft_read_term(char **str, t_hstr **history)
{
	char			*termtype = "xterm-256color";
	struct termios 	term;
	struct termios 	pre_term;
	t_hstr			element;
	t_hstr			*temp;

	write(1, "minishell: ", 11); 
	(*str) = (char *)malloc(sizeof(char) *1024);
	if (tgetent(0, termtype) < 0)
		return (-1);
	if (tcgetattr(0, &term) < 0) // получить атрибуты терминала
		return (-1);
	pre_term = term;
	term.c_lflag &= ~(ECHO); // если установлен отображать вводимые символы
	term.c_lflag &= ~(ICANON);// усли установлен запустить канонический режим. 
//	term.c_cc[VMIN] = 1; // количество символов ждать Саша сказал - лишнее
	term.c_cc[VTIME] = 0; // 0 - не ждать read
	if (tcsetattr(0, TCSANOW, &term) < 0)
		return (-1);
	//создать новый элемент t_hstr и передать его в ft_read_t)
	element = ft_make_el();
	printf("после создания элемента: str =%s, *history.cmd =%s, elment.cmd = %s\n", *str, (*history)->cmd, element.cmd);
	ft_read_t(str, *history,  &element);
	printf("после чтения: str =%s, *history.cmd =%s, elment.cmd = %s\n", *str, (*history)->cmd, element.cmd);
	if (element.cmd[0] != '\0')
	{
		printf("доб эл-т после чтения (%s)\n", element.cmd);
		printf("в лист c последней командой (%s)\n", (*history)->cmd);
		ft_add_before(history, (&element));
		temp = *history;
		while (temp->after != NULL)
		{
			printf("0 = <%s>\n", (temp)->cmd);
			temp = (*history)->after;
			read(0,0,1);
			//iprintf("1 = <%s>\n", (temp)->cmd);
		}
	}
	if (tcsetattr(0, TCSANOW, &pre_term) < 0)
		return(-1);
	return (1);
}



int	main()
{
	char	*str;
	int		i=0;
	t_hstr 	history;
	t_hstr	*start;

	start = &history;
	history.cmd = (char *)malloc(sizeof(char) *1024);
	history.cmd[0] = '\0';
	history.after = NULL;
	history.before = NULL;
	while (i < 4)
	{
		ft_read_term(&str, &start);
		i++;
		write(1, "result: ",9);
		write(1, str, strlen(str));
		write(1, "\n", 1);
	}
	while (start != NULL)
	{
		printf("%s\n", (*start).cmd);
		start = start->before;
	}
	write(1, "\nEND\n", 4);
	//TODO очистить start
	return (0);
}
