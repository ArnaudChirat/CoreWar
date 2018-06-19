/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:47:23 by achirat           #+#    #+#             */
/*   Updated: 2018/01/08 19:19:56 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		check_order(t_conv *conv, char **tmp)
{
	size_t	a;
	size_t	b;
	char	c;

	a = 0;
	b = 0;
	c = 0;
	if (conv->type != TYPE_IMAX)
		return ;
	while ((*tmp)[a] != '0' && (*tmp)[a])
		a++;
	if (tmp[a] == '\0')
		return ;
	while (((*tmp)[a + b] != '-' && (*tmp)[a + b] != '+') && (*tmp)[a + b])
		b++;
	if ((*tmp)[a + b] == '-' || (*tmp)[a + b] == '+')
	{
		c = (*tmp)[a];
		(*tmp)[a] = (*tmp)[a + b];
		(*tmp)[a + b] = c;
	}
}
