/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:51:39 by sabra             #+#    #+#             */
/*   Updated: 2021/03/18 10:32:15 by sabra            ###   ########.fr       */
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
	SINGLE_Q, 		// '
	DOUBLE_Q, 		// "
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
	int		len_args;
	int	in;
	int	out;
}			t_cmd;

/*
* Initialization. Create a copy: envp, declare null and void in the structures
*/
char			**ft_copy_envp(char **ev);

/*
 * Reading from std0 to str
 */
void			ft_read(char **str);

/*
 * Parsing str into t_cmd structure
 */
int				ft_parser_shell(char **envp, char *str);
char			**ft_split_cmd(char const *s, char c, size_t i, int flag);
char			**ft_split_arg(char *s, char *c, size_t i, int flag);
int				ft_isntend_split(char const *s, int *flag);
int				ft_free_split(char **result, size_t last);
void			ft_check_d(const char *s, int *d, int *flag, int *i);
void			ft_check_d_v1(const char *s, int *d, int *flag);
void			ft_check_d_less(const char s, char *c,  int *d, int *flag);
int				ft_check_tail(int flag);
int				ft_lenarray(char **cmd);
void			free_array_shell(char **ar);
void			free_array_shell_2(char ***ar);
void			free_t_cmd(t_cmd *ar_t_cmd, int len);

/*
 * Error
 */
char			**ft_parser_er2(char *error);
char			*ft_parser_er1(char *error);

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
void		ft_m_test_pr(t_list *first);
void		ft_print_array_2(char **arr);
void		ft_print_array_3(char ***arr);
void		ft_print_array_t_cmd(t_cmd *ar_t_cmd, int len);
#endif
