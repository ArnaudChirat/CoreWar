/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:27:17 by achirat           #+#    #+#             */
/*   Updated: 2018/01/12 15:58:55 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		check_flags_u(t_conv *conv, char **tmp)
{
	char	*tmp2;

	tmp2 = *tmp;
	if (conv->tab['#'] != 0 && conv->def_type == 'x')
	{
		*tmp = ft_strjoin("0x", *tmp);
		ft_strdel(&tmp2);
	}
	else if (conv->tab['#'] != 0 && conv->def_type == 'X')
	{
		*tmp = ft_strjoin("0X", *tmp);
		ft_strdel(&tmp2);
	}
	else if (conv->tab['#'] != 0 && (conv->def_type == 'o' ||
		conv->def_type == 'O') && *tmp[0] != '0')
	{
		*tmp = ft_strjoin("0", *tmp);
		ft_strdel(&tmp2);
	}
}

static void		check_flags(t_conv *conv, char **tmp)
{
	char	*tmp2;

	tmp2 = *tmp;
	if (conv->type == TYPE_IMAX)
	{
		if (conv->tab['+'] != 0)
		{
			*tmp = ft_strjoin("+", *tmp);
			ft_strdel(&tmp2);
		}
		else if (conv->tab[' '] != 0)
		{
			*tmp = ft_strjoin(" ", *tmp);
			ft_strdel(&tmp2);
		}
	}
	else if (conv->type == TYPE_UIMAX)
		check_flags_u(conv, tmp);
}

static void		check_precision(t_conv *conv, char **tmp)
{
	char	*strf;
	int		len;
	int		a;
	char	*tmp2;

	a = 0;
	len = conv->precision - ft_strlen(*tmp);
	if (conv->type == TYPE_IMAX && conv->u_var.i_max < 0)
		len += 1;
	if (len > 0)
	{
		strf = ft_strnew(len);
		tmp2 = *tmp;
		while (a < len)
			strf[a++] = '0';
		if (conv->type == TYPE_IMAX && conv->u_var.i_max < 0)
		{
			(*tmp)[0] = '0';
			strf[0] = '-';
		}
		*tmp = ft_strjoin(strf, *tmp);
		ft_strdel(&tmp2);
		free(strf);
	}
}

static void		check_format(t_conv *conv, const char *format, char **tmp)
{
	char	*str;
	char	*tmp2;

	if (!(str = ft_strchr(format + 1, conv->def_type)))
		return ;
	tmp2 = *tmp;
	*tmp = ft_strjoin(*tmp, str + 1);
	ft_strdel(&tmp2);
	if (ft_strchr(str + 1, '%'))
	{
		tmp2 = *tmp;
		*tmp = ft_strsub(*tmp, 0, ft_strlen(*tmp) -
				ft_strlen(ft_strchr(str + 1, '%')));
		ft_strdel(&tmp2);
	}
}

void			add_flags(t_conv *conv, const char *format, char **tmp)
{
	if (conv->type == TYPE_VOID)
		ft_precision_str(conv, tmp);
	else if (conv->def_type != 'c' && conv->type != TYPE_VOID)
		check_precision(conv, tmp);
	check_flags(conv, tmp);
	check_width(conv, tmp);
	check_format(conv, format, tmp);
}
