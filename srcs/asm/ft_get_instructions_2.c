/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_instructions_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:36:23 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:36:25 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

void	ft_get_instructions_2(t_parse *tmp, t_parse *next)
{
	char *str;

	while (tmp)
	{
		if (ft_strchr(tmp->label, LABEL_CHAR) && tmp->label[0] != LABEL_CHAR
			&& tmp->label[ft_strlen(tmp->label) - 1] != LABEL_CHAR)
		{
			next = tmp->next;
			tmp->next = ft_new_parse(tmp->col, tmp->lig,
					ft_strdup(ft_strchr(tmp->label, LABEL_CHAR) + 1), 0);
			str = ft_strsub(tmp->label, 0, ft_strlen(tmp->label) -
					ft_strlen(ft_strchr(tmp->label, LABEL_CHAR) + 1));
			free(tmp->label);
			tmp->label = str;
			tmp->next->next = next;
		}
		tmp = tmp->next;
	}
}
