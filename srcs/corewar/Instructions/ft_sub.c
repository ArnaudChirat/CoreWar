/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:32:05 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 18:32:57 by achirat          ###   ########.fr       */
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
