/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:22:58 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/05 16:23:00 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_live(t_proc *proc, t_proc **begin)
{
	int		number;
	int		i;
	int		j;

	(void)begin;
	i = 0;
	number = proc->arg[0][1];
	while (i < MAX_PLAYERS)
	{
		if (g_live_tab[i].id == number && g_live_tab[i].name != NULL)
		{
			j = 0;
			while (j < MAX_PLAYERS)
				g_live_tab[j++].last = 0;
			g_live_tab[i].last = 1;
			g_live_tab[i].live++;
		}
		i++;
	}
	i = 0;
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
	proc->live += 1;
	proc->did_live = 1;
}
