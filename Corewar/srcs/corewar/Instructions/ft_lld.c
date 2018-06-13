/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccorsin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:23:10 by ccorsin           #+#    #+#             */
/*   Updated: 2018/06/05 16:23:11 by ccorsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/vm.h"

void			ft_lld(t_proc *proc, t_proc **begin)
{
	int		i;
	int		value;

	(void)begin;
	i = 0;
	proc->reg[proc->arg[1][1]] = 0;
	if (proc->arg[0][0] == T_DIR)
		value = proc->arg[0][1];
	else
		value = ft_get_content_ind(proc, proc->arg[0][1]);
	while (i < REG_SIZE)
	{
		proc->reg[proc->arg[1][1]] += value << ((REG_SIZE - 1 - i) * 8) & 0xff;
		i++;
	}
	if (value)
		proc->carry = 0;
	else
		proc->carry = 1;
	proc->pc = (proc->pc + proc->step) % MEM_SIZE;
}
