/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:48:26 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/05 13:44:28 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7
# define FD_ERR 2
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft/libft.h"
# include "../libbitop/libbitop.h"

enum			e_parser
{
	SEMICOLON = 0,    	// ;
	PIPE,				// |
	REDIRECTING_OUT, 	// >
	REDIRECTING_IN,	 	// <
	APPENDIG_OUT,		// >>
	AND,				// &&
	OR,					// ||
	PATH,				// у команды есть путь - не надо использовать $PATH 		
	SINGLE_QUOTE, 		// '
	ERROR = 10,
};

enum			e_error
{
	OK = 0,
	PROBLEM_WITH_MALLOC,
};

typedef struct		s_sh
{
	char		*inst;
	t_list		*arg;
	int			flag; // устанавливаю биты - e_parser,  если найду, в начале обязательно занулить
}			t_sh;

// Загатовленная структура для команд, TODO реализовать парсинг с листом команд(структур команд)
// Пока вызов команд выполнен относительно вышеуказанной структуры.

typedef struct		s_cmd
{
	int	id;
	char	**args;
	int	in;
	int	out;
}			t_cmd;

/*
* Initialization. Create a copy: envp, declare null and void in the structures
*/
void			ft_init(char **argp, char **w_argp);
void			ft_set_sh(t_cmd *sh);

/*
 * Reading from std0 to str
 */
void			ft_read(char **str);

/*
 * Parsing str into sh structure
 */
t_list			ft_parser(char **envp, char *str);

/*
 * Commands funcs :)
 */
void			pwd(t_sh *sh, char **env);


/*
 * test funcs :)
 */
void	ft_test_pr(t_list *first);
#endif
