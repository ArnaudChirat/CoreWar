/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 09:03:19 by achirat           #+#    #+#             */
/*   Updated: 2018/01/12 11:05:43 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_four_bits(wchar_t wchar)
{
	unsigned char	tab[5];

	tab[0] = (unsigned char)(((wchar & 0x1C0000) >> 18) + 0xf0);
	tab[1] = (unsigned char)(((wchar & 0x3f000) >> 12) + 0x80);
	tab[2] = (unsigned char)(((wchar & 0xfc0) >> 6) + 0x80);
	tab[3] = (unsigned char)((wchar & 0x3f) + 0x80);
	tab[4] = '\0';
	return (ft_strdup((const char*)tab));
}

static char	*ft_three_bits(wchar_t wchar)
{
	unsigned char	tab[4];

	tab[0] = (unsigned char)(((wchar & 0xf000) >> 12) + 0xe0);
	tab[1] = (unsigned char)(((wchar & 0xfc0) >> 6) + 0x80);
	tab[2] = (unsigned char)((wchar & 0x3f) + 0x80);
	tab[3] = '\0';
	return (ft_strdup((const char*)tab));
}

static char	*ft_two_bits(wchar_t wchar)
{
	unsigned char	tab[3];

	tab[0] = (unsigned char)(((wchar & 0x7c0) >> 6) + 0xc0);
	tab[1] = (unsigned char)((wchar & 0x3F) + 0x80);
	tab[2] = '\0';
	return (ft_strdup((const char*)tab));
}

static int	ft_parse(wchar_t wchar)
{
	if (wchar < 0x0000 || wchar > 0x10ffff)
		return (0);
	if (wchar >= 0xd800 && wchar <= 0xdfff)
		return (0);
	return (1);
}

char		*ft_unicode(wchar_t wchar)
{
	char	*len;
	char	*tmp;

	tmp = NULL;
	len = ft_itoabase((intmax_t)wchar, "01");
	if (ft_parse(wchar) == 0 || MB_CUR_MAX == 1)
	{
		free(len);
		return (0);
	}
	if (ft_strlen(len) < 8)
	{
		tmp = ft_strnew(1);
		tmp[0] = (char)wchar;
		if (wchar == 0)
			tmp[0] = 'A';
	}
	else if (ft_strlen(len) >= 8 && ft_strlen(len) <= 11)
		tmp = ft_two_bits(wchar);
	else if (ft_strlen(len) > 11 && ft_strlen(len) <= 16)
		tmp = ft_three_bits(wchar);
	else if (ft_strlen(len) > 16 && ft_strlen(len) <= 21)
		tmp = ft_four_bits(wchar);
	free(len);
	return (tmp);
}
