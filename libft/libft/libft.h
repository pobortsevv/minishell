/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabra <sabra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:39:34 by sabra             #+#    #+#             */
/*   Updated: 2021/02/18 20:24:12 by sabra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <math.h>
# define BUFFER_SIZE 1024

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_struct
{
	int		minus;
	int		zero;
	int		width;
	int		dot_star;
	int		lenght;
	char	type;
}					t_struct;

int					ft_printf(const char *input, ...);
int					ft_write_common(const char *str, va_list args, int i);
char				*ft_strdup_gnl(char *src);
char				*ft_strjoin_gnl(char *s1, char *s2);
int					get_next_line(int fd, char **line);
int					ft_type_init(t_struct flgs, va_list args);
int					ft_c_type(t_struct flgs, va_list args, int count);
int					ft_s_type(t_struct flgs, va_list args);
int					ft_p_type(t_struct flgs, va_list args);
int					ft_di_type(t_struct flgs, va_list args, int count);
int					ft_u_type(t_struct flgs, va_list args);
float				ft_queq(float a, float b, float c, int id);
int					ft_dwx_type(t_struct flgs, va_list args);
int					ft_upx_type(t_struct flgs, va_list args);
t_struct			ft_minus_init(t_struct flgs);
t_struct			ft_width_init(const char *str, t_struct flgs, int i,
		va_list args);
t_struct			ft_dot_star_init(const char *str, t_struct flgs,
		int i, va_list args);
char				**ft_free_mat(char **mat);
void				ft_free_line(char **line);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
int					ft_isdigit(int c);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlen(const char *str);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(char *s1, char *s2, unsigned int n);
char				*ft_strnstr(char *str1, char *str2, size_t size);
int					ft_atoi(const char *str);
float				ft_atof(char *str);
int					ft_intlen(int n);
char				*ft_strdup(char *src);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_isalnum(int character);
int					ft_inset(char *line, char *set);
int					ft_isalpha(int character);
int					ft_isascii(int character);
int					ft_isprint(int character);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_charcnt(char *line, int c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr16_fd(unsigned long num, int fd, char *base);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
int					ft_space(char sym);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *));

#endif
