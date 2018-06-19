/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:47:42 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 14:47:43 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

int		ft_is_proc_index(int index, t_proc **begin)
{
	t_proc *tmp;

	tmp = *begin;
	while (tmp)
	{
		if (tmp->pc == index)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_print_matrix(void)
{
	int i;

	i = 0;
	ft_printf("0x%.4x :", i);
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i)
			write(1, " \n", 2);
		if (i % 64 == 0 && i)
			ft_printf("%#.4x :", i);
		ft_printf("%3.2hhx", g_arena[i].instruction);
		i++;
	}
	write(1, " \n", 2);
	exit(1);
}

void	ft_print_player(t_player *players_list)
{
	while (players_list)
	{
		ft_printf("_-- CHAMPIONS --_\n");
		ft_printf("ID = %d\n", players_list->id);
		ft_printf("Player number = %d\n", players_list->player_nbr);
		ft_printf("Magic number = %u\n", players_list->magic_nbr);
		ft_printf("Name = %s\n", players_list->name);
		ft_printf("Comment = %s\n", players_list->comment);
		ft_printf("Size of prog = %u\n", players_list->size_prog);
		ft_printf("--------------------------------------------------\n");
		players_list = players_list->next;
	}
}

void	ft_print_game(t_player **begin)
{
	t_player	*player;

	player = *begin;
	if (ft_strlen(player->name) == 0 || ft_strlen(player->comment) == 0)
		ft_error(5, 0, 0, 0);
	ft_printf("Introducing contestants...\n");
	while (player != NULL)
	{
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
				player->id, player->size_prog, player->name,
				player->comment);
		player = player->next;
	}
}
