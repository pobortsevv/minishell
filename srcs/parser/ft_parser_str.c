/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:04:21 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/23 11:37:43 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include  <stdio.h>

// проверка символа и установка флагов
// 	Сделано: если " ' -  то в итоговой строке их не должно быть (e'h'c"o"  == echo)
// 	TODO если:
//		export ec="echo"
//		$ec tar
//		"$ec" r
//		рабочие варианты
// 	Сделано: если \ - то в итоговой строке его нет (e\cho == echo), но  "e\cho" - ошибка - e\cho 
// 	TODO если $NAME - то замена 

char	*ft_dollar (char *str, int *i, int *flag)
{
	char	*res;
	char	*temp;
	int		j;

	j = 0;
	temp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '<'
					&& str[*i] !='>')
	{
		temp[j] = str[(*i)];
		j++;
		(*i)++;
		ft_is(&str[*i], flag, i);
	}
	temp[j] = '\0';
	//printf("найти значение переменной %s\n", &temp[1]);
	//  получить значение переменной
	//  res = ft_giv(&temp[1]);
	res = (char *)malloc (10);
	res[0] = 'Z';
	res[1] = 'N';
	res[2] = 'A';
	res[3] = 'C';
	res[4] = 'H';
	res[5] = 'E';
	res[6] = 'N';
	res[7] = 'I';
	res[8] = 'E';
	res[9] = '\0';
	free(temp);
	return (res);
}

char		**ft_parser_str(t_cmd ar)
{
	char	**res;
	int		flag;
	int		i;

	res = NULL;
	flag = 0;
	i = 1;
	if (ar.len_args <= 0
			|| !(res = (char **)malloc(sizeof(char *) * ar.len_args + 1)))
		return (NULL);
	res[ar.len_args] = NULL;
	// Проверяю 0-й элемент - команду - это путь или  имя? - проврека вчодит ли в команду'/'
	// проверить ", например 'e'c"h"o tat  => echo tat
	res[0] = ft_res0(ar.args[0], &flag);
	if (flag)
		printf("Error: comand error\n");
	// TODO обработку ошибок - кавычки без пары
	
//	printf("command =%s\n", res[0]);
	res[1] = NULL;


	//TODO цикл по массиву аргументов t_cmd
/*	while (ar.args[i] != NULL)
	{
		res[i]= (char *)malloc(sizeof(char) * (ft_strlen (ar.args[i]) + 1));
		ft_strlcpy(res[i], ar.args[i], ft_strlen(ar.args[i]) + 1);
		i++;
	}
	*/
/*
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
	*/
	//вернем массив аргументов для команды и измененный in и out у структуры
	return (res);
}

char	**ft_make_norm(char **ar)
{
	int		len;
	char	**res;
	int		flag;
	int		i;

	flag = 0;
	i = 1;
	len = ft_lenarray(ar);
	if (len <= 0
			|| !(res = (char **)malloc(sizeof(char *) * len + 1)))
		return (NULL);
	res[len] = NULL;
	res[0] = ft_res0(ar[0], &flag);
	if (res[0] == NULL || flag)
		return ((ft_parser_err_free2("comman not found (127)\n", res)));
	while (ar[i] != NULL)
	{
		flag = 0;
		res[i] = ft_res_arg(ar[i], &flag);
		i++;
	}
	return (res);
}
