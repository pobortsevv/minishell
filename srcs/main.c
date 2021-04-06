/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:14:30 by sabra             #+#    #+#             */
/*   Updated: 2021/04/06 14:01:21 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <stdio.h>

t_sh shell;

void		ft_test_pr(t_list *first)
{
	t_list	*t;
	t_cmd	*ex;
	int		i;

	t=first; while (t != NULL)
	{
		i = 0;
		printf("инструкция:\n");
		ex = (t_cmd *)(t->content);
		printf("id = %d\n", ex->id);
		while (ex->args[i] != NULL)
		{
			printf("%s\n", (char *)(ex->args[i]));
			i++;
		}
		t = t->next;
	}
	return ;
}

int			init_command(t_cmd *cmd, char **envp)
{
	char 	*path;
	char 	*filename;
	int		result;

	//ft_putstr_fd("test", 0);
	result = 127;
	if ((ft_strcmp(cmd->args[0], "pwd")) == 0)
		return (ft_pwd());
	if ((ft_strcmp(cmd->args[0], "env")) == 0)
		return (ft_env(envp));
	if ((ft_strcmp(cmd->args[0], "echo")) == 0)
		return (ft_echo(cmd));
	if ((ft_strcmp(cmd->args[0], "exit")) == 0)
		return (ft_exit(cmd));
	path = ft_var_find("PATH", envp);
	if ((filename = ft_find_bin(cmd->args[0], path)))
		result = ft_exec_bin(cmd, filename, envp);
	if (path)
		ft_free_line(&path);
	return (result);
}

int				handle_cmd_not_found(char *name)
{
	ft_putstr_fd("minishell: ", shell.out_tmp);
	ft_putstr_fd(name, shell.out_tmp);
	ft_putendl_fd(": command not found", shell.out_tmp); 
	return (127);
}

char			**ft_exec_cmd(t_cmd *ar_cmd, char **env, int cmd_count)
{
	if (cmd_count > 1)
		return (ft_exec_pipe(ar_cmd, env, cmd_count));
	if (cmd_count == 1)
	{
		ft_stolower(ar_cmd[0].args[0]);
		if ((ft_strcmp(ar_cmd[0].args[0], "unset")) == 0)
			return (ft_unset(&ar_cmd[0], env));
		else if ((ft_strcmp(ar_cmd[0].args[0], "export")) == 0)
			return (ft_export(&ar_cmd[0], env));
		else if ((ft_strcmp(ar_cmd[0].args[0], "cd")) == 0)
			return (ft_cd(&ar_cmd[0], env));
		else
		{
			shell.status = init_command(&ar_cmd[0], env);
			if (shell.status == 127)
				handle_cmd_not_found(ar_cmd[0].args[0]);
		}
	}
	return (env);
}

int			main(int argc, char **argv, char **envp)
{
	char		*str;
	char		**evc=NULL;
	int			gnl;
	int 		res;
	t_hstr		*el;

	str = NULL;
	el = ft_make_el();
	//printf("el =<%s> \n", el->cmd);
	ft_bzero(&shell, sizeof(t_sh));
	evc = ft_copy_envp(envp);
	evc = ft_init_envp(evc);
	shell.in_tmp = dup(0);
	shell.out_tmp = dup(1);
	shell.term = ft_var_find("TERM", evc);
	shell.start = el;
	while (1)
	{
		//ft_putstr_fd("\033[0;35m\033[1mminishell> \033[0m", STDOUT);
		sig_init();
		//gnl = get_next_line(0, &str);
		gnl = ft_give_str(&str);
		if ((res = ft_check_str(str)) != 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token\n", STDERR);
			shell.status = 258;
			if (str)
				ft_free_line(&str);
		}
		else
		{
			if (gnl == 0 && *str == '\0')
				ft_exit(NULL);
			evc = ft_parser_shell(evc, str);
			if (!evc)
			{
				printf("Error with shell\n");
				break ;
			}
			if (str)
				ft_free_line(&str);
		}
	}
	ft_free_mat(evc);
	if (str)
		free(str);
	if (argc && argv[0] && envp[0])
		;
	return (0);
}
