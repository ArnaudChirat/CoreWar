/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:23:47 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/14 11:52:39 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"
/*
static unsigned int		ft_get_val1(t_proc *proc)
{
	short	val1;

	if (proc->arg[1][0] == T_REG)
		return (-1);
	else
		val1 = proc->arg[1][1];
	return (val1);
}*/

void					ft_st(t_proc *proc, t_proc **begin)
{
	short	v;
	int		i;

	(void)begin;
	i = 0;
	if (proc->arg[1][0] != T_REG)
	{
		v = proc->arg[1][1] % IDX_MOD;
		while (i < REG_SIZE)
		{
			g_arena[(MEM_SIZE + proc->pc + v + i)
			% MEM_SIZE].instruction =
		proc->reg[proc->arg[0][1]] >> (REG_SIZE - i - 1) * 8 & 0xff;
		g_arena[(MEM_SIZE + proc->pc + v + i) % MEM_SIZE].player = proc->num;
		i++;

			/*	g_arena[(proc->pc + v % IDX_MOD + i) % MEM_SIZE].instruction =
				proc->reg[proc->arg[0][1]] >> (REG_SIZE - i - 1) * 8 & 0xff;
				g_arena[(proc->pc + v % IDX_MOD + i++) % MEM_SIZE].player =
				proc->num;*/
		}
	}
	proc->pc = (proc->step + proc->pc) % MEM_SIZE;
}
