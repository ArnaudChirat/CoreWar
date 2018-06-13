/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:18:42 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/05 16:18:44 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"
#include "../../inc/vm_define_list.h"

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

void		ft_free_all(t_data *data)
{
	ft_free_data(data);
}
