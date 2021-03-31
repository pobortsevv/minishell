/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 21:45:13 by sabra             #+#    #+#             */
/*   Updated: 2021/03/31 18:59:21 by sabra            ###   ########.fr       */
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
	char *path;
	char *filename;

	path = ft_var_find("PATH", envp);
	if ((ft_strcmp(cmd->args[0], "pwd")) == 0)
		return (ft_pwd(cmd->out));
	if ((ft_strcmp(cmd->args[0], "env")) == 0)
		return (ft_env(envp, cmd->out));
	if ((ft_strcmp(cmd->args[0], "echo")) == 0 || (ft_strcmp(cmd->args[0], "echo\"\"")) == 0 || (ft_strcmp(cmd->args[0], "echo\'\'")) == 0)
		return (ft_echo(cmd));
	if ((ft_strcmp(cmd->args[0], "exit")) == 0)
		return (ft_exit(cmd));
	else if ((filename = ft_find_bin(cmd->args[0], path)))
		return (ft_exec_bin(cmd, filename, envp));
	if (path)
		ft_free_line(&path);
	return (127);
}

char			**ft_exec_cmd(t_cmd *ar_cmd, char **env, int cmd_count)
{
	//if (cmd_count > 1)
		//return (ft_exec_pipe(ar_cmd, env, cmd_count));
	if (cmd_count == 1)
	{
		ft_stolower(ar_cmd[0].args[0]);
		if ((ft_strcmp(ar_cmd[0].args[0], "unset")) == 0)
			env = ft_unset(&ar_cmd[0], env);
		else if ((ft_strcmp(ar_cmd[0].args[0], "export")) == 0)
			env = ft_export(&ar_cmd[0], env);
		else if ((ft_strcmp(ar_cmd[0].args[0], "cd")) == 0)
			env = ft_cd(&ar_cmd[0], env);
		else
			shell.status = init_command(&ar_cmd[0], env);
		if (shell.status == 127)
		{
			ft_putstr_fd("minishell: ", ar_cmd[0].out);
			ft_putstr_fd(ar_cmd[0].args[0], ar_cmd[0].out);
			ft_putendl_fd(": command not found", ar_cmd[0].out); 
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

	str = NULL;
	ft_bzero(&shell, sizeof(t_sh));
	evc = ft_copy_envp(envp);
	evc = ft_init_envp(evc);
	shell.in_tmp = dup(0);
	sig_init();
	while (1)
	{
		ft_printf("minishell> ");
		gnl = get_next_line(0, &str);
		if ((res = ft_check_str(str)) != 0)
		{
			printf("minishell: syntax error near unexpected token (%d)\n", res);
			if (str)
				free (str);
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
				free(str);
		}
	}
	ft_free_mat(evc);
	if (str)
		free(str);
	if (argc && argv[0] && envp[0])
		;
	return (0);
}
