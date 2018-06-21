/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:01:36 by achirat           #+#    #+#             */
/*   Updated: 2018/06/20 17:05:21 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef __APPLE__
#  include <stdint.h>
#  define OPEN_MAX FOPEN_MAX
# endif

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

char			*ft_itoabase_u(unsigned long long nbr, char *base);
char			*ft_itoabase(long long nbr, char *base);
void			ft_putchar(char c);
void			ft_putstr(char const *str);
void			ft_putnbr(int a);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strndup(const char *s1, int n);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *stack, const char *needle, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memalloc(size_t n);
void			ft_memdel(void **app);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strnjoin(char const *s1, char const *s2, size_t n);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
void			ft_tabdel(char ***tab);
char			*ft_itoa(int n);
void			ft_putendl(char const *str);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_del(void *content, size_t content_size);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstaddend(t_list **alst, t_list *new);
t_list			*ft_lstdup(t_list *list);
size_t			ft_lstlen(t_list *alst);
void			ft_swap(int *a, int *b);
int				ft_sqrt(int nb);
int				ft_nextsqrt(int n);
void			ft_foreach(void *content, size_t len, void (*f)(void *));
void			ft_lstrev(t_list **alst);
char			*ft_strrev(char *s);
double			ft_squareroot(double x, int prec);

float			ft_fmin(float a, float b);
float			ft_fmax(float a, float b);
float			ft_fclamp(float min, float max, float val);
int32_t			ft_min(int32_t a, int32_t b);
int32_t			ft_max(int32_t a, int32_t b);
int32_t			ft_clamp(int32_t min, int32_t max, int32_t val);

#endif
