/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:27:58 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:28:01 by achirat          ###   ########.fr       */
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
