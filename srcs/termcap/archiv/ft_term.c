# include <term.h>
#include  <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char    buf[100];
char    *buffer;

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

int		ft_read(char **str, struct termios *term)
{
	int		l;
	char	*s;


	s = (char *)malloc(sizeof(char) * 256);
	*(str[0]) = '\0';
	s[0] = '\0';
	while (strcmp(s, "\n"))
	{
		l= read(0, s, 100);
		if (!strcmp(s, "\e[A"))
		{
			ft_move_left_clear();
			write(1,"up", 2);
		}
		else if (!strcmp(s, "\e[B"))
		{
			ft_move_left_clear();
			write(1,"down", 4);
		}
		else
		{
			write(1, (s), l);
			strlcpy((*str), s, 1024);
		}
	}
	write(1, "1\n", 2);
	write(1, *str, strlen(*str));
	free(s);
	return (0);
}

int		ft_read_term(char **str)
{
	char			*termtype = "xterm-256color";
	struct termios 	term;

	write(1, "minishell: ", 11); 
	(*str) = (char *)malloc(sizeof(char) *1024);
	if (tgetent(0, termtype) < 0)
		return (-1);
	if (tcgetattr(0, &term) < 0) // получить атрибуты терминала
		return (-1);
	term.c_lflag &= ~(ECHO); // если установлен отображать вводимые символы
	term.c_lflag &= ~(ICANON);// усли установлен запустить канонический режим. 
//	term.c_cc[VMIN] = 1; // количество символов ждать Саша сказал - лишнее
	term.c_cc[VTIME] = 0; // 0 - не ждать read
	if (tcsetattr(0, TCSANOW, &term) < 0)
		return (-1);
	ft_read(str, &term);
	return (1);
}


int	main()
{
	char	*str;

	ft_read_term(&str);
	write(1, "result :\n",9);
	write(1, str, strlen(str));
	return (0);
}
