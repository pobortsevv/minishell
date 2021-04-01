/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:04:21 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/01 09:55:37 by mlaureen         ###   ########.fr       */
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

char	*ft_dollar (char *str, int *i, char **envp)
{
	char	*res;
	char	*temp;
	int		j;

	j = 0;
	res = NULL;
	temp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	(*i)++;
	while (str[*i] != '\0' && str[(*i) - 1] != 92 && str[*i] != ' '
			&& str[*i] != 34 && str[*i] != 39 && str[*i] != '$')
	{
		temp[j] = str[(*i)];
		j++;
		(*i)++;
	}
	temp[j] = '\0';
	if (temp[0] != '\0' && (res = ft_var_find(&temp[0], envp)) == NULL)
	{
		res = (char *)malloc(sizeof(char));
		res[0] = '\0';
	}
	if  (temp[0] == '\0')
	{
		res = (char *)malloc(sizeof(char)*2);
		res[0] = '$';
		res[1] = '\0';
	}
	free(temp);
	return (res);
}

static int	ft_in_out(char *a, int *in, int *out)
{
	int		i;

	i = 0;
	if (a[0] == '>' && a[1] == '>')
		return (ft_write_append(&a[2], out));
	else if (a[0] == '>')
		return (ft_write_only(&a[1], out));
	else
		return (ft_read_only(&a[1], in));
	return (0);
}

char	**ft_make_norm(char **ar, int *in, int *out, char **envp)
{
	int		len;
	char	**res;
	int		flag;
	int		i;
	int		j;

	flag = 0;
	i = 0;
	j = 0;
	len = ft_lenarray(ar);
	if (len <= 0
			|| !(res = (char **)malloc(sizeof(char *) * len + 1)))
		return (NULL);
	res[len] = NULL;
	res[0] = NULL;
	//printf("%p; %p\n", &res[0], &res[len]);
	//printf("%p\n", res);
	//res[0] = ft_res0(ar[0], &flag, envp);
	//if (res[0] == NULL)
	//	return ((ft_parser_err_free2("comman not found (127)\n", res)));
	while (ar[i] != NULL)
	{
		flag = 0;
		if (ar[i][0] == '<' || ar[i][0] == '>')
			ft_in_out(ar[i], in, out);
		else
		{
			if (j == 0)
				res[0] = ft_res_arg(ar[i], &flag, envp);
				//res[0] = ft_res0(ar[i], &flag, envp);
			else 
				res[j] = ft_res_arg(ar[i], &flag, envp);
			j++;
		}
		i++;
	}
	if (res[0] == NULL)
		return ((ft_parser_free2(res)));
	while (j <= i)
	{
		res[j] = NULL;
		j++;
	}
//	printf("нормированный массив\n");
//	ft_print_array_2(res);
	return (res);
}
