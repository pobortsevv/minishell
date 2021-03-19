/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:04:21 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/17 19:01:44 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

// проверка символа и установка флагов
int			ft_isntend_split(char const *s, int *flag)
{
	int		ret;

	ret = 1;
	if ((checkbit(*flag, SLASH_1) && checkbit(*flag, SLASH_2)) ||
			!checkbit(*flag, SLASH_1))
	{
		if (checkbit(*flag, SLASH_2))
		{
			*flag = switchbit(*flag, SLASH_1);
			*flag = switchbit(*flag, SLASH_2);
		}
		if (!(checkbit(*flag, SINGLE_Q)) && s[0] == '\\')
			*flag = setbit(*flag, SLASH_1);
		else if (s[0] == 39)
			*flag = switchbit(*flag, SINGLE_Q);
		else if (!(checkbit(*flag, SINGLE_Q)) && s[0] == '"')
			*flag = switchbit(*flag, DOUBLE_Q);
	}
	else if (checkbit(*flag, SLASH_1))
		*flag = setbit(*flag, SLASH_2);
	return (ret);
}

// перешагиваем через символ, если он равен 
//  ' - установлен флаг SINGLE_Q
//  " - установлен флаг DOUBLE_Q - TODO переделать, если " - то обработать $
//  символ после \  -  установлен флаг SLASH_2
//
static void	ft_skip(char const **s, int *flag)
{
	*flag = 0;
	while (**s && ft_isntend_split(*s, flag) &&
			&& (checkbit(*flag, SINGLE_Q) || checkbit(*flag, DOUBLE_Q) ||
				checkbit(*flag, SLASH_2)))))
		(*s)++;
	return ;
}

//возвращаем 1 если флаг = SINGLE_Q, DOUBLE_Q, SLASH_2
//TODO надо выделить  обработку " - проверку $

static int	ft_check_flag(int flag)
{
	int		res;

	res = 0;
	res = (checkbit(flag, SINGLE_Q) || checkbit(flag, DOUBLE_Q) ||
			checkbit(flag, SLASH_2));
	return (res);
}



char		**ft_split_cmd(char const *s, char c, size_t i, int flag)
{
	char	**result;

	i = 0;
	flag = 0;
	// TODO создать массив для отправки в команду, из стркутуры t_cmd, размер известен - 
	if (!s ||
			!(result = (char **)malloc(sizeof(char *) * (ft_count(s, c)) + 1)))
		return (NULL);
	//TODO цикл по массиву аргументов t_cmd
	while (*s)
	{
		// TODO обработать строку: >>      a.txt
		// проверяем первый и второй символ, если равны <, > то это 
		// надо открыть файл - в массив не заносим - обработка завершена 
		// изменяем в структуре дескрипторы
		while (*s && s[0] == c && ft_isntend_split(s, &flag))
			s++;

		//TODO обрабатываем слово по-символьно:
		// 1. убираем ' 
		// 2. убираем " - и обрабатываем $
		// 3. перешагиваем \символ
		//
		if (*s && ft_isntend_split(s, &flag) && (s[0] != c || (s[0] == c &&
			(ft_check_flag(flag)))))
		{
			// TODO записываем слово в массив для отправки в команду,
			// слово после удаления ', " и вставке $ПЕРЕМЕННАЯ
			if (!(result[i] = ft_create_word(s, c)))
			{
				ft_free_split(result, i);
				return (NULL);
			}
			i++;
		}
	}
	// TODO записываем NULL - во все невостребованные элементы массива для отправки в команду;
	// то есть те что уже исполнили >, >>, <
	result[i] = NULL;
	//вернем массив аргументов для команды и измененный in и out у структуры
	return (result);
}
