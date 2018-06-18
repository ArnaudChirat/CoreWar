/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 19:11:09 by achirat           #+#    #+#             */
/*   Updated: 2018/01/12 11:06:29 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	modif_unsigned(t_conv *conv)
{
	if (conv->tab['l'] == 0 && conv->tab['h'] == 0 && conv->tab['z'] == 0
		&& conv->tab['j'] == 0)
		conv->u_var.u_i_max = (unsigned int)conv->u_var.u_i_max;
	else if (conv->tab['l'] == 1 && conv->tab['h'] == 0 && conv->tab['z'] == 0
			&& conv->tab['j'] == 0)
		conv->u_var.u_i_max = (unsigned long)conv->u_var.u_i_max;
	else if (conv->tab['l'] == 2 && conv->tab['h'] == 0 && conv->tab['z'] == 0
			&& conv->tab['j'] == 0)
		conv->u_var.u_i_max = (unsigned long long)conv->u_var.u_i_max;
	else if (conv->tab['l'] == 0 && conv->tab['h'] == 1 && conv->tab['z'] == 0
			&& conv->tab['j'] == 0)
		conv->u_var.u_i_max = (unsigned short)conv->u_var.u_i_max;
	else if (conv->tab['l'] == 0 && conv->tab['h'] == 2 && conv->tab['z'] == 0
			&& conv->tab['j'] == 0)
		conv->u_var.u_i_max = (unsigned char)conv->u_var.u_i_max;
	else if (conv->tab['l'] == 0 && conv->tab['h'] == 0 && conv->tab['z'] == 1
			&& conv->tab['j'] == 0)
		conv->u_var.u_i_max = (size_t)conv->u_var.u_i_max;
}

static void	modif_signed(t_conv *conv)
{
	if (conv->tab['l'] == 0 && conv->tab['h'] == 0 && conv->tab['z'] == 0
		&& conv->tab['j'] == 0)
		conv->u_var.i_max = (int)conv->u_var.i_max;
	else if (conv->tab['l'] == 1 && conv->tab['h'] == 0 && conv->tab['z'] == 0
			&& conv->tab['j'] == 0)
		conv->u_var.i_max = (long)conv->u_var.i_max;
	else if (conv->tab['l'] == 2 && conv->tab['h'] == 0 && conv->tab['z'] == 0
			&& conv->tab['j'] == 0)
		conv->u_var.i_max = (long long)conv->u_var.i_max;
	else if (conv->tab['l'] == 0 && conv->tab['h'] == 1 && conv->tab['z'] == 0
			&& conv->tab['j'] == 0)
		conv->u_var.i_max = (short)conv->u_var.i_max;
	else if (conv->tab['l'] == 0 && conv->tab['h'] == 2 && conv->tab['z'] == 0
			&& conv->tab['j'] == 0)
		conv->u_var.i_max = (char)conv->u_var.i_max;
	else if (conv->tab['l'] == 0 && conv->tab['h'] == 0 && conv->tab['z'] == 1
			&& conv->tab['j'] == 0)
		conv->u_var.i_max = (size_t)conv->u_var.i_max;
}

static void	modif_char(t_conv *conv)
{
	if (conv->tab['l'] == 0)
		conv->u_var.i_max = (char)conv->u_var.i_max;
	else if (conv->tab['l'] == 1)
		conv->u_var.i_max = (wchar_t)conv->u_var.i_max;
}

void		modif_var(t_conv *conv)
{
	if (conv->type == TYPE_IMAX && (conv->def_type == 'd' ||
		conv->def_type == 'i'))
		modif_signed(conv);
	else if (conv->type == TYPE_IMAX && conv->def_type == 'c')
		modif_char(conv);
	else if (conv->type == TYPE_UIMAX && conv->def_type != 'U')
		modif_unsigned(conv);
	else if (conv->def_type == 'D')
		conv->u_var.i_max = (long)conv->u_var.i_max;
	else if (conv->def_type == 'U')
		conv->u_var.u_i_max = (unsigned long)conv->u_var.u_i_max;
	else
		return ;
}
