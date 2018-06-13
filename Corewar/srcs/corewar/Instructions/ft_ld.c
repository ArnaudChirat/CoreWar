/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:22:24 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/07 11:56:42 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_ld(t_proc *proc, t_proc **begin)
{
	int				i;
	unsigned int	value;

	(void)begin;
	i = 0;
	proc->reg[proc->arg[1][1]] = 0;
	if (proc->arg[0][0] == T_DIR)
		value = proc->arg[0][1];
	else
	{
		if (proc->arg[0][1] % MEM_SIZE > MEM_SIZE / 2)
			value = ft_get_content_ind(proc, -((MEM_SIZE - proc->arg[0][1]
				% MEM_SIZE) % IDX_MOD));
		else
			value = ft_get_content_ind(proc, proc->arg[0][1] % IDX_MOD);
	}
	proc->reg[proc->arg[1][1]] = value;
	if (value)
		proc->carry = 0;
	else
		proc->carry = 1;
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
}
