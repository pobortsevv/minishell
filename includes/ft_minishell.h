/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:48:26 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/02 10:35:45 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL
enum			e_parser
{
	NOTHING	=0,
	SEMICOLON    		// ;
	PIPE,				// |
	REDIRECTING_OUT, 	// >
	REDIRECTING_IN,	 	// <
	APPENDIG_OUT,		// >>
	AND,				// &&
	OR,					// ||
	PATH,				// у команды есть путь - не надо использовать $PATH 				
	ERROR = 10,
};
typedef struct
{
	char	*comand;
	char	**arg;
	int		flag; // устанавливаю биты - e_parser,  если найду, в начале обязательно занулить
}			t_command;

#endif
