/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:51:39 by sabra             #+#    #+#             */
/*   Updated: 2021/03/15 10:33:46 by mlaureen         ###   ########.fr       */
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
# define SYM " ><"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
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
	DOUBLE_QUOTE, 		// "
	SLASH_1 = 10,
	SLASH_2 = 11,
	END_ARRAY = 12,
	TAIL = 13,
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
int				ft_parser_shell(char **envp, char *str);
t_cmd			*ft_new_parser_cmd(char *cmd); //!!!!
char			**ft_split_cmd(char const *s, char c);
char			**ft_split_arg(char const *s, char *c);
int				ft_lenarray(char **cmd);
t_cmd			*ft_make_array_t_cmd(char **cmd_pipe);
//char			***ft_make_array_cmd(char **cmd_pipe);

/*
 * Commands funcs :)
 */
int			ft_pwd(void);
int			ft_env(char **env);
int			ft_export(t_cmd *cmd, char **env);
int			ft_cd(t_cmd *cmd);
int			ft_exit(t_cmd *cmd, t_list *list);


/*
 * test funcs :)
 */
void	ft_m_test_pr(t_list *first);
void	ft_print_array_2(char ** arr);
#endif
