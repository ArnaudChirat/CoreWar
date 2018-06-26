/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 11:21:36 by achirat           #+#    #+#             */
/*   Updated: 2018/06/26 16:10:50 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LEN_1 0
#define LEN_2 1
#define LEN_S 2

static char	*len_str(char *n1, char *n2, char *str, int *index)
{
	size_t	len_n1;
	size_t	len_n2;

	len_n1 = ft_strlen(n1);
	len_n2 = ft_strlen(n2);
	if (len_n1 > len_n2)
	{
		*index = len_n1 - 1;
		str = ft_strnew(len_n1 + 1);
		str = ft_strdup(n1);
	}
	else
	{
		*index = len_n2 - 1;
		str = ft_strnew(len_n2 + 1);
		str = ft_strdup(n2);
	}
	return (str);
}

char		*ft_addstr(char *n1, char *n2, char *base)
{
	int		index;
	size_t	len_base;
	char	*str;
	int		len[LEN_S];

	if (!n1 || !n2)
		return (0);
	len[LEN_1] = ft_strlen(n1) - 1;
	len[LEN_2] = ft_strlen(n2) - 1;
	len_base = ft_strlen(base);
	str = len_str(n1, n2, str, &index);
	while (len[LEN_2] >= 0 && len[LEN_1] >= 0)
	{
		if ((n1[len[LEN_1]] + n2[len[LEN_2]] - 96) >= (int)len_base)
		{
			str[index] = n1[len[LEN_1]] + n2[len[LEN_2]] - len_base - 48;
			str[index - 1] += 1;
		}
		else
			str[index] = n1[len[LEN_1]] + n2[len[LEN_2]] - 48;
		index--;
		len[LEN_1]--;
		len[LEN_2]--;
	}
	return (str);
}
