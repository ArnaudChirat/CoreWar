/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 21:50:36 by achirat           #+#    #+#             */
/*   Updated: 2018/01/11 16:03:14 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_precision_str(t_conv *conv, char **tmp)
{
	size_t	a;
	char	*tmp2;

	a = ft_strlen(*tmp);
	tmp2 = *tmp;
	if (conv->tab['l'] == 1 || conv->def_type == 'S')
		return ;
	if (conv->precision < (int)a && conv->precision != 0)
	{
		*tmp = ft_strsub(*tmp, 0, conv->precision);
		ft_strdel(&tmp2);
	}
}
