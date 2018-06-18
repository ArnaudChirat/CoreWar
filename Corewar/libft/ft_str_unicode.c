/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_unicode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 10:32:07 by achirat           #+#    #+#             */
/*   Updated: 2018/01/12 10:46:34 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_str_unicode(t_conv *conv, wchar_t *wchar)
{
	char	*tmp;
	char	*tmp2;
	char	*str;

	tmp = ft_strnew(0);
	while (*wchar)
	{
		tmp2 = tmp;
		if (!(str = ft_unicode(*wchar)))
			return (0);
		if (conv->precision && (int)(ft_strlen(str) + ft_strlen(tmp)) >
			conv->precision)
		{
			free(str);
			if (tmp2 != tmp)
				free(tmp2);
			break ;
		}
		else
			tmp = ft_strjoin(tmp, str);
		ft_strdel(&tmp2);
		ft_strdel(&str);
		wchar++;
	}
	return (tmp);
}
