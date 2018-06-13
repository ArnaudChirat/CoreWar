/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:24:12 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/05 16:24:13 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_sub(t_proc *proc, t_proc **begin)
{
	(void)begin;
	proc->reg[proc->arg[2][1]] = proc->reg[proc->arg[0][1]] -
		proc->reg[proc->arg[1][1]];
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
	if (proc->reg[proc->arg[2][1]])
		proc->carry = 0;
	else
		proc->carry = 1;
}
