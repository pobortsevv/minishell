/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:48:26 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/03 14:35:22 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
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
	ERROR = 10,
};
enum		e_error
{
	OK = 0,
	PROBLEM_WITH_MALLOC,
};
typedef struct
{
	char		*inst;
	t_list		*arg;
	int			flag; // устанавливаю биты - e_parser,  если найду, в начале обязательно занулить
}				t_command;

/*
* Initialization. Create a copy: envp, declare null and void in the structures
*/
void			ft_init(t_command *sh, char **argp, char **w_argp);
void			ft_set_sh(t_command *sh);

/*
 * Reading from std0 to str
 */
void			ft_read(char **str);

/*
 * Parsing str into sh structure
 */
void			ft_parser(t_command *sh, char **envp, char *str);
#endif
