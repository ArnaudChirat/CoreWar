/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:49:54 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 14:54:18 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	On free la variable 'data' qui contient toutes les informations necessaires
**	au deroulement de la partie
*/

void		ft_free_data(t_data *data)
{
	t_player	*player;
	t_proc		*proc;

	while (data->players_list)
	{
		ft_strdel(&data->players_list->name);
		ft_strdel(&data->players_list->comment);
		ft_strdel(&data->players_list->prog);
		player = data->players_list;
		data->players_list = data->players_list->next;
		free(player);
		player = NULL;
	}
	while (data->proc_list)
	{
		proc = data->proc_list;
		data->proc_list = data->proc_list->next;
		free(proc);
		proc = NULL;
	}
}
