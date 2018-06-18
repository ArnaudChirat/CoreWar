/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:32:23 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:32:25 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_zjmp(t_proc *proc, t_proc **begin)
{
	short i;

	(void)begin;
	if (!proc->carry)
		proc->pc = (proc->pc + proc->step) % MEM_SIZE;
	else
	{
		i = proc->arg[0][1];
		proc->pc = (proc->pc + (i % MEM_SIZE % IDX_MOD))
				% MEM_SIZE;
		if (proc->pc < 0)
			proc->pc += MEM_SIZE;
	}
}
