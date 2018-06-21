/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:28:47 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:28:49 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_fork(t_proc *proc, t_proc **begin)
{
	if (proc->arg[0][1] <= MEM_SIZE / 2)
		ft_add_proc_start(begin, ft_create_fork_proc((proc->pc + proc->arg[0][1]
		% IDX_MOD) % MEM_SIZE, proc));
	else
	{
		ft_add_proc_start(begin, ft_create_fork_proc((MEM_SIZE + (proc->pc
		- (MEM_SIZE - proc->arg[0][1] % MEM_SIZE) % IDX_MOD))
		% MEM_SIZE, proc));
	}
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
}
