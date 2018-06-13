/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:04:24 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/01 11:19:45 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

void	ft_process(t_data *data)
{
	t_player	*player;
	t_proc		*proc;

	player = data->players_list;
	proc = NULL;
	while (player != NULL)
	{
		proc = ft_create_init_proc(player->pc, player->id, player->player_nbr);
		ft_add_proc_start(&data->proc_list, proc);
		player = player->next;
	}
}
