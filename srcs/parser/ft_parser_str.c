/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:04:21 by mlaureen          #+#    #+#             */
/*   Updated: 2021/04/07 15:42:18 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_dollar_c(char *str, char **temp, int *i, int *j)
{
	while (str[*i] != '\0' && str[(*i) - 1] != 92 && str[*i] != ' '
			&& str[*i] != 34 && str[*i] != 39 && str[*i] != '$'
			&& str[*i] != '=')
	{
		(*temp)[*j] = str[(*i)];
		(*j)++;
		(*i)++;
	}
	return ;
}

char		*ft_dollar(char *str, int *i, char **envp)
{
	char	*res;
	char	*temp;
	int		j;

	j = 0;
	res = NULL;
	temp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	(*i)++;
	ft_dollar_c(str, &temp, i, &j);
	temp[j] = '\0';
	if (temp[0] != '\0' && (res = ft_var_find(&temp[0], envp)) == NULL)
	{
		res = (char *)malloc(sizeof(char));
		res[0] = '\0';
	}
	if (temp[0] == '\0')
	{
		res = (char *)malloc(sizeof(char) * 2);
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

static char	**init_ft_make_norm(char **ar, int *i, int *j, char ***res)
{
	int		len;

	(*i) = 0;
	(*j) = 0;
	len = ft_lenarray(ar);
	if (len <= 0
			|| !((*res) = (char **)malloc(sizeof(char *) * len + 1)))
		return (NULL);
	(*res)[len] = NULL;
	(*res)[0] = NULL;
	return (*res);
}

char		**ft_make_norm(char **ar, int *in, int *out, char **envp)
{
	char	**res;
	int		flag;
	int		i;
	int		j;

	init_ft_make_norm(ar, &i, &j, &res);
	while (ar[i] != NULL)
	{
		flag = 0;
		if (ar[i][0] == '<' || ar[i][0] == '>')
			ft_in_out(ar[i], in, out);
		else
			res[j++] = ft_res_arg(ar[i], &flag, envp);
		i++;
	}
	if (res[0] == NULL)
		return ((ft_parser_free2(res)));
	while (j <= i)
		res[j++] = NULL;
	return (res);
}
