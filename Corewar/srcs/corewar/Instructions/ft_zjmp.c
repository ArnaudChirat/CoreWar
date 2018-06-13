/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:24:41 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/05 16:24:43 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_zjmp(t_proc *proc, t_proc **begin)
{
	(void)begin;
	if (!proc->carry)
		proc->pc = (proc->pc + proc->step) % MEM_SIZE;
	else
	{
		if (proc->arg[0][1] <= MEM_SIZE / 2)
			proc->pc = (proc->pc + proc->arg[0][1] % MEM_SIZE % IDX_MOD)
				% MEM_SIZE;
		else
			proc->pc = (MEM_SIZE + (proc->pc - ((MEM_SIZE - proc->arg[0][1]
				% MEM_SIZE) % IDX_MOD))) % MEM_SIZE;
	}
}
