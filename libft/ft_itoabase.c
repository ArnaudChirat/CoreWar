/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:11:05 by achirat           #+#    #+#             */
/*   Updated: 2018/01/15 17:13:11 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*fill(int len, char *str, long long nbr, char *base)
{
	long long	n2;
	size_t		len_base;

	n2 = nbr;
	len_base = ft_strlen(base);
	if (nbr >= 0)
		while (len >= 0)
		{
			str[len] = base[n2 % len_base];
			n2 = n2 / len_base;
			len--;
		}
	else
	{
		n2 = -n2;
		while (len > 0)
		{
			str[len] = base[n2 % len_base];
			n2 = n2 / len_base;
			len--;
		}
		str[len] = '-';
	}
	return (str);
}

char			*ft_itoabase(long long nbr, char *base)
{
	int					len;
	char				*str;
	unsigned long long	nbr1;
	size_t				len_base;

	len = 0;
	len_base = ft_strlen(base);
	if (nbr < 0)
	{
		nbr1 = -nbr;
		len++;
	}
	else
		nbr1 = nbr;
	while (nbr1 > (len_base - 1))
	{
		nbr1 = nbr1 / len_base;
		len++;
	}
	if (!(str = ft_strnew(len + 1)))
		return (0);
	str = fill(len, str, nbr, base);
	return (str);
}

static char		*fillu(int len, char *str, unsigned long long nbr, char *base)
{
	size_t		len_base;

	len_base = ft_strlen(base);
	while (len >= 0)
	{
		str[len] = base[nbr % len_base];
		nbr = nbr / len_base;
		len--;
	}
	return (str);
}

char			*ft_itoabase_u(unsigned long long nbr, char *base)
{
	int					len;
	char				*str;
	unsigned long long	nbr1;
	size_t				len_base;

	len = 0;
	len_base = ft_strlen(base);
	nbr1 = nbr;
	while (nbr1 > (len_base - 1))
	{
		nbr1 = nbr1 / len_base;
		len++;
	}
	if (!(str = ft_strnew(len + 1)))
		return (0);
	str = fillu(len, str, nbr, base);
	return (str);
}
