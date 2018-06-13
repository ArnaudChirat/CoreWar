/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_players.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanglai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:43:12 by clanglai          #+#    #+#             */
/*   Updated: 2018/06/08 10:02:39 by mjoubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	Tableau global contenant les infos trivials sur les joueurs, le nombre
**	de live par CYCLE_TO_DIE, l'id et la variable 'last' indiquant le dernier
**	joueur a avoir declare etre en vie
*/

t_live	g_live_tab[MAX_PLAYERS];

/*
**	Verifie la dispo d'un numero pour le flag -n
*/

static int		ft_id_available(t_player *players_list, int id)
{
	t_player	*begin_list;

	begin_list = players_list;
	while (begin_list)
	{
		if (id == begin_list->id)
			return (id + 1);
		begin_list = begin_list->next;
	}
	return (id);
}

/*
**	Attribue un id a chaque joueur, c'est ce numero qui lui permettra
**	d'effectuer un live a son nom pendant la partie
*/

static void		ft_id_players(t_player *players_list)
{
	int			id;
	t_player	*tmp;

	id = 1;
	tmp = players_list;
	while (tmp)
	{
		if (tmp->id == 0)
		{
			id = ft_id_available(players_list, id);
			tmp->id = id;
		}
		tmp = tmp->next;
	}
}

/*
**	On echange les joueurs dans la liste pour les faire correspondre a l'ordre
**	dans lesquels ils ont ete passes en arguments
*/

static void		ft_swap_player(t_player **players_list)
{
	t_player	*tmp;
	t_player	*tmp2;
	t_player	**pl_list_tmp;

	pl_list_tmp = players_list;
	while (*pl_list_tmp && (*pl_list_tmp)->next)
	{
		if ((*pl_list_tmp)->id > (*pl_list_tmp)->next->id)
		{
			tmp = *pl_list_tmp;
			tmp2 = (*pl_list_tmp)->next->next;
			*pl_list_tmp = (*pl_list_tmp)->next;
			(*pl_list_tmp)->next = tmp;
			(*pl_list_tmp)->next->next = tmp2;
			ft_swap_player(players_list);
			break ;
		}
		pl_list_tmp = &((*pl_list_tmp)->next);
	}
}

/*
**	On remplit le tableau global en se servant de la liste chaine
**	contenant tout les joueurs
*/

static void		ft_number_players(t_data *data, t_player *players_list)
{
	int		nbr;

	nbr = 1;
	while (players_list)
	{
		g_live_tab[nbr - 1].player_nbr = players_list->player_nbr;
		players_list->player_nbr = nbr;
		g_live_tab[nbr - 1].id = players_list->id;
		g_live_tab[nbr - 1].name = players_list->name;
		g_live_tab[nbr - 1].last = 0;
		nbr++;
		players_list = players_list->next;
	}
	data->nbr_player = nbr - 1;
	if (nbr - 1 > MAX_PLAYERS)
		ft_error(0, "Too many players", 0, 0);
	if (nbr == 2)
		ft_error(7, data->players_list->name, 0, 0);
}

/*
**	On parcoure les arguments pour extraire flags et noms de joueurs
*/

void			ft_players(t_data *data, char **argv, int argc)
{
	int				fd;
	int				index;
	t_player		*new;

	index = data->end_flag;
	while (index < argc)
	{
		new = NULL;
		while (index < argc && argv[index][0] == '-')
			ft_flags(&index, argv, &new);
		fd = open(argv[index], O_RDONLY);
		if (fd < 0)
			ft_error(2, argv[index], 0, 0);
		ft_champion(data, &new, argv[index], fd);
		close(fd);
		index++;
	}
	ft_id_players(data->players_list);
	ft_swap_player(&data->players_list);
	ft_number_players(data, data->players_list);
	ft_launch_players(data->players_list, data->nbr_player, 0);
}
