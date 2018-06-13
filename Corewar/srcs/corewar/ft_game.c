/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:42:45 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/07 17:09:25 by clanglai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	Les fonctions permettant au principal de l'action de se derouler.
**	C'est la qu'on gere les cycles de vie des processus
*/

int			ft_count_players_left(void)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (i < MAX_PLAYERS)
		if (g_live_tab[i++].live)
			res++;
	return (res);
}

int			ft_reset_live(t_proc **begin, int state)
{
	int		i;
	int		res;
	t_proc	*tmp;

	i = 0;
	res = 0;
	while (i < MAX_PLAYERS)
	{
		res += g_live_tab[i].live;
		g_live_tab[i++].live = 0;
	}
	if (!state || res < NBR_LIVE)
	{
		tmp = *begin;
		while (tmp)
		{
			tmp->live = 0;
			tmp->did_live = 0;
			tmp = tmp->next;
		}
	}
	return (res);
}

/*
**	On 'tue' les process n'ayant pas fait de live pendant CYCLE_TO_DIE cycles
*/

static int	ft_kill_process(t_proc **list, int res, t_proc *tmp, t_proc *next)
{
	t_proc	*prev;

	while (tmp)
	{
		next = tmp->next;
		res += tmp->live;
		if (tmp->did_live == 0)
			if (tmp == *list)
			{
				free(tmp);
				*list = next;
			}
			else
			{
				free(tmp);
				prev->next = next;
			}
		else
			prev = ft_reset_live_proc(&tmp);
		tmp = next;
	}
	return (res);
}

/*
**	On determine le gagnant en fonction de la variable 'last' dans le tableau
**	global rassemblant les joueurs. Elle sert a distinguer le dernier champion
**	a avoir emis un live a son nom.
*/

void		ft_winner(void)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (g_live_tab[i].last == 1)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n", g_live_tab[i].id,
					g_live_tab[i].name);
			break ;
		}
		i++;
	}
	if (i == MAX_PLAYERS)
		ft_printf("No live, no game.\n");
}

/*
**	"L'horloge" de la machine virtuelle, elle rythme les cycles, clean les pro-
**	cessus et regule le compteur de live.
*/

void		ft_game(t_data *data, t_draw d)
{
	while (d.ctd > 0 && data->proc_list != NULL)
	{
		d.cy = 0;
		while (++d.cy < d.ctd)
		{
			ft_fight(&data->proc_list);
			if (data->flag_v)
				ft_draw_cycle(&d, data);
			if (data->dump_val && data->dump_val == d.cyc_tot)
				ft_print_matrix();
			d.cyc_tot++;
		}
		d.number = ft_reset_live(&data->proc_list, d.check != MAX_CHECKS);
		if (d.number >= NBR_LIVE || d.check == MAX_CHECKS)
		{
			d.ctd = d.ctd - CYCLE_DELTA;
			ft_kill_process(&data->proc_list, 0, data->proc_list, NULL);
			d.check = 0;
		}
		else
			d.check++;
	}
	getch();
	endwin();
	ft_winner();
}
