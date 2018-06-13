/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:22:13 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/07 15:17:35 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_add(t_proc *proc, t_proc **begin)
{
	(void)begin;
	proc->reg[proc->arg[2][1]] = proc->reg[proc->arg[0][1]] +
		proc->reg[proc->arg[1][1]];
	if (proc->reg[proc->arg[2][1]])
		proc->carry = 0;
	else
		proc->carry = 1;
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
}
