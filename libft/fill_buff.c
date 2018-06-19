/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 17:46:07 by achirat           #+#    #+#             */
/*   Updated: 2018/01/12 10:42:29 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*go_uitoa(t_conv *conv)
{
	char *tmp;

	if (conv->def_type == 'u' || conv->def_type == 'U')
		tmp = ft_itoabase_u(conv->u_var.u_i_max, "0123456789");
	else if (conv->def_type == 'o' || conv->def_type == 'O')
		tmp = ft_itoabase_u(conv->u_var.u_i_max, "01234567");
	else if (conv->def_type == 'x')
		tmp = ft_itoabase_u(conv->u_var.u_i_max, "0123456789abcdef");
	else if (conv->def_type == 'X')
		tmp = ft_itoabase_u(conv->u_var.u_i_max, "0123456789ABCDEF");
	else
		tmp = NULL;
	if (!tmp)
		conv->error = -1;
	return (tmp);
}

static char	*go_itoa(t_conv *conv)
{
	char	*tmp;

	if (conv->def_type == 'd' || conv->def_type == 'i' || conv->def_type == 'D')
		tmp = ft_itoabase(conv->u_var.i_max, "0123456789");
	else if (conv->def_type == 'c' && conv->tab['l'] == 0)
	{
		tmp = ft_strnew(1);
		tmp[0] = conv->u_var.i_max;
		if (conv->u_var.i_max == 0)
			tmp[0] = 'A';
	}
	else if (conv->def_type == 'C' || (conv->def_type == 'c' &&
			conv->tab['l'] == 1))
		tmp = ft_unicode((wchar_t)conv->u_var.i_max);
	else
		tmp = NULL;
	if (!tmp)
		conv->error = -1;
	return (tmp);
}

static char	*go_wchar(t_conv *conv)
{
	wchar_t *wtmp;
	char	*tmp;

	wtmp = (wchar_t*)conv->u_var.ptr;
	tmp = ft_str_unicode(conv, wtmp);
	if (!tmp)
		conv->error = -1;
	return (tmp);
}

static char	*go_str(t_conv *conv)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	if (conv->def_type == 's' && conv->u_var.ptr && conv->tab['l'] == 0)
		tmp = ft_strdup(conv->u_var.ptr);
	else if ((conv->tab['l'] == 1 || conv->def_type == 'S') && conv->u_var.ptr)
		tmp = go_wchar(conv);
	else if (conv->u_var.ptr == NULL && conv->def_type != 'p')
	{
		tmp = ft_strdup("(null)");
	}
	else if (conv->def_type == 'p')
	{
		tmp2 = ft_itoabase_u((unsigned long)conv->u_var.ptr,
				"0123456789abcdef");
		tmp = ft_strjoin("0x", tmp2);
		ft_strdel(&tmp2);
	}
	if (!tmp)
		conv->error = -1;
	return (tmp);
}

void		fill_buff(t_conv *conv, const char *format, t_buff *res)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	if (conv->type == TYPE_IMAX)
		tmp = go_itoa(conv);
	else if (conv->type == TYPE_UIMAX)
		tmp = go_uitoa(conv);
	else if (conv->type == TYPE_VOID)
		tmp = go_str(conv);
	else if (conv->type == TYPE_PRC)
		tmp = ft_strdup("%");
	if (tmp)
	{
		update_flags(conv, &tmp);
		add_flags(conv, format, &tmp);
	}
	tmp2 = tmp;
	check_buff(conv, res, tmp);
	ft_strdel(&tmp2);
}
