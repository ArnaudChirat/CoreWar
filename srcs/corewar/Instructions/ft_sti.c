/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:31:21 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:31:23 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

static int	ft_get_val1(t_proc *proc)
{
	int		val1;

	if (proc->arg[1][0] == T_REG)
		val1 = proc->reg[proc->arg[1][1]];
	else if (proc->arg[1][0] == T_DIR)
		val1 = proc->arg[1][1];
	else
		val1 = ft_get_content_ind(proc, proc->arg[1][1]);
	return (val1);
}

static int	ft_get_val2(t_proc *proc)
{
	int		val2;

	if (proc->arg[2][0] == T_REG)
		val2 = proc->reg[proc->arg[2][1]];
	else
		val2 = proc->arg[2][1];
	return (val2);
}

void		ft_sti(t_proc *proc, t_proc **begin)
{
	int		val1;
	int		val2;
	int		i;
	int		sum;

	(void)begin;
	i = 0;
	val1 = ft_get_val1(proc);
	val2 = ft_get_val2(proc);
	sum = ((val1 + val2) % IDX_MOD);
	while (i < REG_SIZE)
	{
		g_arena[(MEM_SIZE + proc->pc + sum + i) % MEM_SIZE].instruction =
		proc->reg[proc->arg[0][1]] >> (REG_SIZE - i - 1) * 8 & 0xff;
		g_arena[(MEM_SIZE + proc->pc + sum + i) % MEM_SIZE].player = proc->num;
		i++;
	}
	proc->pc = (proc->step + proc->pc) % MEM_SIZE;
}
