/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 11:29:06 by achirat           #+#    #+#             */
/*   Updated: 2018/06/18 11:29:08 by achirat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

static unsigned int	ft_get_val1(t_proc *proc)
{
	unsigned int	val1;

	if (proc->arg[0][0] == T_REG)
		val1 = proc->reg[proc->arg[0][1]];
	else if (proc->arg[0][0] == T_DIR)
	{
		val1 = proc->arg[0][1];
		if (val1 > 65536 / 2)
			val1 = val1 - 65536;
	}
	else
	{
		if (proc->arg[0][1] % MEM_SIZE > MEM_SIZE / 2)
			val1 = ft_get_content_ind(proc, -((MEM_SIZE - proc->arg[0][1]
				% MEM_SIZE) % IDX_MOD));
		else
			val1 = ft_get_content_ind(proc, proc->arg[0][1] % IDX_MOD);
	}
	return (val1);
}

static unsigned int	ft_get_val2(t_proc *proc)
{
	unsigned int	val2;

	if (proc->arg[1][0] == T_REG)
		val2 = proc->reg[proc->arg[1][1]];
	else
	{
		val2 = proc->arg[1][1];
		if (val2 > 65536 / 2)
			val2 = val2 - 65536;
	}
	return (val2);
}

void				ft_ldi(t_proc *proc, t_proc **begin)
{
	int				i;
	unsigned int	val1;
	unsigned int	val2;
	int				sum;

	(void)begin;
	i = 0;
	val1 = ft_get_val1(proc);
	val2 = ft_get_val2(proc);
	proc->reg[proc->arg[2][1]] = 0;
	if ((val1 + val2) % MEM_SIZE > MEM_SIZE / 2)
		sum = -((MEM_SIZE - (val1 + val2) % MEM_SIZE) % IDX_MOD);
	else
		sum = (val1 + val2) % MEM_SIZE % IDX_MOD;
	while (i < REG_SIZE)
	{
		proc->reg[proc->arg[2][1]] *= 256;
		proc->reg[proc->arg[2][1]] += g_arena[(MEM_SIZE + (proc->pc + (sum)
			+ i++)) % MEM_SIZE].instruction & 0xff;
	}
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
	if (sum)
		proc->carry = 0;
	else
		proc->carry = 1;
}
