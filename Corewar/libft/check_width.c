/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:37:48 by achirat           #+#    #+#             */
/*   Updated: 2018/01/11 19:15:33 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_order(t_conv *conv, char **tmp)
{
	size_t	a;

	a = 0;
	if (conv->tab['-'] != 0 || conv->tab['0'] == 0)
		return ;
	if ((conv->u_var.i_max < 0 || conv->tab['+'] != 0 || conv->tab[' '] != 0))
	{
		while ((*tmp)[a] != '+' && (*tmp)[a] != '-' && (*tmp)[a] != ' ')
			a++;
		(*tmp)[0] = (*tmp)[a];
		(*tmp)[a] = '0';
	}
	else if (conv->tab['#'] != 0)
	{
		while ((*tmp)[a] != 'x' && (*tmp)[a] != 'X')
			a++;
		(*tmp)[1] = (*tmp)[a];
		(*tmp)[a] = '0';
	}
}

static void	check_tab(t_conv *conv, char *strf, char **tmp)
{
	char	*tmp2;

	tmp2 = *tmp;
	if (strf && conv->tab['-'] == 0)
	{
		*tmp = ft_strjoin(strf, *tmp);
		ft_strdel(&tmp2);
		ft_order(conv, tmp);
	}
	else if (strf && conv->tab['-'] != 0)
	{
		*tmp = ft_strjoin(*tmp, strf);
		ft_strdel(&tmp2);
	}
}

void		check_width(t_conv *conv, char **tmp)
{
	char	*strf;
	int		len;
	int		a;
	char	c;

	c = ' ';
	a = 0;
	strf = NULL;
	len = conv->width - ft_strlen(*tmp);
	if (len > 0)
	{
		strf = ft_strnew(len);
		while (a < len)
		{
			(conv->tab['0'] != 0) ? c = '0' : c;
			strf[a++] = c;
		}
	}
	check_tab(conv, strf, tmp);
	if (strf)
		free(strf);
}
