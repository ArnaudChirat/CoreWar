/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:30:28 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:30:30 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_lldi(t_proc *proc, t_proc **begin)
{
	int		i;
	int		val1;
	int		val2;

	(void)begin;
	i = 0;
	if (proc->arg[0][0] == T_REG)
		val1 = proc->reg[proc->arg[0][1]];
	else if (proc->arg[0][0] == T_DIR)
		val1 = proc->arg[0][1];
	else
		val1 = ft_get_content_ind(proc, proc->arg[0][1]);
	if (proc->arg[1][0] == T_REG)
		val2 = proc->reg[proc->arg[1][1]];
	else
		val2 = proc->arg[1][1];
	proc->reg[proc->arg[2][1]] = 0;
	while (i < REG_SIZE)
	{
		proc->reg[proc->arg[2][1]] = g_arena[(proc->pc + (val1 + val2) + i) %
			MEM_SIZE].instruction += (val1 + val2) >> (REG_SIZE - i - 1) * 8;
		i++;
	}
	proc->carry = (val1 + val2 ? 0 : 1);
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
}
