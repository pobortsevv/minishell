/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:04:21 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/20 13:07:16 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include  <stdio.h>

// проверка символа и установка флагов
// 	если " ' -  то в итоговой строке их не должно быть (e'h'c"o"  == echo)
// 	если:
//		export ec="echo"
//		$ec tar
//		"$ec" r
//		рабочие варианты
// 	если \ - то в итоговой строке его нет (e\cho == echo), но  "e\cho" - ошибка - e\cho 
// 	если $NAME - то замена 

int			ft_is(char const *s, int *flag, int *i)
{
	int		ret;

	ret = 1;
//	printf("FIRST: checkbit(flag, SINGLE_Q)=%zu\n", checkbit(*flag, SINGLE_Q));
	if ((checkbit(*flag, SLASH_1) && checkbit(*flag, SLASH_2)) ||
			!checkbit(*flag, SLASH_1))
	{
		if (checkbit(*flag, SLASH_2))
		{
			*flag = switchbit(*flag, SLASH_1);
			*flag = switchbit(*flag, SLASH_2);
		}
		if (!(checkbit(*flag, SINGLE_Q)) && s[0] == 92 && (*i)++)
			*flag = setbit(*flag, SLASH_1);
		else if (s[*i] == 39  && s[(*i) + 1] != 39) // else
		{
	//		printf("FFF\n");
			(*i)++;
			*flag = switchbit(*flag, SINGLE_Q);
		}
		else if (s[*i] == 39 && s[(*i) + 1] == 39)
			(*i) += 2;
		else if (!(checkbit(*flag, SINGLE_Q)) &&  //else
				(s[*i] == '"' && s[(*i) + 1] != '"'  && (*i)++))
			*flag = switchbit(*flag, DOUBLE_Q);
		else if (!(checkbit(*flag, SINGLE_Q)) &&
				(s[*i] == '"' && s[(*i) + 1] == '"'))
			(*i) += 2;
	}
	else if (checkbit(*flag, SLASH_1))
		*flag = setbit(*flag, SLASH_2);
//	printf("checkbit(flag, SINGLE_Q)=%zu\n", checkbit(*flag, SINGLE_Q));
//	printf("str=<%c>\n", s[*i]);
//	read (0,0,1);
	return (ret);
}

// перешагиваем через символ, если он равен 
//  ' - установлен флаг SINGLE_Q
//  " - установлен флаг DOUBLE_Q - TODO переделать, если " - то обработать $
//  символ после \  -  установлен флаг SLASH_2
//  усли не установлен SINGLE_Q, DOUBLE_Q и встретили обратный слеш
//  	- то при echo \ - пропускают,
//  	если же это имя файла - оставляем.
//
/*
static void	ft_skip(char const **s, int *flag)
{
	*flag = 0;
	while (**s && ft_isntend_split(*s, flag) &&
			&& (checkbit(*flag, SINGLE_Q) || checkbit(*flag, DOUBLE_Q) ||
				checkbit(*flag, SLASH_2)))))
		(*s)++;
	return ;
}
*/
//возвраœœœœщаем 1 если флаг = SINGLE_Q, DOUBLE_Q, SLASH_2
//TODO надо выделить  обработку " - проверку $
/*
static int	ft_check_flag(int flag)
{
	int		res;

	res = 0;
	res = (checkbit(flag, SINGLE_Q) || checkbit(flag, DOUBLE_Q) ||
			checkbit(flag, SLASH_2));
	return (res);
}
*/
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
	// printf("найти значение переменной %s\n", &temp[1]);
	//  получить значение переменной
	//  res = ft_giv(&temp[1]);
	res = (char *)malloc (2);
	res[0] = 'a';
	res[1] = '\0';
	free(temp);
	return (res);
}

static char	*ft_res0(char *str, int *flag)
{
	char	*res;
	char	*temp;
	char	*t1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	res[ft_strlen(str)] = '\0';
	res[0] = '\0';
	while (str[i] != '\0')
	{
		ft_is(str, flag, &i);
//		printf("после проверки: s[%d]=%c\n", i, str[i]);  
		if (str[i] != '\0' && (!(checkbit(*flag, SINGLE_Q)))
				&& (!checkbit(*flag, SLASH_2)) && str[i] == '$')
		{
			temp = ft_dollar(str, &i, flag);
			res[j] = '\0';
			t1 = res;
			res = ft_strjoin(res, temp);
			free(t1);
			free(temp);
			j = ft_strlen(res);
		}
		if (str[i] != '\0')
		//if (str[i] != '\0' && (!(checkbit(*flag, SINGLE_Q)))
		//		&& (!checkbit(*flag, SLASH_2)))
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}

	res[j] = '\0';
	return (res);
}

char		**ft_parser_str(t_cmd ar)
{
	char	**res;

	res = NULL;
	if (ar.len_args <= 0
			|| !(res = (char **)malloc(sizeof(char *) * ar.len_args + 1)))
		return (NULL);
	res[ar.len_args] = NULL;
	// Проверяю 0-й элемент - команду - это путь или просто имя?
	// проверить ", например 'e'c"h"o tat  => echo tat
	res[0] = ft_res0(ar.args[0], &ar.id);
	printf("command =%s\n", res[0]);
//	res[0] = malloc(2);
//	res[0][0] = 't';
//	res[0][1] = '\0';
	res[1] = NULL;

/*
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
	*/
	//вернем массив аргументов для команды и измененный in и out у структуры
	return (res);
}
