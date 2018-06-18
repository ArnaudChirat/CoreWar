/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:25:44 by achirat           #+#    #+#             */
/*   Updated: 2018/01/31 16:08:19 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			type_string(t_conv *conv)
{
	if (TAB('l') == 0 && TAB('h') == 0 && TAB('j') == 0)
		conv->type = TYPE_STRING;
	else if (TAB('l') == 1 && TAB('h') == 0 && TAB('j') == 0)
		conv->type = TYPE_SWCHAR;
	else
		conv->type = -1;
}

static void			type_char(t_conv *conv)
{
	if (TAB('l') == 0 && TAB('h') == 0 && TAB('j') == 0)
		conv->type = TYPE_CHAR;
	else if (TAB('l') == 1 && TAB('h') == 0 && TAB('j') == 0)
		conv->type = TYPE_WCHAR;
	else
		conv->type = -1;
}

static void			type_unsigned(t_conv *conv)
{
	if (conv->def_type == 'u')
		conv->type = TYPE_UDECIMAL;
	else if (conv->def_type == 'o')
		conv->type = TYPE_UOCTAL;
	else if (conv->def_type == 'x')
		conv->type = TYPE_UHEXA;
	else
		conv->type = -1;
}

void				enum_type(t_conv *conv)
{
	if (conv->def_type == 'd' || conv->def_type == 'i')
		conv->type = TYPE_DECIMAL;
	else if (conv->def_type == 'u' || conv->def_type == 'o' ||
			conv->def_type == 'x')
		type_unsigned(conv);
	else if (conv->def_type == 'c')
		type_char(conv);
	else if (conv->def_type == 's')
		type_string(conv);
	else if (conv->def_type == 'p')
		conv->type = TYPE_UHEXA;
	else
		conv->type = -1;
}
