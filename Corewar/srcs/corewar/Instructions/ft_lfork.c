/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:22:47 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/05 16:22:48 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_lfork(t_proc *proc, t_proc **begin)
{
	t_proc	*tmp;

	tmp = proc;
	ft_add_proc_start(begin, ft_create_fork_proc((proc->pc + proc->arg[0][1]
		% MEM_SIZE) % MEM_SIZE, proc));
	proc->carry = 0;
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
}
