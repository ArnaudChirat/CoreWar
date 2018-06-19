/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:20:11 by achirat           #+#    #+#             */
/*   Updated: 2018/01/31 16:06:47 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		type_string(t_conv *conv, void *arg)
{
	if (TAB('l') == 0 && TAB('h') == 0 && TAB('j') == 0)
		conv->u_var.s = ft_strdup((char*)arg);
	else if (TAB('l') == 1 && TAB('h') == 0 && TAB('j') == 0)
		conv->u_var.S = (wchar_t*)arg;
	else
		conv->type = -1;
}

static void		type_char(t_conv *conv, void *arg)
{
	if (TAB('l') == 0 && TAB('h') == 0 && TAB('j') == 0)
		conv->u_var.c = (char)arg;
	else if (TAB('l') == 1 && TAB('h') == 0 && TAB('j') == 0)
		conv->u_var.C = (wchar_t)arg;
	else
		conv->type = -1;
}

static void		type_unsigned(t_conv *conv, void *arg)
{
	if (TAB('l') == 0 && TAB('h') == 0 && TAB('j') == 0)
		conv->u_var.i_max = (intmax_t)arg;
	else if (TAB('l') == 1 && TAB('h') == 0 && TAB('j') == 0)
		conv->u_var.u_l = (unsigned long)arg;
	else if (TAB('l') >= 2 && TAB('h') == 0 && TAB('j') == 0)
		conv->u_var.u_ll = (unsigned long long)arg;
	else if (TAB('j') == 1 && TAB('h') == 0 && TAB('l') == 0)
		conv->u_var.u_i_max = (uintmax_t)arg;
	else if (TAB('h') == 1 && TAB('j') == 0 && TAB('l') == 0)
		conv->u_var.u_sh = (unsigned short)arg;
	else if (TAB('h') == 2 && TAB('j') == 0 && TAB('l') == 0)
		conv->u_var.u_c = (unsigned char)arg;
	else
		conv->type = -1;
}

static void		type_int(t_conv *conv, void *arg)
{
	if (TAB('l') == 0 && TAB('h') == 0 && TAB('j') == 0)
		conv->u_var.i = (int)arg;
	else if (TAB('l') == 1 && TAB('h') == 0 && TAB('j') == 0)
		conv->u_var.l = (long)arg;
	else if (TAB('l') >= 2 && TAB('h') == 0 && TAB('j') == 0)
		conv->u_var.ll = (long long)arg;
	else if (TAB('j') == 1 && TAB('h') == 0 && TAB('l') == 0)
		conv->u_var.i_max = (intmax_t)arg;
	else if (TAB('h') == 1 && TAB('j') == 0 && TAB('l') == 0)
		conv->u_var.sh = (short)arg;
	else if (TAB('h') == 2 && TAB('j') == 0 && TAB('l') == 0)
		conv->u_var.c = (char)arg;
	else
		conv->type = -1;
}

void			conv_type(t_conv *conv, void *arg)
{
	if (conv->def_type == 'd' || conv->def_type == 'i')
		type_int(conv, arg);
	else if (conv->def_type == 'u' || conv->def_type == 'o' ||
			conv->def_type == 'x')
		type_unsigned(conv, arg);
	else if (conv->def_type == 'c')
		type_char(conv, arg);
	else if (conv->def_type == 's')
		type_string(conv, arg);
	else if (conv->def_type == 'p')
		conv->u_var.ptr = arg;
	else
		conv->type = -1;
}
