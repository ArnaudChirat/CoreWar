/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:21:44 by achirat           #+#    #+#             */
/*   Updated: 2018/01/12 11:07:07 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	update_flags(t_conv *conv, char **tmp)
{
	if (conv->def_type == 'c' && conv->u_var.i_max == 0)
		ft_bzero(conv->tab, sizeof(128));
	if (conv->def_type == '%')
		conv->precision = 0;
	if (conv->u_var.u_i_max == 0 && conv->def_type != 'o' &&
		conv->def_type != 'O')
		conv->tab['#'] = 0;
	if (conv->tab['-'] != 0)
		conv->tab['0'] = 0;
	if (conv->tab['.'] != 0)
		conv->tab['0'] = 0;
	if (conv->tab['+'] != 0 || conv->def_type == 'c')
		conv->tab[' '] = 0;
	if (conv->u_var.i_max < 0)
	{
		conv->tab['+'] = 0;
		conv->tab[' '] = 0;
	}
	if (conv->tab['.'] != 0 && conv->precision == 0 && conv->def_type != '%'
		&& conv->def_type != 'c' && (conv->u_var.i_max == 0
		|| conv->def_type == 's'))
		ft_strclr(*tmp);
}
