/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:22:13 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/05 16:22:15 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_fork(t_proc *proc, t_proc **begin)
{
	t_proc	*tmp;
	int		state;
	int		i;

	tmp = proc;
	state = 1;
	i = 0;
	if (proc->arg[0][1] <= MEM_SIZE / 2)
		ft_add_proc_start(begin, ft_create_fork_proc((proc->pc + proc->arg[0][1]
		% IDX_MOD) % MEM_SIZE, proc));
	else
	{
		state = 2;
		ft_add_proc_start(begin, ft_create_fork_proc((MEM_SIZE + (proc->pc
		- (MEM_SIZE - proc->arg[0][1] % MEM_SIZE) % IDX_MOD))
		% MEM_SIZE, proc));
	}
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
	tmp = *begin;
}
