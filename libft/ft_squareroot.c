/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_squareroot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 20:19:10 by achirat           #+#    #+#             */
/*   Updated: 2018/03/08 19:14:55 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_squareroot(double x, int prec)
{
	double	n;
	int		a;

	a = 0;
	n = x;
	if (x <= 0)
		return (0);
	while (a < prec)
	{
		x = (x + (n / x)) / 2;
		a++;
	}
	return (x);
}
