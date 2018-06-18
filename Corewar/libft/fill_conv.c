/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:26:46 by achirat           #+#    #+#             */
/*   Updated: 2018/01/11 10:39:49 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_type(const char *format, t_conv *conv)
{
	size_t	a;
	char	tab_type[16];

	ft_strcpy(tab_type, "sSpdDioOuUxXcC%");
	while (*format && conv->def_type == 0)
	{
		a = 0;
		while (tab_type[a])
		{
			if (tab_type[a] == *format)
			{
				conv->def_type = tab_type[a];
				break ;
			}
			a++;
		}
		format++;
	}
}

static void	fill_taille(const char *format, t_conv *conv)
{
	size_t	a;
	char	tab_taille[5];

	ft_strcpy(tab_taille, "hljz");
	while (*format != conv->def_type)
	{
		a = 0;
		while (tab_taille[a])
		{
			if (tab_taille[a] == *format)
				conv->tab[(int)tab_taille[a]] += 1;
			a++;
		}
		format++;
	}
}

static void	fill_width_precision(const char *format, t_conv *conv)
{
	while (*format != '.' && *format != conv->def_type)
		format++;
	if (*format == '.')
	{
		conv->tab['.'] = 1;
		conv->precision = ft_atoi(format + 1);
	}
	else
		conv->precision = 0;
}

static void	fill_flags(const char *format, t_conv *conv)
{
	size_t	a;
	char	tab_flags[6];

	ft_strcpy(tab_flags, " +-0#");
	while (conv->def_type != *format && (*format < '1' || *format > '9'))
	{
		a = 0;
		while (tab_flags[a])
		{
			if (tab_flags[a] == *format)
				conv->tab[(int)tab_flags[a]] += 1;
			a++;
		}
		if (*format == '.')
			return ;
		format++;
	}
	conv->width = ft_atoi(format);
}

void		fill_conv(const char *format, t_conv *conv, va_list ap)
{
	ft_bzero(conv, sizeof(t_conv));
	fill_type(format, conv);
	fill_width_precision(format, conv);
	fill_taille(format, conv);
	fill_flags(format, conv);
	ft_conv(conv, ap);
	modif_var(conv);
}
