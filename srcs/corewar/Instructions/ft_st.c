/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:30:44 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 18:32:30 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void					ft_st(t_proc *proc, t_proc **begin)
{
	short	v;
	int		i;

	(void)begin;
	i = 0;
	v = proc->arg[1][1];
	if (proc->arg[1][0] != T_REG)
	{
		v = v % IDX_MOD;
		while (i < REG_SIZE)
		{
			g_arena[(MEM_SIZE + proc->pc + v + i) % MEM_SIZE].instruction =
				proc->reg[proc->arg[0][1]] >> (REG_SIZE - i - 1) * 8 & 0xff;
			g_arena[(MEM_SIZE + proc->pc + v + i) % MEM_SIZE].player =
																	proc->num;
			i++;
		}
	}
	proc->pc = (proc->step + proc->pc) % MEM_SIZE;
}
