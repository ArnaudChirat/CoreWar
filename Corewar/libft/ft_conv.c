/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:07:55 by achirat           #+#    #+#             */
/*   Updated: 2018/01/11 09:13:17 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_conv(t_conv *conv, va_list ap)
{
	if (conv->def_type == 'd' || conv->def_type == 'i' || conv->def_type == 'D'
		|| conv->def_type == 'c' || conv->def_type == 'C')
	{
		conv->u_var.i_max = va_arg(ap, intmax_t);
		conv->type = TYPE_IMAX;
	}
	else if (conv->def_type == 'u' || conv->def_type == 'x' ||
			conv->def_type == 'X' || conv->def_type == 'o' ||
			conv->def_type == 'O' || conv->def_type == 'U')
	{
		conv->u_var.u_i_max = va_arg(ap, uintmax_t);
		conv->type = TYPE_UIMAX;
	}
	else if (conv->def_type == 's' || conv->def_type == 'S' ||
			conv->def_type == 'p')
	{
		conv->u_var.ptr = va_arg(ap, void *);
		conv->type = TYPE_VOID;
	}
	else if (conv->def_type == '%')
		conv->type = TYPE_PRC;
}
