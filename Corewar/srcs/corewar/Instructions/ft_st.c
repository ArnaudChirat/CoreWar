/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:23:47 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/07 14:09:39 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

static unsigned int		ft_get_val1(t_proc *proc)
{
	int	val1;

	if (proc->arg[1][0] == T_REG)
		return (-1);
	else
		val1 = (MEM_SIZE + proc->arg[1][1] % MEM_SIZE) % MEM_SIZE;
	return (val1);
}

void					ft_st(t_proc *proc, t_proc **begin)
{
	int	v;
	int i;

	(void)begin;
	i = 0;
	v = ft_get_val1(proc);
	while (i < REG_SIZE && v > -1)
	{
		if (v <= MEM_SIZE / 2)
		{
			g_arena[(proc->pc + v % IDX_MOD + i) % MEM_SIZE].instruction =
			proc->reg[proc->arg[0][1]] >> (REG_SIZE - i - 1) * 8 & 0xff;
			g_arena[(proc->pc + v % IDX_MOD + i++) % MEM_SIZE].player =
			proc->num;
		}
		else
		{
			g_arena[(MEM_SIZE + (proc->pc - (MEM_SIZE - v % MEM_SIZE)
			% IDX_MOD + i)) % MEM_SIZE].instruction =
			proc->reg[proc->arg[0][1]] >> (REG_SIZE - i - 1) * 8 & 0xff;
			g_arena[(MEM_SIZE + (proc->pc - (MEM_SIZE - v % MEM_SIZE)
			% IDX_MOD + i++)) % MEM_SIZE].player = proc->num;
		}
	}
	proc->pc = (proc->step + proc->pc) % MEM_SIZE;
}
