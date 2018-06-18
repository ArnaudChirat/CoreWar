/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:28:18 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:28:21 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_and(t_proc *proc, t_proc **begin)
{
	int	val1;
	int val2;

	(void)begin;
	if (proc->arg[0][0] == T_REG)
		val1 = proc->reg[proc->arg[0][1]];
	else if (proc->arg[0][0] == T_IND)
		val1 = ft_get_content_ind(proc, proc->arg[0][1]);
	else
		val1 = proc->arg[0][1];
	if (proc->arg[1][0] == T_REG)
		val2 = proc->reg[proc->arg[1][1]];
	else if (proc->arg[1][0] == T_IND)
		val2 = ft_get_content_ind(proc, proc->arg[1][1]);
	else
		val2 = proc->arg[1][1];
	proc->reg[proc->arg[2][1]] = val1 & val2;
	if (proc->reg[proc->arg[2][1]])
		proc->carry = 0;
	else
		proc->carry = 1;
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
}
