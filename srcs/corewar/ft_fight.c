/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:50:05 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 14:50:06 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/vm.h"

/*
**	La fonction ou se deroule le plus gros de l'action. On appelle chaque
**	processus dans l'ordre inverse de leur creation. Si ils lisent un opcode
**	valide on lance le nombre de cycle correspondants. Si apres ce nombre
**	de cycles on s'apercoit que les arguments sont valides on avance de 1
**	sinon on execute l'action et on avance le process de la longueur des args
*/

static void	ft_fight_2(t_proc **tmp, t_proc **begin)
{
	if ((*tmp)->hold == 1)
	{
		if (ft_check_op(*tmp, 1) > 0)
			(*g_func_tab[(*tmp)->opcode - 1])(*tmp, begin);
		else
		{
			if (g_op_tab[(*tmp)->opcode].o_cod == 1)
				(*tmp)->pc = ((*tmp)->pc + 2) % MEM_SIZE;
			else
				(*tmp)->pc = ((*tmp)->pc + 1) % MEM_SIZE;
		}
		(*tmp)->hold = 1;
	}
	(*tmp)->hold = (*tmp)->hold - 1;
}

void		ft_fight(t_proc **begin)
{
	t_proc	*tmp;
	int		i;

	tmp = *begin;
	i = 0;
	while (tmp)
	{
		if (tmp->hold == 0)
		{
			if (ft_check_op(tmp, 0) == -2)
				tmp->pc = (tmp->pc + 1) % MEM_SIZE;
		}
		else
			ft_fight_2(&tmp, begin);
		tmp = tmp->next;
		i++;
	}
}
