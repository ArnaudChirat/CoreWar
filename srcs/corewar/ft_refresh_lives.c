/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refresh_lives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 03:42:12 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 03:42:58 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Les fonctions permettant au principal de l'action de se derouler.
**	C'est la qu'on gere les cycles de vie des processus
*/

static int	ft_reset_live(t_proc **begin, int check)
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
	if (check == MAX_CHECKS || res < NBR_LIVE)
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

void		ft_refresh_lives(t_data *data)
{
	data->number = ft_reset_live(&data->proc_list, data->check);
	if (data->number >= NBR_LIVE || data->check == MAX_CHECKS)
	{
		data->ctd = data->ctd - CYCLE_DELTA;
		ft_kill_process(&data->proc_list, 0, data->proc_list, NULL);
		data->check = 0;
	}
	else
		data->check++;
}
