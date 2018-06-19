/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 09:40:49 by achirat           #+#    #+#             */
/*   Updated: 2018/01/11 16:43:02 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		init_buf(t_buff *res, const char *str)
{
	size_t	init;

	if (ft_strchr(str, '%') != 0)
		init = ft_strlen(str) - ft_strlen(ft_strchr(str, '%'));
	else
		init = ft_strlen(str);
	ft_bzero(res, sizeof(*res));
	ft_strncat(res->buff, str, init);
	res->index = init;
}

int				ft_printf(const char *format, ...)
{
	va_list	ap;
	t_buff	res;
	t_conv	conv;

	init_buf(&res, format);
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			fill_conv(format + 1, &conv, ap);
			fill_buff(&conv, format, &res);
			if (conv.def_type == '%')
				format = ft_strchr(format + 1, '%');
			if (res.index == -1)
				return (res.index);
		}
		format++;
	}
	va_end(ap);
	ft_putstr(res.buff);
	return (res.index);
}
