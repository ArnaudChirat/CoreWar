/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 11:43:01 by achirat           #+#    #+#             */
/*   Updated: 2018/06/26 11:43:04 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strndup(const char *s1, int n)
{
	int		i;
	int		j;
	char	*cpy;

	i = (int)ft_strlen(s1) > n ? n : (int)ft_strlen(s1);
	if (i < 0)
		return (NULL);
	if (!(cpy = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	j = 0;
	while (j < i)
	{
		cpy[j] = s1[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}
