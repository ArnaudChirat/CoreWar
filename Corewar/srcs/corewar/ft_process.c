/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:47:52 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 14:47:53 by cpaquet          ###   ########.fr       */
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
