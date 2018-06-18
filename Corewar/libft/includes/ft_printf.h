/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 09:59:11 by achirat           #+#    #+#             */
/*   Updated: 2018/01/18 16:10:22 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

typedef struct		s_conv
{
	union
	{
		intmax_t	i_max;
		uintmax_t	u_i_max;
		void		*ptr;
	}				u_var;
	int				tab[128];
	char			def_type;
	int				precision;
	int				width;
	int				type;
	int				error;
}					t_conv;

typedef struct		s_buff
{
	int				index;
	char			buff[BUFSIZ];
}					t_buff;

enum				e_type
{
	TYPE_IMAX, TYPE_UIMAX, TYPE_VOID, TYPE_PRC
};

char				*ft_unicode(wchar_t wchar);
void				check_width(t_conv *conv, char **tmp);
void				update_flags(t_conv *conv, char **tmp);
void				ft_precision_str(t_conv *conv, char **tmp);
int					ft_printf(const char *format, ...);
void				fill_conv(const char *format, t_conv *conv, va_list ap);
void				ft_conv(t_conv *conv, va_list ap);
void				fill_buff(t_conv *conv, const char *format, t_buff *res);
void				modif_var(t_conv *conv);
void				check_buff(t_conv *conv, t_buff *res, char *tmp);
void				add_flags(t_conv *conv, const char *format, char **tmp);
char				*ft_str_unicode(t_conv *conv, wchar_t *wchar);

#endif
