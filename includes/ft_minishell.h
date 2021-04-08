/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:51:39 by sabra             #+#    #+#             */
/*   Updated: 2021/04/08 19:25:51 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ECHO 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7
# define FD_ERR 2
# define SYM " ><"
# define ADD_VALUE 3
# define CHANGE_VALUE 4
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <term.h>
# include "../libft/libft/libft.h"
# include "../libbitop/libbitop.h"

typedef struct	s_hstr
{
	char			*cmd;
	struct s_hstr	*after;
	struct s_hstr	*before;
}				t_hstr;

typedef struct	s_sh
{
	char			*term;
	char			*home;
	int				status;
	int				sig_flag;
	int				in_tmp;
	int				out_tmp;
	t_hstr			*start;
}				t_sh;

typedef struct	s_word
{
	int				i;
	int				d;
	int				flag;
}				t_word;

extern t_sh g_shell;

enum			e_parser
{
	SEMICOLON = 0,
	PIPE,
	REDIRECTING_OUT,
	REDIRECTING_IN,
	APPENDIG_OUT,
	AND,
	OR,
	PATH,
	SINGLE_Q,
	DOUBLE_Q,
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

typedef struct	s_cmd
{
	int		id;
	char	**args;
	int		len_args;
	int		in;
	int		out;
}				t_cmd;

char			**ft_copy_envp(char **ev);
char			**ft_init_envp(char **ev, size_t len_env);

void			ft_read(char **str);
size_t			ft_strlchar(char *dst, const char src, size_t dstsize);
int				ft_putint(int c);
t_hstr			*ft_read_t(t_hstr **history);
t_hstr			*ft_make_el(void);
void			ft_add_before(t_hstr **lst, t_hstr *new);
int				ft_give_str(char **str);
size_t			ft_strlchar(char *dst, const char src, size_t dstsize);
void			ft_term_nl(char **s);
void			ft_term_bs(char **s, t_hstr **el);
void			ft_term_exit(void);
void			ft_term_print(char **s, t_hstr **el);

int				ft_check_str(char *str);
char			**ft_parser_shell(char **envp, char *str);
char			**ft_split_cmd(char const *s, char c, size_t i, int flag);
char			**ft_split_arg(char *s, char *c, size_t i, int flag);
int				ft_isntend_split(char const *s, int *flag);
int				ft_free_split(char **result, size_t last);
void			ft_check_d(const char *s, int *d, int *flag, int *i);
void			ft_check_d_v1(const char *s, int *d, int *flag);
void			ft_check_d_less(const char s, char *c, int *d, int *flag);
int				ft_check_tail(int flag);
int				ft_lenarray(char **cmd);
void			free_array_shell(char **ar);
void			free_array_shell_2(char ***ar);
void			free_t_cmd(t_cmd *ar_t_cmd, int len);
void			free_close_fd(t_cmd *ar_t_cmd, int len);
int				ft_write_append(char *a, int *out);
int				ft_write_only(char *a, int *out);
int				ft_read_only(char *a, int *in);
char			*ft_strjoin_mod(char const *s1, char const *s2, size_t len);
char			*ft_pars_name(char *str);
char			*ft_create_word_a(char const *s, char *c);
size_t			ft_count_a(char const *s, char *c);
void			ft_check_cond_if1(char const *s, int *flag, int *i);
void			ft_check_cond_if2(char const *s, int *flag, int *i);
void			ft_check_cond_if3(char const *s, int *flag, int *i);
void			ft_check_condition_sh(char const *s, int *flag, int *i);
int				ft_chec_str_if(char *str, int i, int flag);
void			ft_check_condition(char const *s, int *flag, int *i);

char			**ft_make_norm(char **ar, int *in, int *out, char **envp);
char			**ft_parser_str(t_cmd ar_t_cmd);
char			*ft_res0(char *str, int *flag, char **envp);
char			*ft_res_arg(char *str, int *flag, char **envp);
char			*ft_dollar (char *str, int *i, char **envp);
int				ft_is(char const *s, int *flag, int *i);
int				ft_res0_if(char *str, int *flag, t_word *w);
int				ft_res0_if1(char *str, int *flag, t_word *w);
void			ft_res0_part1(char **res, t_word *w);
void			ft_res0_part0(char *str, t_word *w, char **envp, char **res);
void			ft_in_cycle(char **res, char *temp, int *j, size_t len);
int				ft_res_arg_if0(char *str, int i, int *flag);
int				ft_res_arg_if1(char *str, int i, int *flag);
int				ft_res_arg_if2(char *str, int i, int *flag);
void			ft_res_arg_part1(char *star, char **envp, t_word *w,
		char **res);
void			ft_cp_ar_sh_part(char ***r_a, int i, int len);
void			*ft_free_r_a(char ***r_a);
void			ft_free_r_a_i(char ***r_a, int i);
void			ft_ar_null(char ***ar_pipe);
char			**ft_parser_shel_cycle(t_cmd *ar_t_cmd, int len, char **envp,
		char ***cmd);

char			**ft_parser_er2(char *error);
char			*ft_parser_er1(char *error);
char			**ft_parser_err_free2(char *error, char **a);
char			**ft_parser_free2(char **a);
int				ft_parser_err_fd(char **name);

void			sig_init(void);
void			sig_int(int id);
void			sig_stub(int id);
void			sig_quit(int id);

char			**ft_exec_cmd(t_cmd *ar_cmd, char **env, int cmd_count);
char			**ft_exec_pipe(t_cmd *ar_cmd, char **env, int cmd_count);
int				ft_pwd(int out);
int				ft_env(char **env, int out);
int				ft_exec_bin(t_cmd *cmd, char *filename, char **envp);
int				init_command(t_cmd *cmd, char **envp);
char			**ft_export(t_cmd *cmd, char **env);
char			**ft_unset(t_cmd *cmd, char **env);
char			**ft_cd(t_cmd *cmd, char **envp);
int				ft_exit(t_cmd *cmd);
int				ft_echo(t_cmd *cmd);
int				ft_unstr(char *var, char *key);
int				handle_cmd_not_found(char *name);
char			*ft_var_find(char *var, char **ev);
char			*ft_find_env(char *var, char **ev);
char			*ft_find_bin(char *filename, char *path);
char			**add_value(char *var, char **ev);
char			**change_value(char *var, char **ev);
char			**ft_del_env(char **ev, size_t env_len, char *var);
t_cmd			*close_files(t_cmd *ar_cmd, int i, int cmd_count);
void			dup_start(t_cmd *ar_cmd);
void			dup_end(t_cmd *ar_cmd);
void			exec_pipe_init(char **path, char **env);
void			print_export_until(char *buf, int out);
size_t			env_len(char **env);
void			env_sort(char **a, size_t len);
int				arg_check(char *arg);
char			*find_value(char *key, char **ev);
t_cmd			*close_files(t_cmd *ar_cmd, int i, int cmd_count);
t_cmd			*close_files(t_cmd *ar_cmd, int i, int cmd_count);
void			dup_end(t_cmd *ar_cmd);

void			ft_putstr_error(char *str, int er);
int				ft_check_er_args(t_cmd *ar_t_cmd, int len);

char			*ft_array_to_str(char **array);

void			ft_m_test_pr(t_list *first);
void			ft_print_array_2(char **arr);
void			ft_print_array_3(char ***arr);
void			ft_print_array_t_cmd(t_cmd *ar_t_cmd, int len);

#endif
