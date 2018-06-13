/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:45:27 by clanglai          #+#    #+#             */
/*   Updated: 2018/06/07 11:28:16 by mjoubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"

void	ft_free_parse(t_data data)
{
	t_parse *tmp;
	t_parse	*next;

	tmp = data.parse;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->label)
			free(tmp->label);
		free(tmp);
		tmp = next;
	}
}

void	ft_free_data(t_data data)
{
	t_label *tmp;
	t_label *next;

	tmp = data.ind_label;
	if (tmp)
		while (tmp)
		{
			next = tmp->next;
			free(tmp->label);
			free(tmp);
			tmp = next;
		}
	tmp = data.stor_label;
	if (tmp)
		while (tmp)
		{
			next = tmp->next;
			free(tmp->label);
			free(tmp);
			tmp = next;
		}
	ft_free_parse(data);
}
