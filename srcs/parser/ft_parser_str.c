/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:04:21 by mlaureen          #+#    #+#             */
/*   Updated: 2021/03/26 07:32:09 by mlaureen         ###   ########.fr       */
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
			&& str[*i] != 34 && str[*i] !='$')
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
	i = 1;
	j = 1;
	len = ft_lenarray(ar);
	if (len <= 0
			|| !(res = (char **)malloc(sizeof(char *) * len + 1)))
		return (NULL);
	res[len] = NULL;
	res[0] = ft_res0(ar[0], &flag, envp);
	if (res[0] == NULL)
		return ((ft_parser_err_free2("comman not found (127)\n", res)));
	while (ar[i] != NULL)
	{
		flag = 0;
		if (ar[i][0] == '<' || ar[i][0] == '>')
			ft_in_out(ar[i], in, out);
		else
		{
			res[j] = ft_res_arg(ar[i], &flag, envp);
			j++;
		}
		i++;
	}
	while (j <= i)
	{
		res[j] = NULL;
		j++;
	}
	return (res);
}
