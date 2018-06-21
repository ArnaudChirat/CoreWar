/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 09:23:40 by achirat           #+#    #+#             */
/*   Updated: 2018/01/11 18:58:00 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	take_care(t_buff *res, char *tmp)
{
	size_t	a;
	char	*str;

	a = 0;
	ft_putstr(res->buff);
	while (tmp[a] != 'A')
		a++;
	str = ft_strsub(tmp, 0, a);
	ft_putstr(str);
	ft_putchar(0);
	a++;
	while (tmp[a])
	{
		ft_putchar(tmp[a]);
		a++;
	}
	ft_bzero(res->buff, sizeof(BUFSIZ));
	free(str);
}

static void	error(t_buff *res, t_conv *conv)
{
	ft_bzero(res->buff, BUFSIZ);
	ft_bzero(conv, sizeof(*conv));
	res->index = -1;
}

void		check_buff(t_conv *conv, t_buff *res, char *tmp)
{
	if (conv->error == -1)
	{
		error(res, conv);
		return ;
	}
	else if ((res->index % BUFSIZ) + ft_strlen(tmp) > BUFSIZ)
	{
		ft_putstr(res->buff);
		ft_bzero(res->buff, BUFSIZ);
	}
	res->index += ft_strlen(tmp);
	if (ft_strlen(tmp) > BUFSIZ)
	{
		ft_putstr(tmp);
		return ;
	}
	if ((conv->def_type == 'c' || conv->def_type == 'C')
		&& conv->u_var.i_max == 0)
		take_care(res, tmp);
	else
		ft_strcat(res->buff, tmp);
}
